//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

package com.stealthsoftwareinc.sst;

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import java.util.Collections;
import java.util.Map;

public enum JdbcType implements ToInt, ToJson {
  ARRAY(java.sql.Types.ARRAY),
  BIGINT(java.sql.Types.BIGINT),
  BINARY(java.sql.Types.BINARY),
  BIT(java.sql.Types.BIT),
  BLOB(java.sql.Types.BLOB),
  BOOLEAN(java.sql.Types.BOOLEAN),
  CHAR(java.sql.Types.CHAR),
  CLOB(java.sql.Types.CLOB),
  DATALINK(java.sql.Types.DATALINK),
  DATE(java.sql.Types.DATE),
  DECIMAL(java.sql.Types.DECIMAL),
  DISTINCT(java.sql.Types.DISTINCT),
  DOUBLE(java.sql.Types.DOUBLE),
  FLOAT(java.sql.Types.FLOAT),
  INTEGER(java.sql.Types.INTEGER),
  JAVA_OBJECT(java.sql.Types.JAVA_OBJECT),
  LONGNVARCHAR(java.sql.Types.LONGNVARCHAR),
  LONGVARBINARY(java.sql.Types.LONGVARBINARY),
  LONGVARCHAR(java.sql.Types.LONGVARCHAR),
  NCHAR(java.sql.Types.NCHAR),
  NCLOB(java.sql.Types.NCLOB),
  NULL(java.sql.Types.NULL),
  NUMERIC(java.sql.Types.NUMERIC),
  NVARCHAR(java.sql.Types.NVARCHAR),
  OTHER(java.sql.Types.OTHER),
  REAL(java.sql.Types.REAL),
  REF(java.sql.Types.REF),
  ROWID(java.sql.Types.ROWID),
  SMALLINT(java.sql.Types.SMALLINT),
  SQLXML(java.sql.Types.SQLXML),
  STRUCT(java.sql.Types.STRUCT),
  TIME(java.sql.Types.TIME),
  TIMESTAMP(java.sql.Types.TIMESTAMP),
  TINYINT(java.sql.Types.TINYINT),
  VARBINARY(java.sql.Types.VARBINARY),
  VARCHAR(java.sql.Types.VARCHAR);

  //--------------------------------------------------------------------

  private final int id_;

  private JdbcType(final int id) {
    id_ = id;
  }

  //--------------------------------------------------------------------
  // Integer representation
  //--------------------------------------------------------------------

  @Override
  public int toInt() {
    return id_;
  }

  private static final Map<Integer, JdbcType> intMap_ =
      Collections.unmodifiableMap(Enums.toIntMap(JdbcType.class));

  public static JdbcType fromInt(final int src) {
    return Enums.fromInt(JdbcType.class, intMap_, src);
  }

  //--------------------------------------------------------------------
  // String representation
  //--------------------------------------------------------------------

  @Override
  public String toString() {
    return name();
  }

  public static JdbcType fromString(final CharSequence src) {
    return Enums.fromString(JdbcType.class, src);
  }

  //--------------------------------------------------------------------
  // canSetFrom
  //--------------------------------------------------------------------
  //
  // See JDBC 4.1 Table B-5.
  //

  public final boolean canSetFrom(final String T) {
    switch (this) {
      case TINYINT:
      case SMALLINT:
      case INTEGER:
      case BIGINT:
      case REAL:
      case FLOAT:
      case DOUBLE:
      case DECIMAL:
      case NUMERIC:
      case BIT:
      case BOOLEAN:
      case CHAR:
      case VARCHAR:
      case LONGVARCHAR:
      case BINARY:
      case VARBINARY:
      case LONGVARBINARY:
      case DATE:
      case TIME:
      case TIMESTAMP:
      case NCHAR:
      case NVARCHAR:
      case LONGNVARCHAR:
        return true;
    }
    return false;
  }

  //--------------------------------------------------------------------
  // fromJson
  //--------------------------------------------------------------------

  public static final CreateFromJson<JdbcType> fromJson() {
    return new CreateFromJson<JdbcType>() {
      @Override
      public final JdbcType createFromJson(final Object src) {
        try {
          return fromString(Json.getAs(src, (String)null));
        } catch (final EnumConstantNotPresentException e) {
          throw new JsonException("Unknown JDBC type: "
                                  + Json.smartQuote((String)src));
        }
      }
    };
  }

  //--------------------------------------------------------------------
  // isNumeric
  //--------------------------------------------------------------------

  public final boolean isNumeric() {
    switch (this) {
      case BIGINT:
      case BIT:
      case BOOLEAN:
      case DECIMAL:
      case DOUBLE:
      case FLOAT:
      case INTEGER:
      case NUMERIC:
      case REAL:
      case SMALLINT:
      case TINYINT:
        return true;
    }
    return false;
  }

  //--------------------------------------------------------------------
  // isString
  //--------------------------------------------------------------------

  public final boolean isString() {
    switch (this) {
      case CHAR:
      case LONGVARCHAR:
      case VARCHAR:
        return true;
    }
    return false;
  }

  //--------------------------------------------------------------------
  // toJson
  //--------------------------------------------------------------------

  @Override
  public final Object toJson() {
    return toString();
  }

  //--------------------------------------------------------------------
}
