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

package com.stealthsoftwareinc.sst;

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import java.util.Map;

public final class JdbcAddress {
  private JdbcSubprotocol subprotocol_;
  private String host_;
  private int port_;
  private String username_;
  private String password_;
  private JdbcName database_;

  private UnimplementedException unimplemented() {
    return Jdbc.unimplemented(subprotocol());
  }

  //--------------------------------------------------------------------

  private void parsePort(final Map<String, ?> src) {
    port_ = Json.getAs(src, "port", port_);
    try {
      if (port_ < 1 || port_ > 65535) {
        throw new JsonException("value out of range");
      }
    } catch (final JsonException e) {
      throw e.addKey("port");
    }
  }

  private void mysqlConstruct(final Map<String, ?> src) {
    host_ = Json.getAs(src, "host", host_);
    parsePort(src);
    username_ = Json.getAs(src, "username", username_);
    password_ = Json.getAs(src, "password", password_);
    database_ = Json.getAs(src, "database", database_.fromJson());
  }

  private void postgresqlConstruct(final Map<String, ?> src) {
    host_ = Json.getAs(src, "host", host_);
    parsePort(src);
    username_ = Json.getAs(src, "username", username_);
    password_ = Json.getAs(src, "password", password_);
    database_ = Json.getAs(src, "database", database_.fromJson());
  }

  //--------------------------------------------------------------------
  // sqlite
  //--------------------------------------------------------------------

  private String sqliteFile_;

  private void sqliteConstruct(final Map<String, ?> src) {
    sqliteFile_ = Json.getAs(src, "file", sqliteFile_);
  }

  private String sqliteUrl() {
    final StringBuilder url = new StringBuilder("jdbc:");
    url.append("sqlite:");
    url.append(sqliteFile_);
    return url.toString();
  }

  //--------------------------------------------------------------------
  // sqlserver
  //--------------------------------------------------------------------
  //
  // * Do not enable selectMethod=cursor, as responseBuffering=adaptive,
  //   which enables adaptive buffering, makes it obsolete. Quoting from
  //   <https://docs.microsoft.com/en-us/sql/connect/jdbc/using-adaptive-buffering>:
  //
  //         Avoid using the connection string property
  //         selectMethod=cursor to allow the application to
  //         process a very large result set. The adaptive
  //         buffering feature allows applications to process
  //         very large forward-only, read-only result sets
  //         without using a server cursor. Note that when you
  //         set selectMethod=cursor, all forward-only,
  //         read-only result sets produced by that connection
  //         are impacted. In other words, if your application
  //         routinely processes short result sets with a few
  //         rows, creating, reading, and closing a server
  //         cursor for each result set will use more resources
  //         on both client-side and server-side than is the
  //         case where the selectMethod is not set to cursor.
  //

  private void sqlserverConstruct(final Map<String, ?> src) {
    host_ = Json.getAs(src, "host", host_);
    parsePort(src);
    if (Json.contains(src, "username")
        || Json.contains(src, "password")) {
      username_ = Json.getAs(src, "username", username_);
      password_ = Json.getAs(src, "password", password_);
    }
    database_ = Json.getAs(src, "database", database_.fromJson());
  }

  private String sqlserverUrl() {
    final StringBuilder s = new StringBuilder();

    s.append("jdbc:sqlserver://");

    Uris.escape(s, host_);
    s.append(":");
    Uris.escape(s, String.valueOf(port_));

    s.append(";databaseName=");
    Uris.escape(s, database_.name());

    if (username_ == null) {
      s.append(";integratedSecurity=true");
    } else {
      s.append(";user=");
      Uris.escape(s, username_);
      s.append(";password=");
      Uris.escape(s, password_);
    }

    s.append(";responseBuffering=adaptive");

    return s.toString();
  }

  //--------------------------------------------------------------------

  private JdbcAddress(
      final Map<String, ?> src,
      final CreateFromJson<JdbcAddress> createFromJsonTag) {
    subprotocol_ = Json.getAs(src, "type", subprotocol_.fromJson());
    switch (subprotocol_) {
      case MYSQL:
        mysqlConstruct(src);
        break;
      case POSTGRESQL:
        postgresqlConstruct(src);
        break;
      case SQLITE:
        sqliteConstruct(src);
        break;
      case SQLSERVER:
        sqlserverConstruct(src);
        break;
      default:
        throw unimplemented();
    }
  }

  private JdbcAddress(
      final Object src,
      final CreateFromJson<JdbcAddress> createFromJsonTag) {
    this(Json.copy(Json.expectObject(src)), createFromJsonTag);
  }

  public static final CreateFromJson<JdbcAddress> fromJson() {
    return new CreateFromJson<JdbcAddress>() {
      @Override
      public final JdbcAddress createFromJson(final Object src) {
        return new JdbcAddress(src, this);
      }
    };
  }

  //--------------------------------------------------------------------

  public final JdbcSubprotocol subprotocol() {
    return subprotocol_;
  }

  public final JdbcName database() {
    return database_;
  }

  //--------------------------------------------------------------------

  private String mysqlUrl() {
    final StringBuilder s = new StringBuilder();
    s.append("jdbc:mysql://");
    Uris.escape(s, host_);
    s.append(":");
    Uris.escape(s, String.valueOf(port_));
    s.append("/");
    Uris.escape(s, database_.name());
    s.append("?user=");
    Uris.escape(s, username_);
    s.append("&password=");
    Uris.escape(s, password_);
    s.append("&serverTimezone=UTC");
    return s.toString();
  }

  //--------------------------------------------------------------------

  private String postgresqlUrl() {
    final StringBuilder s = new StringBuilder();
    s.append("jdbc:postgresql://");
    Uris.escape(s, host_);
    s.append(":");
    Uris.escape(s, String.valueOf(port_));
    s.append("/");
    Uris.escape(s, database_.name());
    s.append("?user=");
    Uris.escape(s, username_);
    s.append("&password=");
    Uris.escape(s, password_);
    s.append("&ssl=true");
    return s.toString();
  }

  //--------------------------------------------------------------------
  // url
  //--------------------------------------------------------------------

  public final String url() {
    switch (subprotocol_) {
      case MYSQL:
        return mysqlUrl();
      case POSTGRESQL:
        return postgresqlUrl();
      case SQLITE:
        return sqliteUrl();
      case SQLSERVER:
        return sqlserverUrl();
      default:
        throw unimplemented();
    }
  }

  //--------------------------------------------------------------------
}
