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

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.concurrent.atomic.AtomicBoolean;

// TODO: Maybe we should use
// DriverManager.getConnection(String,Properties) to avoid most of the
// difficulty of dealing with the URL?

public final class JdbcConnection implements AutoCloseable {
  private final JdbcAddress address_;
  private final Connection connection_;
  private final AtomicBoolean closed_ = new AtomicBoolean(false);

  private UnimplementedException unimplemented() {
    return Jdbc.unimplemented(address_.subprotocol());
  }

  private void executeUpdate(final CharSequence sql)
      throws SQLException {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(sql != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try (final Statement x = connection_.createStatement()) {
      x.executeUpdate(sql.toString());
    }
  }

  public JdbcConnection(final JdbcAddress address) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(address != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    address_ = address;
    try {
      connection_ = DriverManager.getConnection(address_.url());
      try {
        switch (address_.subprotocol()) {

          case MYSQL: {
            executeUpdate("USE "
                          + address_.database().underlyingName());
          } break;

          case POSTGRESQL: {
            // PostgreSQL does not need a "USE" statement because the
            // connection_ is tied to the database via the JDBC URL.
          } break;

          case SQLITE: {
          } break;

          case SQLSERVER: {
            executeUpdate("SET QUOTED_IDENTIFIER ON");
            executeUpdate("USE "
                          + address_.database().underlyingName());
          } break;

          default:
            throw unimplemented();
        }
      } catch (final Throwable e) {
        try {
          connection_.close();
        } catch (final Throwable e2) {
        }
        throw e;
      }
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  @Override
  public final void close() {
    if (!closed_.getAndSet(true)) {
      try {
        connection_.close();
      } catch (final Throwable e) {
      }
    }
  }

  public final JdbcAddress address() {
    return address_;
  }

  public final Connection connection() {
    return connection_;
  }

  //--------------------------------------------------------------------

  public final PreparedStatement
  prepareStreamingStatement(final CharSequence sql) {
    try {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(sql != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final PreparedStatement statement =
          connection().prepareStatement(sql.toString(),
                                        ResultSet.TYPE_FORWARD_ONLY,
                                        ResultSet.CONCUR_READ_ONLY);
      try {
        switch (address().subprotocol()) {
          case MYSQL: {
            statement.setFetchSize(Integer.MIN_VALUE);
          } break;
        }
        return statement;
      } catch (final Throwable e) {
        try {
          statement.close();
        } catch (final Throwable e2) {
        }
        throw e;
      }
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  //--------------------------------------------------------------------
}
