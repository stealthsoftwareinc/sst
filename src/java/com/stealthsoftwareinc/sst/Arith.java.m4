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
import java.math.RoundingMode;

public final class Arith {
  private Arith() {
  }

  //--------------------------------------------------------------------
  // floorSqrt
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public static final $1 floorSqrt(final $1 x) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(x >= 0);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      if (x <= 1) {
        return x;
      }
      $1 a = 1;
      $1 b = x;
      while (a < b) {
        final $1 m = a / 2 + b / 2;
        if (m > x / m) {
          b = m;
        } else if (m * m < x) {
          a = m + 1;
        } else {
          return m;
        }
      }
      return a - 1;
    }

  |}|})

  F({|int|})
  F({|long|})

  popdef({|F|})

  {|

  public static final BigInteger floorSqrt(final BigInteger x) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(x != null);
        SST_ASSERT(x.signum() >= 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (x.compareTo(BigInteger.ONE) <= 0) {
      return x;
    }
    BigInteger a = BigInteger.ONE;
    BigInteger b = x;
    while (a.compareTo(b) < 0) {
      final BigInteger m = a.shiftRight(1).add(b.shiftRight(1));
      final BigInteger mm = m.multiply(m);
      final int c = mm.compareTo(x);
      if (c > 0) {
        b = m;
      } else if (c < 0) {
        a = m.add(BigInteger.ONE);
      } else {
        return m;
      }
    }
    return a.subtract(BigInteger.ONE);
  }

  //--------------------------------------------------------------------
  // isPowerOfTwo
  //--------------------------------------------------------------------

  public static final boolean isPowerOfTwo(final int a) {
    return a > 0 && (a & (a - 1)) == 0;
  }

  public static final boolean isPowerOfTwo(final long a) {
    return a > 0 && (a & (a - 1)) == 0;
  }

  public static final boolean isPowerOfTwo(final BigInteger a) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(a != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return a.signum() > 0
        && a.and(a.subtract(BigInteger.ONE)).signum() == 0;
  }

  //--------------------------------------------------------------------
  // newtonSqrt
  //--------------------------------------------------------------------

  public static final BigDecimal newtonSqrt(final BigDecimal x,
                                            final int scale) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(x != null);
        SST_ASSERT(x.signum() >= 0);
        SST_ASSERT(scale >= 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (x.signum() == 0) {
      return BigDecimal.ZERO;
    }
    final BigDecimal two = BigDecimal.valueOf(2);
    BigDecimal y0;
    BigDecimal y1 = new BigDecimal(Arith.floorSqrt(x.toBigInteger()));
    do {
      if (y1.signum() == 0) {
        y1 = BigDecimal.ONE.scaleByPowerOfTen(-scale);
      }
      y0 = y1;
      y1 = y1.add(x.divide(y1, scale, RoundingMode.HALF_UP))
               .divide(two, scale, RoundingMode.HALF_UP);
    } while (!y1.equals(y0));
    return y1;
  }

  //--------------------------------------------------------------------
  // promoteUnsigned
  //--------------------------------------------------------------------

  public static final int promoteUnsigned(final byte x) {
    return toUnsignedInt(x);
  }

  public static final int promoteUnsigned(final short x) {
    return toUnsignedInt(x);
  }

  public static final int promoteUnsigned(final int x) {
    return x;
  }

  public static final long promoteUnsigned(final long x) {
    return x;
  }

  //--------------------------------------------------------------------
  // toUnsignedBig
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|
    public static final BigInteger toUnsignedBig(final $1 x) {
      return BigInteger.valueOf(toUnsignedLong(x));
    }
  |}|})

  F({|byte|})
  F({|short|})
  F({|int|})

  popdef({|F|})

  {|

  public static final BigInteger toUnsignedBig(final long x) {
    return x < 0 ? BigInteger.valueOf(x - Long.MIN_VALUE).setBit(63) :
                   BigInteger.valueOf(x);
  }

  public static final BigInteger toUnsignedBig(final BigInteger x) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(x != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return x;
  }

  //--------------------------------------------------------------------
  // toUnsignedInt
  //--------------------------------------------------------------------

  public static final int toUnsignedInt(final byte a) {
    return a & 0xFF;
  }

  public static final int toUnsignedInt(final short a) {
    return a & 0xFFFF;
  }

  public static final int toUnsignedInt(final int a) {
    return a;
  }

  public static final int toUnsignedInt(final long a) {
    return (int)a;
  }

  public static final int toUnsignedInt(final BigInteger a) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(a != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return a.intValue();
  }

  //--------------------------------------------------------------------
  // toUnsignedLong
  //--------------------------------------------------------------------

  public static final long toUnsignedLong(final byte a) {
    return a & 0xFF;
  }

  public static final long toUnsignedLong(final short a) {
    return a & 0xFFFF;
  }

  public static final long toUnsignedLong(final int a) {
    return a & 0xFFFFFFFFL;
  }

  public static final long toUnsignedLong(final long a) {
    return a;
  }

  public static final long toUnsignedLong(final BigInteger a) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(a != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return a.longValue();
  }

  //--------------------------------------------------------------------
  // unsignedCmp
  //--------------------------------------------------------------------

  public static final int unsignedCmp(final byte a, final byte b) {
    return Integer.compare(a & 0xFF, b & 0xFF);
  }

  public static final int unsignedCmp(final short a, final short b) {
    return Integer.compare(a & 0xFFFF, b & 0xFFFF);
  }

  public static final int unsignedCmp(final int a, final int b) {
    return Long.compare(a & 0xFFFFFFFFL, b & 0xFFFFFFFFL);
  }

  public static final int unsignedCmp(final long a, final long b) {
    return Long.compare(a + Long.MIN_VALUE, b + Long.MIN_VALUE);
  }

  //--------------------------------------------------------------------
  // unsignedMod
  //--------------------------------------------------------------------

  public static final byte unsignedMod(final byte a, final byte b) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(b != 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (byte)((a & 0xFF) % (b & 0xFF));
  }

  public static final short unsignedMod(final short a, final short b) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(b != 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (short)((a & 0xFFFF) % (b & 0xFFFF));
  }

  public static final int unsignedMod(final int a, final int b) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(b != 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (int)((a & 0xFFFFFFFFL) % (b & 0xFFFFFFFFL));
  }

  public static final long unsignedMod(long a, final long b) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(b != 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (b < 0) {
      return unsignedCmp(a, b) < 0 ? a : a - b;
    }
    if (a >= 0) {
      return a % b;
    }
    if ((b >>> 62) == 0) {
      return (((a >>> 1) % b) * 2 + (a & 1)) % b;
    }
    while (a < 0) {
      a -= b;
    }
    return a;
  }

  //--------------------------------------------------------------------
}

|}|})
