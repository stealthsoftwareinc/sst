changequote(`{|', `|}')
ifdef({|make_rules|}, {||}, {|{|
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

import java.math.BigInteger;

public final class Modulus {
  private final BigInteger modulus_;
  private final long modulusLong_;
  private final int modulusInt_;
  private final BigInteger maxValue_;
  private final byte[] maxValueBytes_;
  private final byte topMask_;

  public Modulus(final BigInteger modulus) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(modulus != null);
        SST_ASSERT(modulus.signum() > 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    modulus_ = modulus;
    modulusLong_ = modulus_.longValue();
    modulusInt_ = modulus_.intValue();
    maxValue_ = modulus_.subtract(BigInteger.ONE);
    maxValueBytes_ = maxValueBytes(modulus_);
    topMask_ = topMask(maxValueBytes_[0]);
  }

  public Modulus(final long modulus) {
    this(BigInteger.valueOf(modulus));
  }

  //--------------------------------------------------------------------
  // get
  //--------------------------------------------------------------------
  //
  // Note that these functions will return zero when the modulus is
  // exactly sized to the type. For example, a modulus of 2^32 returns
  // true for valuesFit((Integer)null) and zero for get((Integer)null).
  // This is intentional.
  //

  public final byte get(final Byte dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(valuesFit(dstType));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (byte)modulusInt_;
  }

  public final short get(final Short dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(valuesFit(dstType));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (short)modulusInt_;
  }

  public final int get(final Integer dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(valuesFit(dstType));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return modulusInt_;
  }

  public final long get(final Long dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(valuesFit(dstType));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return modulusLong_;
  }

  public final BigInteger get(final BigInteger dstType) {
    return modulus_;
  }

  //--------------------------------------------------------------------
  // maxValueBytes
  //--------------------------------------------------------------------

  public static final byte[] maxValueBytes(final BigInteger modulus) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(modulus != null);
        SST_ASSERT(modulus.signum() > 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final byte[] x = modulus.subtract(BigInteger.ONE).toByteArray();
    if (x.length == 1 || x[0] != 0) {
      return x;
    }
    final byte[] y = new byte[x.length - 1];
    System.arraycopy(x, 1, y, 0, y.length);
    return y;
  }

  public final byte[] maxValueBytes() {
    return maxValueBytes_.clone();
  }

  //--------------------------------------------------------------------
  // topMask
  //--------------------------------------------------------------------

  private static final byte topMask(final byte maxValueTopByte) {
    final int t = maxValueTopByte & 0xFF;
    if (t == 0) {
      return 0;
    }
    int x = 0xFF;
    while ((t & (x >>> 1)) == t) {
      x >>>= 1;
    }
    return (byte)x;
  }

  public final byte topMask() {
    return topMask_;
  }

  //--------------------------------------------------------------------
  // valueSize
  //--------------------------------------------------------------------

  public static final int valueSize(final long modulus) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(modulus > 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (modulus == 1) {
      return 1;
    }
    int size = 0;
    for (long x = modulus - 1; x != 0; x >>>= 8) {
      ++size;
    }
    return size;
  }

  public static final int valueSize(final BigInteger modulus) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(modulus != null);
        SST_ASSERT(modulus.signum() > 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return maxValueBytes(modulus).length;
  }

  public final int valueSize() {
    return maxValueBytes_.length;
  }

  //--------------------------------------------------------------------
  // valuesFit
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|
    public final boolean valuesFit(final $1 dstType) {
      return valueSize() <= dstType.SIZE / 8;
    }
  |}|})

  F({|Byte|})
  F({|Short|})
  F({|Integer|})
  F({|Long|})

  popdef({|F|})

  {|

  public final boolean valuesFit(final BigInteger dstType) {
    return true;
  }

  //--------------------------------------------------------------------
}

|}|})
