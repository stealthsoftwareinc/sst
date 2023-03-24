dnl
dnl Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
dnl
dnl Permission is hereby granted, free of charge, to any person
dnl obtaining a copy of this software and associated documentation
dnl files (the "Software"), to deal in the Software without
dnl restriction, including without limitation the rights to use,
dnl copy, modify, merge, publish, distribute, sublicense, and/or
dnl sell copies of the Software, and to permit persons to whom the
dnl Software is furnished to do so, subject to the following
dnl conditions:
dnl
dnl The above copyright notice and this permission notice (including
dnl the next paragraph) shall be included in all copies or
dnl substantial portions of the Software.
dnl
dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl OTHER DEALINGS IN THE SOFTWARE.
dnl
dnl SPDX-License-Identifier: MIT
dnl

include(`src/m4/config.m4')

changequote(`{|', `|}')

ifdef({|make_rules|}, {|{|
  |}make_target{|: src/m4/config.m4
|}|}, {|{|

package com.stealthsoftwareinc.sst;

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

public final class FixedPointModContext {
  private final Modulus modulus_;
  private final int scale_;

  private final BigInteger modulusBig_;
  private final BigInteger scalarBig_;
  private final BigInteger unscaledMinBig_;
  private final BigInteger unscaledMaxBig_;

  private final BigDecimal scalarDec_;
  private final BigDecimal unscaledMinDec_;
  private final BigDecimal unscaledMaxDec_;

  private final double scalarDouble_;

  |}

  pushdef({|F|}, {|{|
    private final $1 modulus$2_;
    private final $1 scalar$2_;
    private final $1 unscaledMin$2_;
    private final $1 unscaledMax$2_;
    private final $1 scaledMin$2_;
    private final $1 scaledMax$2_;
  |}|})

  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------

  public FixedPointModContext(final Modulus modulus, final int scale) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(modulus != null);
        SST_ASSERT(scale >= 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }

    modulus_ = modulus;
    scale_ = scale;

    modulusBig_ = modulus_.get((BigInteger)null);
    scalarBig_ = BigInteger.TEN.pow(scale_);
    unscaledMinBig_ = modulusBig_.shiftRight(1).negate();
    unscaledMaxBig_ =
        modulusBig_.subtract(BigInteger.ONE).shiftRight(1);

    scalarDec_ = new BigDecimal(scalarBig_);
    unscaledMinDec_ = new BigDecimal(unscaledMinBig_);
    unscaledMaxDec_ = new BigDecimal(unscaledMaxBig_);

    scalarDouble_ = scalarBig_.doubleValue();

    |}

    pushdef({|F|}, {|{|
      {
        final $2 T = null;
        if (modulus_.valuesFit(T)
            && scalarBig_.compareTo(BigInteger.valueOf(T.MAX_VALUE))
                   <= 0) {
          final $1 m = modulus_.get(T);
          modulus$2_ = m;
          scalar$2_ = ($1)scalarBig_.longValue();
          unscaledMin$2_ = m == 0 ? $2.MIN_VALUE : ($1)(-(m >>> 1));
          unscaledMax$2_ = m == 0 ? $2.MAX_VALUE : ($1)((m - 1) >>> 1);
          scaledMin$2_ = ($1)(unscaledMin$2_ / scalar$2_);
          scaledMax$2_ = ($1)(unscaledMax$2_ / scalar$2_);
        } else {
          modulus$2_ = 0;
          scalar$2_ = 0;
          unscaledMin$2_ = 0;
          unscaledMax$2_ = 0;
          scaledMin$2_ = 0;
          scaledMax$2_ = 0;
        }
      }
    |}|})

    F({|int|}, {|Integer|})
    F({|long|}, {|Long|})

    popdef({|F|})

    {|
  }

  //--------------------------------------------------------------------

  private final RuntimeException notRepresentableUnderModulus(
      final String src) {
    return new RuntimeException("Value " + src + " * " + scalarBig_
                                + " is not representable under modulus "
                                + modulusBig_ + ".");
  }

  |}

  pushdef({|F|}, {|{|
    private final RuntimeException notRepresentableAs(
        final String src,
        final $2 dstType) {
      return new RuntimeException("Value " + src + " / " + scalarBig_
                                  + " is not representable in $1.");
    }
  |}|})

  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})
  F({|BigInteger|}, {|BigInteger|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------
  // Fundamental encode and decode methods
  //--------------------------------------------------------------------

  |}

  pushdef({|F1|}, {|{|

    public final $3 encode(final $1 src,
                           final $4 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(dstType));
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      if (src < 0) {
        if (checked && src < scaledMin$4_) {
          throw notRepresentableUnderModulus(src + "");
        }
        return ($3)(src * scalar$4_ + modulus$4_);
      }
      if (checked && src > scaledMax$4_) {
        throw notRepresentableUnderModulus(src + "");
      }
      return ($3)(src * scalar$4_);
    }

    public final $3 decode(final $1 src,
                           final $4 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(($2)null));
          SST_ASSERT(modulus$2_ == 0
                     || Arith.unsignedCmp(src, modulus$2_) < 0);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      if (src == 0) {
        return 0;
      }
      if (checked && scalar$2_ == 0) {
        throw notRepresentableAs(src + "", dstType);
      }
      final $1 x;
      if (Arith.unsignedCmp(src, unscaledMax$2_) <= 0) {
        x = src;
      } else {
        x = ($1)(src - modulus$2_);
      }
      if (checked && x % scalar$2_ != 0) {
        throw notRepresentableAs(src + "", dstType);
      }
      final $1 y = ($1)(x / scalar$2_);
      if (checked && y < $4.MIN_VALUE) {
        throw notRepresentableAs(src + "", dstType);
      }
      if (checked && y > $4.MAX_VALUE) {
        throw notRepresentableAs(src + "", dstType);
      }
      return ($3)y;
    }

  |}|})

  pushdef({|F2|}, {|
    F1({|$1|}, {|$2|}, {|int|}, {|Integer|})
    F1({|$1|}, {|$2|}, {|long|}, {|Long|})
  |})

  F2({|int|}, {|Integer|})
  F2({|long|}, {|Long|})

  popdef({|F2|})
  popdef({|F1|})

  {|

  public final BigInteger encode(final BigInteger src,
                                 final BigInteger dstType,
                                 final boolean checked) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final BigInteger x = src.multiply(scalarBig_);
    if (x.signum() < 0) {
      if (checked && x.compareTo(unscaledMinBig_) < 0) {
        throw notRepresentableUnderModulus(src + "");
      }
      return x.add(modulusBig_);
    }
    if (checked && x.compareTo(unscaledMaxBig_) > 0) {
      throw notRepresentableUnderModulus(src + "");
    }
    return x;
  }

  public final BigInteger decode(final BigInteger src,
                                 final BigInteger dstType,
                                 final boolean checked) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
        SST_ASSERT(src.signum() >= 0);
        SST_ASSERT(src.compareTo(modulusBig_) < 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final BigInteger x;
    if (src.compareTo(unscaledMaxBig_) > 0) {
      x = src.subtract(modulusBig_);
    } else {
      x = src;
    }
    if (!checked) {
      return x.divide(scalarBig_);
    }
    final BigInteger[] dr = x.divideAndRemainder(scalarBig_);
    if (dr[1].signum() != 0) {
      throw notRepresentableAs(src + "", dstType);
    }
    return dr[0];
  }

  |}

  pushdef({|F|}, {|{|

    public final $1 encode(final BigDecimal src,
                           final $2 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(dstType));
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      BigInteger dst = src.scaleByPowerOfTen(scale_).toBigInteger();
      if (dst.signum() < 0) {
        if (checked && dst.compareTo(unscaledMinBig_) < 0) {
          throw notRepresentableUnderModulus(src + "");
        }
        dst = dst.add(modulusBig_);
      } else if (checked && dst.compareTo(unscaledMaxBig_) > 0) {
        throw notRepresentableUnderModulus(src + "");
      }
      return Rep.toInteger(dst, dstType);
    }

  |}|})

  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})
  F({|BigInteger|}, {|BigInteger|})

  popdef({|F|})

  {|

  public final BigDecimal decode(final BigInteger src,
                                 final BigDecimal dstType,
                                 final boolean checked) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
        SST_ASSERT(src.signum() >= 0);
        SST_ASSERT(src.compareTo(modulusBig_) < 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return new BigDecimal(src.compareTo(unscaledMaxBig_) <= 0 ?
                              src :
                              src.subtract(modulusBig_))
        .scaleByPowerOfTen(-scale_);
  }

  |}

  pushdef({|F|}, {|{|

    public final BigInteger encode(final $1 src,
                                   final BigInteger dstType,
                                   final boolean checked) {
      return encode(BigInteger.valueOf(src), dstType, checked);
    }

    public final BigInteger decode(final $1 src,
                                   final BigInteger dstType,
                                   final boolean checked) {
      return decode(Arith.toUnsignedBig(src), dstType, checked);
    }

    public final BigDecimal decode(final $1 src,
                                   final BigDecimal dstType,
                                   final boolean checked) {
      return decode(Arith.toUnsignedBig(src), dstType, checked);
    }

    public final $1 encode(final BigInteger src,
                           final $2 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(dstType));
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      if (checked
          && src.compareTo(BigInteger.valueOf($2.MIN_VALUE)) < 0) {
        throw notRepresentableUnderModulus(src + "");
      }
      if (checked
          && src.compareTo(BigInteger.valueOf($2.MAX_VALUE)) > 0) {
        throw notRepresentableUnderModulus(src + "");
      }
      return encode(($1)src.longValue(), dstType, checked);
    }

    public final $1 decode(final BigInteger src,
                           final $2 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(src.signum() >= 0);
          SST_ASSERT(src.compareTo(modulusBig_) < 0);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return Rep.toInteger(decode(src, (BigInteger)null, checked),
                           dstType);
    }

  |}|})

  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})

  popdef({|F|})

  pushdef({|F|}, {|{|

    public final $3 encode(final $1 src,
                           final $4 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(dstType));
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final double x = src * scalarDouble_;
      if (x < 0) {
        if (checked && x < unscaledMin$4_) {
          throw notRepresentableUnderModulus(src + "");
        }
        return ($3)(($3)x + modulus$4_);
      }
      if (checked && x > unscaledMax$4_) {
        throw notRepresentableUnderModulus(src + "");
      }
      return ($3)x;
    }

    public final $1 decode(final $3 src,
                           final $2 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(($4)null));
          SST_ASSERT(modulus$4_ == 0
                     || Arith.unsignedCmp(src, modulus$4_) < 0);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      if (Arith.unsignedCmp(src, unscaledMax$4_) <= 0) {
        return ($1)(src / scalarDouble_);
      }
      return ($1)((unscaledMin$4_
                   + (Arith.promoteUnsigned(src) - unscaledMax$4_ - 1))
                  / scalarDouble_);
    }

  |}|})

  F({|double|}, {|Double|}, {|int|}, {|Integer|})
  F({|double|}, {|Double|}, {|long|}, {|Long|})

  popdef({|F|})

  pushdef({|F|}, {|{|

    public final BigInteger encode(final $1 src,
                                   final BigInteger dstType,
                                   final boolean checked) {
      return encode(BigDecimal.valueOf(src), dstType, checked);
    }

    public final $1 decode(final BigInteger src,
                           final $2 dstType,
                           final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(src.signum() >= 0);
          SST_ASSERT(src.compareTo(modulusBig_) < 0);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return ($1)((src.compareTo(unscaledMaxBig_) <= 0 ?
                       src :
                       src.subtract(modulusBig_))
                      .doubleValue()
                  / scalarDouble_);
    }

  |}|})

  F({|double|}, {|Double|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------
  //
  // For information about which ResultSet getter methods should be used
  // to retrieve which java.sql.Types types, see the following:
  //
  //     * JDBC 4.1 Specification Table B-6 (page 196)
  //     * JDBC 4.2 Specification Table B-6 (pages 198-201)
  //     * JDBC 4.3 Specification Table B-6 (pages 198-201)
  //

  |}

  pushdef({|F|}, {|{|

    public final $1 encode(final ResultSet resultSet,
                           final int columnIndex,
                           final JdbcType columnType,
                           final $2 dstType,
                           final boolean checked) throws SQLException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(dstType));
          SST_ASSERT(resultSet != null);
          final ResultSetMetaData m = resultSet.getMetaData();
          SST_ASSERT(columnIndex >= 1);
          SST_ASSERT(columnIndex <= m.getColumnCount());
          SST_ASSERT(columnType != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      switch (columnType) {
        case BIT:
        case BOOLEAN:
        case TINYINT:
        case SMALLINT:
        case INTEGER:
          return encode(resultSet.getInt(columnIndex),
                        dstType,
                        checked);
        case BIGINT:
          return encode(resultSet.getLong(columnIndex),
                        dstType,
                        checked);
        case REAL:
        case FLOAT:
        case DOUBLE:
          return encode(resultSet.getDouble(columnIndex),
                        dstType,
                        checked);
        case DECIMAL:
        case NUMERIC:
          return encode(resultSet.getBigDecimal(columnIndex),
                        dstType,
                        checked);
      }
      throw new ImpossibleException("Column type " + columnType
                                    + " is not supported.");
    }

  |}|})

  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})
  F({|BigInteger|}, {|BigInteger|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------
  // The encodeSquare method
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public final $1 encodeSquare(final int src,
                                 final $2 dstType,
                                 final boolean checked) {
      return encode((long)src * src, dstType, checked);
    }

    public final $1 encodeSquare(final long src,
                                 final $2 dstType,
                                 final boolean checked) {
      return encodeSquare(BigInteger.valueOf(src), dstType, checked);
    }

    public final $1 encodeSquare(final BigInteger src,
                                 final $2 dstType,
                                 final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return encode(src.multiply(src), dstType, checked);
    }

    public final $1 encodeSquare(final double src,
                                 final $2 dstType,
                                 final boolean checked) {
      return encode(src * src, dstType, checked);
    }

    public final $1 encodeSquare(final BigDecimal src,
                                 final $2 dstType,
                                 final boolean checked) {
      return encode(src.multiply(src), dstType, checked);
    }

    public final $1 encodeSquare(final ResultSet resultSet,
                                 final int columnIndex,
                                 final JdbcType columnType,
                                 final $2 dstType,
                                 final boolean checked)
        throws SQLException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(modulus_.valuesFit(dstType));
          SST_ASSERT(resultSet != null);
          final ResultSetMetaData m = resultSet.getMetaData();
          SST_ASSERT(columnIndex >= 1);
          SST_ASSERT(columnIndex <= m.getColumnCount());
          SST_ASSERT(columnType != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      switch (columnType) {
        case BIT:
        case BOOLEAN:
        case TINYINT:
        case SMALLINT:
        case INTEGER:
          return encodeSquare(resultSet.getInt(columnIndex),
                              dstType,
                              checked);
        case BIGINT:
          return encodeSquare(resultSet.getLong(columnIndex),
                              dstType,
                              checked);
        case REAL:
        case FLOAT:
        case DOUBLE:
          return encodeSquare(resultSet.getDouble(columnIndex),
                              dstType,
                              checked);
        case DECIMAL:
        case NUMERIC:
          return encodeSquare(resultSet.getBigDecimal(columnIndex),
                              dstType,
                              checked);
      }
      throw new ImpossibleException("Column type " + columnType
                                    + " is not supported.");
    }

  |}|})

  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})
  F({|BigInteger|}, {|BigInteger|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------
  // modulus
  //--------------------------------------------------------------------

  public final Modulus modulus() {
    return modulus_;
  }

  //--------------------------------------------------------------------
}

|}|})
