//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

package com.stealthsoftwareinc.test.sst;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.stealthsoftwareinc.sst.JdbcType;
import java.sql.Types;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

@Execution(ExecutionMode.CONCURRENT)
public final class JdbcTypeTest {
  @Test
  public final void testToInt() {
    assertEquals(Types.ARRAY, JdbcType.ARRAY.toInt());
    assertEquals(Types.BIGINT, JdbcType.BIGINT.toInt());
    assertEquals(Types.BINARY, JdbcType.BINARY.toInt());
    assertEquals(Types.BIT, JdbcType.BIT.toInt());
    assertEquals(Types.BLOB, JdbcType.BLOB.toInt());
    assertEquals(Types.BOOLEAN, JdbcType.BOOLEAN.toInt());
    assertEquals(Types.CHAR, JdbcType.CHAR.toInt());
    assertEquals(Types.CLOB, JdbcType.CLOB.toInt());
    assertEquals(Types.DATALINK, JdbcType.DATALINK.toInt());
    assertEquals(Types.DATE, JdbcType.DATE.toInt());
    assertEquals(Types.DECIMAL, JdbcType.DECIMAL.toInt());
    assertEquals(Types.DISTINCT, JdbcType.DISTINCT.toInt());
    assertEquals(Types.DOUBLE, JdbcType.DOUBLE.toInt());
    assertEquals(Types.FLOAT, JdbcType.FLOAT.toInt());
    assertEquals(Types.INTEGER, JdbcType.INTEGER.toInt());
    assertEquals(Types.JAVA_OBJECT, JdbcType.JAVA_OBJECT.toInt());
    assertEquals(Types.LONGNVARCHAR, JdbcType.LONGNVARCHAR.toInt());
    assertEquals(Types.LONGVARBINARY, JdbcType.LONGVARBINARY.toInt());
    assertEquals(Types.LONGVARCHAR, JdbcType.LONGVARCHAR.toInt());
    assertEquals(Types.NCHAR, JdbcType.NCHAR.toInt());
    assertEquals(Types.NCLOB, JdbcType.NCLOB.toInt());
    assertEquals(Types.NULL, JdbcType.NULL.toInt());
    assertEquals(Types.NUMERIC, JdbcType.NUMERIC.toInt());
    assertEquals(Types.NVARCHAR, JdbcType.NVARCHAR.toInt());
    assertEquals(Types.OTHER, JdbcType.OTHER.toInt());
    assertEquals(Types.REAL, JdbcType.REAL.toInt());
    assertEquals(Types.REF, JdbcType.REF.toInt());
    assertEquals(Types.ROWID, JdbcType.ROWID.toInt());
    assertEquals(Types.SMALLINT, JdbcType.SMALLINT.toInt());
    assertEquals(Types.SQLXML, JdbcType.SQLXML.toInt());
    assertEquals(Types.STRUCT, JdbcType.STRUCT.toInt());
    assertEquals(Types.TIME, JdbcType.TIME.toInt());
    assertEquals(Types.TIMESTAMP, JdbcType.TIMESTAMP.toInt());
    assertEquals(Types.TINYINT, JdbcType.TINYINT.toInt());
    assertEquals(Types.VARBINARY, JdbcType.VARBINARY.toInt());
    assertEquals(Types.VARCHAR, JdbcType.VARCHAR.toInt());
  }

