changequote(`{|', `|}')
ifdef({|make_rules|}, {||}, {|{|
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

import java.math.BigInteger;
import java.util.List;
import java.util.Random;
import java.nio.ByteOrder;

public final class RandModContext {
  private static final int DEFAULT_RAND_BUF_SIZE = 4096;

  private final Modulus modulus_;
  private final byte[] maxValue_;
  private final byte chopMask_;
  private final byte[] valueBuf_;
  private final byte[] randBuf_;
  private int randBufPos_;

  public RandModContext(final BigInteger modulus,
                        final int randBufSize) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(modulus != null);
        SST_ASSERT(modulus.compareTo(BigInteger.ZERO) > 0);
        SST_ASSERT(randBufSize > 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    modulus_ = new Modulus(modulus);
    maxValue_ = modulus_.maxValueBytes();
    chopMask_ = modulus_.topMask();
    valueBuf_ = new byte[1 + maxValue_.length];
    randBuf_ = new byte[Math.max(randBufSize / maxValue_.length, 1)
                        * maxValue_.length];
    randBufPos_ = randBuf_.length;
  }

  public RandModContext(final BigInteger modulus) {
    this(modulus, DEFAULT_RAND_BUF_SIZE);
  }

  public RandModContext(final long modulus, final int randBufSize) {
    this(BigInteger.valueOf(modulus), randBufSize);
  }

  public RandModContext(final long modulus) {
    this(modulus, DEFAULT_RAND_BUF_SIZE);
  }

  //--------------------------------------------------------------------
  // valueSize
  //--------------------------------------------------------------------

  public final int valueSize() {
    return maxValue_.length;
  }

  //--------------------------------------------------------------------
  // valuesFit
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public final boolean valuesFit(final $1 dstType) {
      return modulus_.valuesFit(dstType);
    }

  |}|})

  F({|Byte|})
  F({|Short|})
  F({|Integer|})
  F({|Long|})

  popdef({|F|})

  {|

  public final boolean valuesFit(final BigInteger dstType) {
    return modulus_.valuesFit(dstType);
  }

  //--------------------------------------------------------------------
  // modulus
  //--------------------------------------------------------------------

  public final Modulus modulus() {
    return modulus_;
  }

  //--------------------------------------------------------------------
  // discardUntilNext
  //--------------------------------------------------------------------

  private void discardUntilNext(final Random src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
discard:
    while (true) {
      if (randBufPos_ == randBuf_.length) {
        src.nextBytes(randBuf_);
        randBufPos_ = 0;
      }
      randBuf_[randBufPos_] &= chopMask_;
      for (int i = 0; i != maxValue_.length; ++i) {
        final int a = randBuf_[randBufPos_ + i] & 0xFF;
        final int b = maxValue_[i] & 0xFF;
        if (a < b) {
          break;
        }
        if (a > b) {
          randBufPos_ += maxValue_.length;
          continue discard;
        }
      }
      break;
    }
  }

  //--------------------------------------------------------------------
  // gen
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public final $1 gen(final Random src, final $2 dstType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(maxValue_.length <= $2.SIZE / 8);
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      discardUntilNext(src);
      $1 x = 0;
      for (int i = 0; i != maxValue_.length; ++i) {
        x = ($1)((x << 8) | (randBuf_[randBufPos_++] & 0xFF));
      }
      return x;
    }

    public final $1 gen(final $2 dstType) {
      return gen(Rand.cryptoRng(), dstType);
    }

  |}|})

  F({|byte|}, {|Byte|})
  F({|int|}, {|Integer|})
  F({|short|}, {|Short|})
  F({|long|}, {|Long|})

  popdef({|F|})

  {|

  public final BigInteger gen(final Random src,
                              final BigInteger dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    discardUntilNext(src);
    System.arraycopy(randBuf_,
                     randBufPos_,
                     valueBuf_,
                     1,
                     maxValue_.length);
    randBufPos_ += maxValue_.length;
    return new BigInteger(valueBuf_);
  }

  public final BigInteger gen(final BigInteger dstType) {
    return gen(Rand.cryptoRng(), dstType);
  }

  |}

  pushdef({|F|}, {|{|

    public final void gen(final Random src,
                          final $1[] dst,
                          final int dstPos,
                          final int dstLen) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.length);
          SST_ASSERT(dstLen >= 0);
          SST_ASSERT(dstLen <= dst.length - dstPos);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      for (int i = dstPos; i != dstPos + dstLen; ++i) {
        dst[i] = gen(src, ($2)null);
      }
    }

    public final void gen(final $1[] dst,
                          final int dstPos,
                          final int dstLen) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.length);
          SST_ASSERT(dstLen >= 0);
          SST_ASSERT(dstLen <= dst.length - dstPos);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(Rand.cryptoRng(), dst, dstPos, dstLen);
    }

    public final void gen(final Random src,
                          final $1[] dst,
                          final int dstPos) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.length);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(src, dst, dstPos, dst.length - dstPos);
    }

    public final void gen(final $1[] dst, final int dstPos) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.length);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(Rand.cryptoRng(), dst, dstPos);
    }

    public final void gen(final Random src, final $1[] dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(src, dst, 0);
    }

    public final void gen(final $1[] dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(Rand.cryptoRng(), dst);
    }

  |}|})

  F({|byte|}, {|Byte|})
  F({|int|}, {|Integer|})
  F({|short|}, {|Short|})
  F({|long|}, {|Long|})
  F({|Byte|}, {|Byte|})
  F({|Integer|}, {|Integer|})
  F({|Short|}, {|Short|})
  F({|Long|}, {|Long|})
  F({|BigInteger|}, {|BigInteger|})

  popdef({|F|})

  pushdef({|F|}, {|{|

    public final void gen(final Random src,
                          final List<$1> dst,
                          final $1 dstType,
                          final int dstPos,
                          final int dstLen) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.size());
          SST_ASSERT(dstLen >= 0);
          SST_ASSERT(dstLen <= dst.size() - dstPos);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      for (int i = dstPos; i != dstPos + dstLen; ++i) {
        dst.set(i, gen(src, ($1)null));
      }
    }

    public final void gen(final List<$1> dst,
                          final $1 dstType,
                          final int dstPos,
                          final int dstLen) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.size());
          SST_ASSERT(dstLen >= 0);
          SST_ASSERT(dstLen <= dst.size() - dstPos);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(Rand.cryptoRng(), dst, dstType, dstPos, dstLen);
    }

    public final void gen(final Random src,
                          final List<$1> dst,
                          final $1 dstType,
                          final int dstPos) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.size());
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(src, dst, dstType, dstPos, dst.size() - dstPos);
    }

    public final void gen(final List<$1> dst,
                          final $1 dstType,
                          final int dstPos) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(dstPos >= 0);
          SST_ASSERT(dstPos <= dst.size());
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(Rand.cryptoRng(), dst, dstType, dstPos);
    }

    public final void gen(final Random src,
                          final List<$1> dst,
                          final $1 dstType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(src, dst, dstType, 0);
    }

    public final void gen(final List<$1> dst, final $1 dstType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      gen(Rand.cryptoRng(), dst, dstType);
    }

  |}|})

  F({|Byte|})
  F({|Integer|})
  F({|Short|})
  F({|Long|})
  F({|BigInteger|})

  popdef({|F|})

  {|

  public final void gen(final Random src,
                        final byte[] dst,
                        final int dstPos,
                        final int dstLen,
                        final ByteOrder byteOrder) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
        SST_ASSERT(dst != null);
        SST_ASSERT(dstPos >= 0);
        SST_ASSERT(dstPos <= dst.length);
        SST_ASSERT(dstLen >= 0);
        SST_ASSERT(dstLen <= dst.length - dstPos);
        SST_ASSERT((dstLen - dstPos) % valueSize() == 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    for (int i = dstPos; i != dstPos + dstLen; i += valueSize()) {
      discardUntilNext(src);
      if (byteOrder == ByteOrder.BIG_ENDIAN) {
        System.arraycopy(randBuf_, randBufPos_, dst, i, valueSize());
        randBufPos_ += valueSize();
      } else {
        for (int j = 0; j != valueSize(); ++j) {
          dst[i + (valueSize() - 1 - j)] = randBuf_[randBufPos_++];
        }
      }
    }
  }

  //--------------------------------------------------------------------
}

|}|})
