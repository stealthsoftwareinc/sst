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

import java.math.BigDecimal;
import java.sql.PreparedStatement;
import java.util.List;

public final class Jdbc {
  private Jdbc() {
  }

  public static final UnimplementedException
  unimplemented(final JdbcSubprotocol subprotocol) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(subprotocol != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return new UnimplementedException(
        "The jdbc:" + subprotocol
        + " subprotocol is not fully supported yet.");
  }

  public static final PreparedStatement
  resetParameters(final PreparedStatement statement,
                  final Iterable<Object> parameters) {
    try {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(statement != null);
          SST_ASSERT(parameters != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      statement.clearParameters();
      int i = 0;
      for (final Object parameter : parameters) {
        statement.setObject(++i, parameter);
      }
      return statement;
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  public static final
      String[] formatParameters(final List<Object> parameters,
                                final JdbcSubprotocol subprotocol) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(parameters != null);
        SST_ASSERT(subprotocol != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final String[] ys = new String[parameters.size()];
    for (int i = 0; i != ys.length; ++i) {
      final Object x = parameters.get(i);
      final String y;
      if (x == null) {
        ys[i] = "null";
      } else if (x instanceof Long) {
        ys[i] = ((Long)x).toString();
      } else if (x instanceof BigDecimal) {
        ys[i] = ((BigDecimal)x).toString();
      } else if (x instanceof String) {
        ys[i] = "'" + ((String)x).replace("'", "''") + "'";
      } else {
        throw new UnimplementedException();
      }
    }
    return ys;
  }
}