  @Test
  public final void testFromInt() {
    assertEquals(Types.ARRAY, JdbcType.fromInt(Types.ARRAY).toInt());
    assertEquals(Types.BIGINT, JdbcType.fromInt(Types.BIGINT).toInt());
    assertEquals(Types.BINARY, JdbcType.fromInt(Types.BINARY).toInt());
    assertEquals(Types.BIT, JdbcType.fromInt(Types.BIT).toInt());
    assertEquals(Types.BLOB, JdbcType.fromInt(Types.BLOB).toInt());
    assertEquals(Types.BOOLEAN,
                 JdbcType.fromInt(Types.BOOLEAN).toInt());
    assertEquals(Types.CHAR, JdbcType.fromInt(Types.CHAR).toInt());
    assertEquals(Types.CLOB, JdbcType.fromInt(Types.CLOB).toInt());
    assertEquals(Types.DATALINK,
                 JdbcType.fromInt(Types.DATALINK).toInt());
    assertEquals(Types.DATE, JdbcType.fromInt(Types.DATE).toInt());
    assertEquals(Types.DECIMAL,
                 JdbcType.fromInt(Types.DECIMAL).toInt());
    assertEquals(Types.DISTINCT,
                 JdbcType.fromInt(Types.DISTINCT).toInt());
    assertEquals(Types.DOUBLE, JdbcType.fromInt(Types.DOUBLE).toInt());
    assertEquals(Types.FLOAT, JdbcType.fromInt(Types.FLOAT).toInt());
    assertEquals(Types.INTEGER,
                 JdbcType.fromInt(Types.INTEGER).toInt());
    assertEquals(Types.JAVA_OBJECT,
                 JdbcType.fromInt(Types.JAVA_OBJECT).toInt());
    assertEquals(Types.LONGNVARCHAR,
                 JdbcType.fromInt(Types.LONGNVARCHAR).toInt());
    assertEquals(Types.LONGVARBINARY,
                 JdbcType.fromInt(Types.LONGVARBINARY).toInt());
    assertEquals(Types.LONGVARCHAR,
                 JdbcType.fromInt(Types.LONGVARCHAR).toInt());
    assertEquals(Types.NCHAR, JdbcType.fromInt(Types.NCHAR).toInt());
    assertEquals(Types.NCLOB, JdbcType.fromInt(Types.NCLOB).toInt());
    assertEquals(Types.NULL, JdbcType.fromInt(Types.NULL).toInt());
    assertEquals(Types.NUMERIC,
                 JdbcType.fromInt(Types.NUMERIC).toInt());
    assertEquals(Types.NVARCHAR,
                 JdbcType.fromInt(Types.NVARCHAR).toInt());
    assertEquals(Types.OTHER, JdbcType.fromInt(Types.OTHER).toInt());
    assertEquals(Types.REAL, JdbcType.fromInt(Types.REAL).toInt());
    assertEquals(Types.REF, JdbcType.fromInt(Types.REF).toInt());
    assertEquals(Types.ROWID, JdbcType.fromInt(Types.ROWID).toInt());
    assertEquals(Types.SMALLINT,
                 JdbcType.fromInt(Types.SMALLINT).toInt());
    assertEquals(Types.SQLXML, JdbcType.fromInt(Types.SQLXML).toInt());
    assertEquals(Types.STRUCT, JdbcType.fromInt(Types.STRUCT).toInt());
    assertEquals(Types.TIME, JdbcType.fromInt(Types.TIME).toInt());
    assertEquals(Types.TIMESTAMP,
                 JdbcType.fromInt(Types.TIMESTAMP).toInt());
    assertEquals(Types.TINYINT,
                 JdbcType.fromInt(Types.TINYINT).toInt());
    assertEquals(Types.VARBINARY,
                 JdbcType.fromInt(Types.VARBINARY).toInt());
    assertEquals(Types.VARCHAR,
                 JdbcType.fromInt(Types.VARCHAR).toInt());
  }

  @Test
  public final void testToString() {
    assertEquals("ARRAY", JdbcType.ARRAY.toString());
    assertEquals("BIGINT", JdbcType.BIGINT.toString());
    assertEquals("BINARY", JdbcType.BINARY.toString());
    assertEquals("BIT", JdbcType.BIT.toString());
    assertEquals("BLOB", JdbcType.BLOB.toString());
    assertEquals("BOOLEAN", JdbcType.BOOLEAN.toString());
    assertEquals("CHAR", JdbcType.CHAR.toString());
    assertEquals("CLOB", JdbcType.CLOB.toString());
    assertEquals("DATALINK", JdbcType.DATALINK.toString());
    assertEquals("DATE", JdbcType.DATE.toString());
    assertEquals("DECIMAL", JdbcType.DECIMAL.toString());
    assertEquals("DISTINCT", JdbcType.DISTINCT.toString());
    assertEquals("DOUBLE", JdbcType.DOUBLE.toString());
    assertEquals("FLOAT", JdbcType.FLOAT.toString());
    assertEquals("INTEGER", JdbcType.INTEGER.toString());
    assertEquals("JAVA_OBJECT", JdbcType.JAVA_OBJECT.toString());
    assertEquals("LONGNVARCHAR", JdbcType.LONGNVARCHAR.toString());
    assertEquals("LONGVARBINARY", JdbcType.LONGVARBINARY.toString());
    assertEquals("LONGVARCHAR", JdbcType.LONGVARCHAR.toString());
    assertEquals("NCHAR", JdbcType.NCHAR.toString());
    assertEquals("NCLOB", JdbcType.NCLOB.toString());
    assertEquals("NULL", JdbcType.NULL.toString());
    assertEquals("NUMERIC", JdbcType.NUMERIC.toString());
    assertEquals("NVARCHAR", JdbcType.NVARCHAR.toString());
    assertEquals("OTHER", JdbcType.OTHER.toString());
    assertEquals("REAL", JdbcType.REAL.toString());
    assertEquals("REF", JdbcType.REF.toString());
    assertEquals("ROWID", JdbcType.ROWID.toString());
    assertEquals("SMALLINT", JdbcType.SMALLINT.toString());
    assertEquals("SQLXML", JdbcType.SQLXML.toString());
    assertEquals("STRUCT", JdbcType.STRUCT.toString());
    assertEquals("TIME", JdbcType.TIME.toString());
    assertEquals("TIMESTAMP", JdbcType.TIMESTAMP.toString());
    assertEquals("TINYINT", JdbcType.TINYINT.toString());
    assertEquals("VARBINARY", JdbcType.VARBINARY.toString());
    assertEquals("VARCHAR", JdbcType.VARCHAR.toString());
  }

  @Test
  public final void testFromString() {
    assertEquals(Types.ARRAY, JdbcType.fromString("ARRAY").toInt());
    assertEquals(Types.BIGINT, JdbcType.fromString("BIGINT").toInt());
    assertEquals(Types.BINARY, JdbcType.fromString("BINARY").toInt());
    assertEquals(Types.BIT, JdbcType.fromString("BIT").toInt());
    assertEquals(Types.BLOB, JdbcType.fromString("BLOB").toInt());
    assertEquals(Types.BOOLEAN, JdbcType.fromString("BOOLEAN").toInt());
    assertEquals(Types.CHAR, JdbcType.fromString("CHAR").toInt());
    assertEquals(Types.CLOB, JdbcType.fromString("CLOB").toInt());
    assertEquals(Types.DATALINK,
                 JdbcType.fromString("DATALINK").toInt());
    assertEquals(Types.DATE, JdbcType.fromString("DATE").toInt());
    assertEquals(Types.DECIMAL, JdbcType.fromString("DECIMAL").toInt());
    assertEquals(Types.DISTINCT,
                 JdbcType.fromString("DISTINCT").toInt());
    assertEquals(Types.DOUBLE, JdbcType.fromString("DOUBLE").toInt());
    assertEquals(Types.FLOAT, JdbcType.fromString("FLOAT").toInt());
    assertEquals(Types.INTEGER, JdbcType.fromString("INTEGER").toInt());
    assertEquals(Types.JAVA_OBJECT,
                 JdbcType.fromString("JAVA_OBJECT").toInt());
    assertEquals(Types.LONGNVARCHAR,
                 JdbcType.fromString("LONGNVARCHAR").toInt());
    assertEquals(Types.LONGVARBINARY,
                 JdbcType.fromString("LONGVARBINARY").toInt());
    assertEquals(Types.LONGVARCHAR,
                 JdbcType.fromString("LONGVARCHAR").toInt());
    assertEquals(Types.NCHAR, JdbcType.fromString("NCHAR").toInt());
    assertEquals(Types.NCLOB, JdbcType.fromString("NCLOB").toInt());
    assertEquals(Types.NULL, JdbcType.fromString("NULL").toInt());
    assertEquals(Types.NUMERIC, JdbcType.fromString("NUMERIC").toInt());
    assertEquals(Types.NVARCHAR,
                 JdbcType.fromString("NVARCHAR").toInt());
    assertEquals(Types.OTHER, JdbcType.fromString("OTHER").toInt());
    assertEquals(Types.REAL, JdbcType.fromString("REAL").toInt());
    assertEquals(Types.REF, JdbcType.fromString("REF").toInt());
    assertEquals(Types.ROWID, JdbcType.fromString("ROWID").toInt());
    assertEquals(Types.SMALLINT,
                 JdbcType.fromString("SMALLINT").toInt());
    assertEquals(Types.SQLXML, JdbcType.fromString("SQLXML").toInt());
    assertEquals(Types.STRUCT, JdbcType.fromString("STRUCT").toInt());
    assertEquals(Types.TIME, JdbcType.fromString("TIME").toInt());
    assertEquals(Types.TIMESTAMP,
                 JdbcType.fromString("TIMESTAMP").toInt());
    assertEquals(Types.TINYINT, JdbcType.fromString("TINYINT").toInt());
    assertEquals(Types.VARBINARY,
                 JdbcType.fromString("VARBINARY").toInt());
    assertEquals(Types.VARCHAR, JdbcType.fromString("VARCHAR").toInt());
  }
}
