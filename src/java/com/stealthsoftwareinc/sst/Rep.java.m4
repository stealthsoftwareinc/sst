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

import java.io.IOException;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.CharBuffer;

|}ifelse(WITH_NETTY, 1, {|{|
import io.netty.buffer.ByteBuf;
|}|}){|

public final class Rep {
  private Rep() {
  }

  //--------------------------------------------------------------------

  private static RepException integerOutOfRange(final Throwable cause) {
    return new RepException("integer out of range", cause);
  }

  private static RepException integerOutOfRange() {
    return integerOutOfRange(null);
  }

  private static RepException malformedInteger(final Throwable cause) {
    return new RepException("malformed integer", cause);
  }

  private static RepException malformedInteger() {
    return malformedInteger(null);
  }

  //--------------------------------------------------------------------

  private static final class Index { public int i = 0; }

  private static boolean
  parseNegative(final CharSequence s, final Index i, final int n) {
    SST_ASSERT(s != null);
    SST_ASSERT(i != null);
    SST_ASSERT(n == s.length());
    SST_ASSERT(i.i >= 0);
    SST_ASSERT(i.i <= n);
    if (i.i < n) {
      if (s.charAt(i.i) == '-') {
        ++i.i;
        return true;
      }
      if (s.charAt(i.i) == '+') {
        ++i.i;
      }
    }
    return false;
  }

  private static int
  parseBase(final CharSequence s, final Index i, final int n) {
    SST_ASSERT(s != null);
    SST_ASSERT(i != null);
    SST_ASSERT(n == s.length());
    SST_ASSERT(i.i >= 0);
    SST_ASSERT(i.i <= n);
    if (i.i < n && s.charAt(i.i) == '0' && i.i + 1 < n) {
      final char c = s.charAt(i.i + 1);
      if (c == 'b' || c == 'B') {
        i.i += 2;
        return 2;
      }
      if (c == 'o' || c == 'O') {
        i.i += 2;
        return 8;
      }
      if (c == 'x' || c == 'X') {
        i.i += 2;
        return 16;
      }
      if (c >= '0' && c <= '9') {
        // decimal-magnitude forbids a leading zero.
        throw malformedInteger();
      }
    }
    return 10;
  }

  //--------------------------------------------------------------------
  // Converting to fundamental integer types
  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    public static final boolean toInteger(final $1 src,
                                          final Boolean dstType) {
      final byte b = toInteger(src, (Byte)null);
      if (b < 0) {
        throw integerOutOfRange();
      }
      if (b > 1) {
        throw integerOutOfRange();
      }
      return b == 1;
    }

  |}|})

  f({|boolean|})
  f({|byte|})
  f({|short|})
  f({|int|})
  f({|long|})
  f({|BigInteger|})
  f({|float|})
  f({|double|})
  f({|BigDecimal|})
  f({|CharSequence|})

  popdef({|f|})

  pushdef({|f|}, {|{|

    public static final $2 toInteger(final boolean src,
                                     final $1 dstType) {
      return src ? ($2)1 : ($2)0;
    }

    public static final $2 toInteger(final byte src, final $1 dstType) {
      return ($2)src;
    }

    public static final $2 toInteger(final short src,
                                     final $1 dstType) {
      if (src < $1.MIN_VALUE) {
        throw integerOutOfRange();
      }
      if (src > $1.MAX_VALUE) {
        throw integerOutOfRange();
      }
      return ($2)src;
    }

    public static final $2 toInteger(final int src, final $1 dstType) {
      if (src < $1.MIN_VALUE) {
        throw integerOutOfRange();
      }
      if (src > $1.MAX_VALUE) {
        throw integerOutOfRange();
      }
      return ($2)src;
    }

    public static final $2 toInteger(final long src, final $1 dstType) {
      if (src < $1.MIN_VALUE) {
        throw integerOutOfRange();
      }
      if (src > $1.MAX_VALUE) {
        throw integerOutOfRange();
      }
      return ($2)src;
    }

    public static final $2 toInteger(final BigInteger src,
                                     final $1 dstType) {
      SST_ASSERT(src != null);
      if (src.compareTo(BigInteger.valueOf($1.MIN_VALUE)) < 0) {
        throw integerOutOfRange();
      }
      if (src.compareTo(BigInteger.valueOf($1.MAX_VALUE)) > 0) {
        throw integerOutOfRange();
      }
      return ($2)src.longValue();
    }

    public static final $2 toInteger(final float src,
                                     final $1 dstType) {
      return toInteger(BigDecimal.valueOf(src), dstType);
    }

    public static final $2 toInteger(final double src,
                                     final $1 dstType) {
      return toInteger(BigDecimal.valueOf(src), dstType);
    }

    public static final $2 toInteger(final BigDecimal src,
                                     final $1 dstType) {
      SST_ASSERT(src != null);
      try {
        return toInteger(src.toBigIntegerExact(), dstType);
      } catch (final ArithmeticException e) {
        throw malformedInteger(e);
      }
    }

    public static final $2 toInteger(final CharSequence src,
                                     final $1 dstType) {
      SST_ASSERT(src != null);
      final CharSequence s = src;
      final int n = s.length();
      if (n == 4 && s.charAt(0) == 't' && s.charAt(1) == 'r'
          && s.charAt(2) == 'u' && s.charAt(3) == 'e') {
        return ($2)1;
      }
      if (n == 5 && s.charAt(0) == 'f' && s.charAt(1) == 'a'
          && s.charAt(2) == 'l' && s.charAt(3) == 's'
          && s.charAt(4) == 'e') {
        return ($2)0;
      }
      final Index i = new Index();
      final boolean negative = parseNegative(s, i, n);
      final int base = parseBase(s, i, n);
      if (i.i == n) {
        throw malformedInteger();
      }
      final $2 min = $1.MIN_VALUE;
      final $2 max = $1.MAX_VALUE;
      $2 value = ($2)0;
      boolean firstDigit = true;
      for (; i.i != n; ++i.i) {
        if (firstDigit) {
          firstDigit = false;
        } else if (s.charAt(i.i) == '\'' && ++i.i == n) {
          throw malformedInteger();
        }
        final char c = s.charAt(i.i);
        final int digit;
        if (c >= '0' && c <= '0' + Math.min(base - 1, 9)) {
          digit = c - '0';
        } else if (base >= 11 && c >= 'A' && c <= 'A' + (base - 11)) {
          digit = 10 + (c - 'A');
        } else if (base >= 11 && c >= 'a' && c <= 'a' + (base - 11)) {
          digit = 10 + (c - 'a');
        } else {
          throw malformedInteger();
        }
        try {
          if (negative) {
            if (value < min / ($2)base) {
              throw integerOutOfRange();
            }
            value *= ($2)base;
            if (value < min + ($2)digit) {
              throw integerOutOfRange();
            }
            value -= ($2)digit;
          } else {
            if (value > max / ($2)base) {
              throw integerOutOfRange();
            }
            value *= ($2)base;
            if (value > max - ($2)digit) {
              throw integerOutOfRange();
            }
            value += ($2)digit;
          }
        } catch (final RepException e) {
          while (++i.i != n) {
            final char d = s.charAt(i.i);
            if (d >= '0' && d <= '0' + Math.min(base - 1, 9)) {
            } else if (base >= 11 && d >= 'A'
                       && d <= 'A' + (base - 11)) {
            } else if (base >= 11 && d >= 'a'
                       && d <= 'a' + (base - 11)) {
            } else {
              throw malformedInteger();
            }
          }
          throw e;
        }
      }
      return value;
    }

  |}|})

  f({|Byte|}, {|byte|})
  f({|Short|}, {|short|})
  f({|Integer|}, {|int|})
  f({|Long|}, {|long|})

  popdef({|f|})

  {|
  // clang-format on

  //--------------------------------------------------------------------
  // Converting to BigInteger
  //--------------------------------------------------------------------

  public static final BigInteger toInteger(final boolean src,
                                           final BigInteger dstType) {
    return BigInteger.valueOf(src ? 1 : 0);
  }

  public static final BigInteger toInteger(final byte src,
                                           final BigInteger dstType) {
    return BigInteger.valueOf(src);
  }

  public static final BigInteger toInteger(final short src,
                                           final BigInteger dstType) {
    return BigInteger.valueOf(src);
  }

  public static final BigInteger toInteger(final int src,
                                           final BigInteger dstType) {
    return BigInteger.valueOf(src);
  }

  public static final BigInteger toInteger(final long src,
                                           final BigInteger dstType) {
    return BigInteger.valueOf(src);
  }

  public static final BigInteger toInteger(final BigInteger src,
                                           final BigInteger dstType) {
    SST_ASSERT(src != null);
    return src;
  }

  public static final BigInteger toInteger(final float src,
                                           final BigInteger dstType) {
    try {
      return BigDecimal.valueOf(src).toBigIntegerExact();
    } catch (final ArithmeticException e) {
      throw integerOutOfRange(e);
    }
  }

  public static final BigInteger toInteger(final double src,
                                           final BigInteger dstType) {
    try {
      return BigDecimal.valueOf(src).toBigIntegerExact();
    } catch (final ArithmeticException e) {
      throw integerOutOfRange(e);
    }
  }

  public static final BigInteger toInteger(final BigDecimal src,
                                           final BigInteger dstType) {
    SST_ASSERT(src != null);
    try {
      return src.toBigIntegerExact();
    } catch (final ArithmeticException e) {
      throw integerOutOfRange(e);
    }
  }

  public static final BigInteger toInteger(final CharSequence src,
                                           final BigInteger dstType) {
    SST_ASSERT(src != null);
    final CharSequence s = src;
    final int n = s.length();
    if (n == 4 && s.charAt(0) == 't' && s.charAt(1) == 'r'
        && s.charAt(2) == 'u' && s.charAt(3) == 'e') {
      return BigInteger.ONE;
    }
    if (n == 5 && s.charAt(0) == 'f' && s.charAt(1) == 'a'
        && s.charAt(2) == 'l' && s.charAt(3) == 's'
        && s.charAt(4) == 'e') {
      return BigInteger.ZERO;
    }
    final Index i = new Index();
    final boolean negative = parseNegative(s, i, n);
    final int base = parseBase(s, i, n);
    final BigInteger bigBase = BigInteger.valueOf(base);
    if (i.i == n) {
      throw malformedInteger();
    }
    BigInteger value = BigInteger.ZERO;
    boolean firstDigit = true;
    for (; i.i != n; ++i.i) {
      if (firstDigit) {
        firstDigit = false;
      } else if (s.charAt(i.i) == '\'' && ++i.i == n) {
        throw malformedInteger();
      }
      final char c = s.charAt(i.i);
      final int digit;
      if (c >= '0' && c <= '0' + Math.min(base - 1, 9)) {
        digit = c - '0';
      } else if (base >= 11 && c >= 'A' && c <= 'A' + (base - 11)) {
        digit = 10 + (c - 'A');
      } else if (base >= 11 && c >= 'a' && c <= 'a' + (base - 11)) {
        digit = 10 + (c - 'a');
      } else {
        throw malformedInteger();
      }
      final BigInteger bigDigit = BigInteger.valueOf(digit);
      value = value.multiply(bigBase);
      if (negative) {
        value = value.subtract(bigDigit);
      } else {
        value = value.add(bigDigit);
      }
    }
    return value;
  }

  //--------------------------------------------------------------------
  // fromBytes
  //--------------------------------------------------------------------

  |}

  pushdef({|F1|}, {|{|

    public static final $1 fromBytes(final $3 src,
                                     final int off,
                                     final int len,
                                     final $2 T,
                                     final IntegerRep rep,
                                     final ByteOrder endian,
                                     final boolean checked) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          final int capacity = |}$4({|src|}){|;
          SST_ASSERT(capacity > 0);
          SST_ASSERT(off >= 0);
          SST_ASSERT(off < capacity);
          SST_ASSERT(len > 0);
          SST_ASSERT(len <= capacity - off);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final boolean bigEndian = endian == ByteOrder.BIG_ENDIAN;
      switch (rep) {
        case PURE_UNSIGNED: {
          $1 dst = 0;
          final int i0 = checked ? 0 : Math.max(0, len - $2.SIZE / 8);
          for (int i = i0; i < len; ++i) {
            final int j = bigEndian ? i : len - 1 - i;
            final int x = |}$5({|src|}, {|off + j|}){| & 0xFF;
            if (checked) {
              if (dst > ($2.MAX_VALUE >> 8) || x > $2.MAX_VALUE) {
                throw new RepException();
              }
            }
            dst = ($1)((dst << 8) | x);
          }
          return dst;
        } // break;
        case TWOS_COMPLEMENT: {
          $1 dst = 0;
          final int i0 = checked ? 0 : Math.max(0, len - $2.SIZE / 8);
          final int j0 = bigEndian ? 0 : len - 1;
          final int x0 = |}$5({|src|}, {|off + j0|}){| & 0xFF;
          final boolean negative = x0 > 0x7F;
          for (int i = i0; i < len; ++i) {
            final int j = bigEndian ? i : len - 1 - i;
            final int x = |}$5({|src|}, {|off + j|}){| & 0xFF;
            final int y = (negative ? ~x : x) & 0xFF;
            if (checked) {
              if (dst > ($2.MAX_VALUE >> 8) || x > $2.MAX_VALUE) {
                throw new RepException();
              }
            }
            dst = ($1)((dst << 8) | y);
          }
          if (negative) {
            dst = ($1)(-dst - 1);
          }
          return dst;
        } // break;
        default:
          throw new UnimplementedException();
      }
    }

  |}|})

  pushdef({|F9|}, {|{|

    public static final BigInteger fromBytes(final $1 src,
                                             final int off,
                                             final int len,
                                             final BigInteger T,
                                             final IntegerRep rep,
                                             final ByteOrder endian,
                                             final boolean checked,
                                             byte[] buf) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          final int capacity = |}$2({|src|}){|;
          SST_ASSERT(capacity > 0);
          SST_ASSERT(off >= 0);
          SST_ASSERT(off < capacity);
          SST_ASSERT(len > 0);
          SST_ASSERT(len <= capacity - off);
          if (buf != null) {
            SST_ASSERT((Object)buf != (Object)src);
            if (rep == IntegerRep.PURE_UNSIGNED) {
              SST_ASSERT(buf.length - 1 == len);
            } else if (rep == IntegerRep.TWOS_COMPLEMENT) {
              SST_ASSERT(buf.length == len);
            }
          }
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final boolean bigEndian = endian == ByteOrder.BIG_ENDIAN;
      switch (rep) {
        case PURE_UNSIGNED: {
          if (len == Integer.MAX_VALUE) {
            throw new UnimplementedException();
          }
          if (buf == null) {
            buf = new byte[1 + len];
          } else {
            buf[0] = 0;
          }
          if (bigEndian) {
            for (int i = 0; i < len; ++i) {
              buf[1 + i] = (byte)|}$3({|src|}, {|off + i|}){|;
            }
          } else {
            for (int i = 0; i < len; ++i) {
              final int j = len - 1 - i;
              buf[1 + j] = (byte)|}$3({|src|}, {|off + i|}){|;
            }
          }
          return new BigInteger(buf);
        } // break;
        case TWOS_COMPLEMENT: {
          if (buf == null) {
            buf = new byte[len];
          }
          if (bigEndian) {
            for (int i = 0; i < len; ++i) {
              buf[i] = |}$3({|src|}, {|off + i|}){|;
            }
          } else {
            for (int i = 0; i < len; ++i) {
              final int j = len - 1 - i;
              buf[j] = |}$3({|src|}, {|off + i|}){|;
            }
          }
          return new BigInteger(buf);
        } // break;
        default:
          throw new UnimplementedException();
      }
    }

    public static final BigInteger fromBytes(final $1 src,
                                             final int off,
                                             final int len,
                                             final BigInteger T,
                                             final IntegerRep rep,
                                             final ByteOrder endian,
                                             final boolean checked) {
      return fromBytes(src, off, len, T, rep, endian, checked, null);
    }

  |}|})

  pushdef({|F2|}, {|
    F1({|byte|}, {|Byte|}, {|$1|}, {|$2|}, {|$3|})
    F1({|short|}, {|Short|}, {|$1|}, {|$2|}, {|$3|})
    F1({|int|}, {|Integer|}, {|$1|}, {|$2|}, {|$3|})
    F1({|long|}, {|Long|}, {|$1|}, {|$2|}, {|$3|})
    F9({|$1|}, {|$2|}, {|$3|})
  |})

  pushdef({|array_cap|}, {|{|$1.length|}|})
  pushdef({|array_get|}, {|{|$1[$2]|}|})

  pushdef({|ByteBuffer_cap|}, {|{|$1.capacity()|}|})
  pushdef({|ByteBuffer_get|}, {|{|$1.get($2)|}|})

  pushdef({|ByteBuf_cap|}, {|{|$1.capacity()|}|})
  pushdef({|ByteBuf_get|}, {|{|$1.getByte($2)|}|})

  F2({|byte[]|}, {|array_cap|}, {|array_get|})
  F2({|ByteBuffer|}, {|ByteBuffer_cap|}, {|ByteBuffer_get|})
  ifelse(WITH_NETTY, 1, {|
    F2({|ByteBuf|}, {|ByteBuf_cap|}, {|ByteBuf_get|})
  |})

  popdef({|F1|})
  popdef({|F9|})
  popdef({|F2|})
  popdef({|array_cap|})
  popdef({|array_get|})
  popdef({|ByteBuffer_cap|})
  popdef({|ByteBuffer_get|})
  popdef({|ByteBuf_cap|})
  popdef({|ByteBuf_get|})

  {|

  //--------------------------------------------------------------------
  // fromHex
  //--------------------------------------------------------------------

  public static final byte fromHex(final char src) {
    if (src >= '0' && src <= '9') {
      return (byte)(src - '0');
    }
    if (src >= 'A' && src <= 'F') {
      return (byte)(src - 'A' + 10);
    }
    if (src >= 'a' && src <= 'f') {
      return (byte)(src - 'a' + 10);
    }
    throw new RepException("invalid hex digit: "
                           + Json.smartQuote(src));
  }

  public static final ByteBuffer fromHex(final CharBuffer src,
                                         final ByteBuffer dst,
                                         final boolean exact) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
      SST_ASSERT(dst != null);
    }
    if (src.remaining() % 2 != 0) {
      throw new RepException("odd hex length");
    }
    if (dst.remaining() < src.remaining() / 2) {
      throw new BufferOverrunException();
    }
    if (exact && dst.remaining() > src.remaining() / 2) {
      throw new BufferUnderrunException();
    }
    while (src.hasRemaining()) {
      final int x = fromHex(src.get());
      final int y = fromHex(src.get());
      dst.put((byte)((x << 4) | y));
    }
    return dst;
  }

  public static final ByteBuffer fromHex(final CharBuffer src,
                                         final ByteBuffer dst) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
      SST_ASSERT(dst != null);
    }
    return fromHex(src, dst, false);
  }

  public static final byte[] fromHex(final CharBuffer src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
    }
    if (src.remaining() % 2 != 0) {
      throw new RepException("odd hex length");
    }
    final byte[] dst = new byte[src.remaining() / 2];
    fromHex(src, ByteBuffer.wrap(dst), true);
    return dst;
  }

  public static final byte[] fromHex(final CharSequence src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
    }
    return fromHex(CharBuffer.wrap(src));
  }

  //--------------------------------------------------------------------
  // toBytes
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public static final void toBytes($1 src,
                                     byte[] dst,
                                     final int off,
                                     final int len,
                                     final IntegerRep rep,
                                     final ByteOrder endian,
                                     final boolean checkRange) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(off >= 0);
          SST_ASSERT(off < dst.length);
          SST_ASSERT(len > 0);
          SST_ASSERT(len <= dst.length - off);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      switch (rep) {
        case TWOS_COMPLEMENT: {
          if (checkRange) {
            throw new UnimplementedException();
          } else {
            for (int i = 0; i != len; ++i) {
              final int j =
                  endian == ByteOrder.BIG_ENDIAN ? len - 1 - i : i;
              dst[off + j] = (byte)(src & 0xFF);
              src >>>= 8;
            }
          }
        } break;
        default:
          throw new UnimplementedException();
      }
    }

  |}|})

  F({|byte|}, {|Byte|})
  F({|short|}, {|Short|})
  F({|int|}, {|Integer|})
  F({|long|}, {|Long|})

  popdef({|F|})

  {|

  public static final void toBytes(final BigInteger src,
                                   byte[] dst,
                                   final int off,
                                   final int len,
                                   final IntegerRep rep,
                                   final ByteOrder endian,
                                   final boolean checkRange) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
        SST_ASSERT(dst != null);
        SST_ASSERT(off >= 0);
        SST_ASSERT(off < dst.length);
        SST_ASSERT(len > 0);
        SST_ASSERT(len <= dst.length - off);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final boolean bigEndian = endian == ByteOrder.BIG_ENDIAN;
    switch (rep) {
      case TWOS_COMPLEMENT: {
        if (checkRange) {
          throw new UnimplementedException();
        } else {
          final byte[] x = src.toByteArray();
          final byte fill = (byte)(src.signum() < 0 ? 0xFF : 0x00);
          for (int i = 0; i < len; ++i) {
            final int j = bigEndian ? len - 1 - i : i;
            dst[off + j] = i < x.length ? x[x.length - 1 - i] : fill;
          }
        }
      } break;
      default:
        throw new UnimplementedException();
    }
  }

  //--------------------------------------------------------------------
  // toHex
  //--------------------------------------------------------------------

  public static final Appendable toHex(final byte src,
                                       final Appendable dst,
                                       final boolean uppercase)
      throws IOException {
    if (!SST_NDEBUG) {
      SST_ASSERT(dst != null);
    }
    final String digits =
        uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    dst.append(digits.charAt((src >>> 4) & 0xF));
    dst.append(digits.charAt((src >>> 0) & 0xF));
    return dst;
  }

  public static final StringBuilder toHex(final byte src,
                                          final StringBuilder dst,
                                          final boolean uppercase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(dst != null);
    }
    try {
      return (StringBuilder)toHex(src, (Appendable)dst, uppercase);
    } catch (final IOException e) {
      throw new AssertionError("StringBuilder threw an IOException");
    }
  }

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    public static final $1 toHex(final byte src, final $1 dst) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(dst != null);
      }
      return toHex(src, dst, true);
    }

    public static final $1 toHex(final ByteBuffer src,
                                 final $1 dst,
                                 final boolean uppercase) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(src != null);
        SST_ASSERT(dst != null);
      }
      while (src.hasRemaining()) {
        toHex(src.get(), dst, uppercase);
      }
      return dst;
    }

    public static final $1 toHex(final ByteBuffer src,
                                 final $1 dst) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(src != null);
        SST_ASSERT(dst != null);
      }
      return toHex(src, dst, true);
    }

    public static final $1 toHex(final byte[] src,
                                 final int off,
                                 final int len,
                                 final $1 dst,
                                 final boolean uppercase) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(src != null);
        SST_ASSERT(off >= 0);
        SST_ASSERT(off <= src.length);
        SST_ASSERT(len >= 0);
        SST_ASSERT(len <= src.length - off);
        SST_ASSERT(dst != null);
      }
      return toHex(ByteBuffer.wrap(src, off, len), dst, uppercase);
    }

    public static final $1 toHex(final byte[] src,
                                 final int off,
                                 final int len,
                                 final $1 dst) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(src != null);
        SST_ASSERT(off >= 0);
        SST_ASSERT(off <= src.length);
        SST_ASSERT(len >= 0);
        SST_ASSERT(len <= src.length - off);
        SST_ASSERT(dst != null);
      }
      return toHex(src, off, len, dst, true);
    }

    public static final $1 toHex(final byte[] src,
                                 final $1 dst,
                                 final boolean uppercase) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(src != null);
        SST_ASSERT(dst != null);
      }
      return toHex(ByteBuffer.wrap(src), dst, uppercase);
    }

    public static final $1 toHex(final byte[] src,
                                 final $1 dst) $2 {
      if (!SST_NDEBUG) {
        SST_ASSERT(src != null);
        SST_ASSERT(dst != null);
      }
      return toHex(src, dst, true);
    }

  |}|})

  f({|Appendable|}, {|throws IOException|})
  f({|StringBuilder|})

  popdef({|f|})

  {|
  // clang-format on

  public static final String toHex(final byte src,
                                   final boolean uppercase) {
    return toHex(src, new StringBuilder(), uppercase).toString();
  }

  public static final String toHex(final byte src) {
    return toHex(src, true);
  }

  public static final String toHex(final ByteBuffer src,
                                   final boolean uppercase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
    }
    return toHex(src, new StringBuilder(), uppercase).toString();
  }

  public static final String toHex(final ByteBuffer src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
    }
    return toHex(src, true);
  }

  public static final String toHex(final byte[] src,
                                   final int off,
                                   final int len,
                                   final boolean uppercase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
      SST_ASSERT(off >= 0);
      SST_ASSERT(off <= src.length);
      SST_ASSERT(len >= 0);
      SST_ASSERT(len <= src.length - off);
    }
    return toHex(ByteBuffer.wrap(src, off, len), uppercase);
  }

  public static final String toHex(final byte[] src,
                                   final int off,
                                   final int len) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
      SST_ASSERT(off >= 0);
      SST_ASSERT(off <= src.length);
      SST_ASSERT(len >= 0);
      SST_ASSERT(len <= src.length - off);
    }
    return toHex(src, off, len, true);
  }

  public static final String toHex(final byte[] src,
                                   final boolean uppercase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
    }
    return toHex(ByteBuffer.wrap(src), uppercase);
  }

  public static final String toHex(final byte[] src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(src != null);
    }
    return toHex(src, true);
  }

  //--------------------------------------------------------------------
  // toReal
  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|to_primitive_cast|}, {|{|
    public static final $1 toReal(final $3 src, final $2 dstType) {
      return ($1)src;
    }
  |}|})

  pushdef({|to_primitive_1Value|}, {|{|
    public static final $1 toReal(final $3 src, final $2 dstType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toReal(src.$1Value(), dstType);
    }
  |}|})

  pushdef({|to_primitive|}, {|{|

    |}
    to_primitive_cast({|$1|}, {|$2|}, {|char|})
    to_primitive_cast({|$1|}, {|$2|}, {|byte|})
    to_primitive_cast({|$1|}, {|$2|}, {|short|})
    to_primitive_cast({|$1|}, {|$2|}, {|int|})
    to_primitive_cast({|$1|}, {|$2|}, {|long|})
    to_primitive_cast({|$1|}, {|$2|}, {|float|})
    to_primitive_cast({|$1|}, {|$2|}, {|double|})
    {|

    public static final $1 toReal(final boolean src, final $2 dstType) {
      return toReal(src ? 1 : 0, dstType);
    }

    |}
    to_primitive_1Value({|$1|}, {|$2|}, {|BigInteger|})
    to_primitive_1Value({|$1|}, {|$2|}, {|BigDecimal|})
    {|

    public static final $1 toReal(final CharSequence src,
                                  final $2 dstType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      try {
        return $2.valueOf(src.toString());
      } catch (final NumberFormatException e) {
        throw new RepException(e);
      }
    }

  |}|})

  to_primitive({|float|}, {|Float|})
  to_primitive({|double|}, {|Double|})

  popdef({|to_primitive|})
  popdef({|to_primitive_1Value|})
  popdef({|to_primitive_cast|})

  pushdef({|to_BigDecimal_valueOf|}, {|{|
    public static final BigDecimal toReal(final $1 src,
                                          final BigDecimal dstType) {
      try {
        return BigDecimal.valueOf(src);
      } catch (final NumberFormatException e) {
        throw new RepException(e);
      }
    }
  |}|})

  to_BigDecimal_valueOf({|char|})
  to_BigDecimal_valueOf({|byte|})
  to_BigDecimal_valueOf({|short|})
  to_BigDecimal_valueOf({|int|})
  to_BigDecimal_valueOf({|long|})
  to_BigDecimal_valueOf({|float|})
  to_BigDecimal_valueOf({|double|})

  popdef({|to_BigDecimal_valueOf|})

  {|
  // clang-format on

  public static final BigDecimal toReal(final boolean src,
                                        final BigDecimal dstType) {
    return toReal(src ? 1 : 0, dstType);
  }

  public static final BigDecimal toReal(final BigInteger src,
                                        final BigDecimal dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return new BigDecimal(src);
  }

  public static final BigDecimal toReal(final BigDecimal src,
                                        final BigDecimal dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return src;
  }

  public static final BigDecimal toReal(final CharSequence src,
                                        final BigDecimal dstType) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try {
      return new BigDecimal(src.toString());
    } catch (final NumberFormatException e) {
      throw new RepException(e);
    }
  }

  //--------------------------------------------------------------------
  // toString
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public static final Appendable toString(final $1 src,
                                            final Appendable dst)
        throws IOException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      dst.append(src.toString());
      return dst;
    }

    public static final StringBuilder toString(
        final $1 src,
        final StringBuilder dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      try {
        return (StringBuilder)toString(src, (Appendable)dst);
      } catch (final IOException e) {
        SST_ASSERT(e, "StringBuilder threw an IOException");
        throw new AssertionError("StringBuilder threw an IOException");
      }
    }

    public static final String toString(final $1 src) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, new StringBuilder()).toString();
    }

  |}|})

  F({|Byte|})
  F({|Short|})
  F({|Integer|})
  F({|Long|})
  F({|BigInteger|})

  F({|Float|})
  F({|Double|})

  popdef({|F|})

  pushdef({|F|}, {|{|

    public static final Appendable toString(final $1[] src,
                                            final int off,
                                            final int len,
                                            final Appendable dst)
        throws IOException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(off >= 0);
          SST_ASSERT(off <= src.length);
          SST_ASSERT(len >= 0);
          SST_ASSERT(len <= src.length - off);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      dst.append('[');
      for (int i = off; i < off + len; ++i) {
        if (i > 0) {
          dst.append(", ");
        }
        toString(src[i], dst);
      }
      dst.append(']');
      return dst;
    }

    public static final Appendable toString(final $1[] src,
                                            final Appendable dst)
        throws IOException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, 0, src.length, dst);
    }

    public static final StringBuilder toString(
        final $1[] src,
        final int off,
        final int len,
        final StringBuilder dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(off >= 0);
          SST_ASSERT(off <= src.length);
          SST_ASSERT(len >= 0);
          SST_ASSERT(len <= src.length - off);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      try {
        return (StringBuilder)toString(src, off, len, (Appendable)dst);
      } catch (final IOException e) {
        SST_ASSERT(e, "StringBuilder threw an IOException");
        throw new AssertionError("StringBuilder threw an IOException");
      }
    }

    public static final StringBuilder toString(
        final $1[] src,
        final StringBuilder dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, 0, src.length, dst);
    }

    public static final String toString(final $1[] src,
                                        final int off,
                                        final int len) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(off >= 0);
          SST_ASSERT(off <= src.length);
          SST_ASSERT(len >= 0);
          SST_ASSERT(len <= src.length - off);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, off, len, new StringBuilder()).toString();
    }

    public static final String toString(final $1[] src) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, 0, src.length);
    }

  |}|})

  F({|byte|})
  F({|short|})
  F({|int|})
  F({|long|})

  F({|float|})
  F({|double|})

  popdef({|F|})

  pushdef({|F|}, {|{|

    public static final Appendable toString(final $1[] src,
                                            final int off,
                                            final int len,
                                            final Appendable dst)
        throws IOException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          for (int i = 0; i < src.length; ++i) {
            SST_ASSERT(src[i] != null);
          }
          SST_ASSERT(off >= 0);
          SST_ASSERT(off <= src.length);
          SST_ASSERT(len >= 0);
          SST_ASSERT(len <= src.length - off);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      dst.append('[');
      for (int i = off; i < off + len; ++i) {
        if (i > 0) {
          dst.append(", ");
        }
        toString(src[i], dst);
      }
      dst.append(']');
      return dst;
    }

    public static final Appendable toString(final $1[] src,
                                            final Appendable dst)
        throws IOException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          for (int i = 0; i < src.length; ++i) {
            SST_ASSERT(src[i] != null);
          }
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, 0, src.length, dst);
    }

    public static final StringBuilder toString(
        final $1[] src,
        final int off,
        final int len,
        final StringBuilder dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          for (int i = 0; i < src.length; ++i) {
            SST_ASSERT(src[i] != null);
          }
          SST_ASSERT(off >= 0);
          SST_ASSERT(off <= src.length);
          SST_ASSERT(len >= 0);
          SST_ASSERT(len <= src.length - off);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      try {
        return (StringBuilder)toString(src, off, len, (Appendable)dst);
      } catch (final IOException e) {
        SST_ASSERT(e, "StringBuilder threw an IOException");
        throw new AssertionError("StringBuilder threw an IOException");
      }
    }

    public static final StringBuilder toString(
        final $1[] src,
        final StringBuilder dst) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, 0, src.length, dst);
    }

    public static final String toString(final $1[] src,
                                        final int off,
                                        final int len) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
          for (int i = 0; i < src.length; ++i) {
            SST_ASSERT(src[i] != null);
          }
          SST_ASSERT(off >= 0);
          SST_ASSERT(off <= src.length);
          SST_ASSERT(len >= 0);
          SST_ASSERT(len <= src.length - off);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, off, len, new StringBuilder()).toString();
    }

    public static final String toString(final $1[] src) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      return toString(src, 0, src.length);
    }

  |}|})

  F({|Byte|})
  F({|Short|})
  F({|Integer|})
  F({|Long|})
  F({|BigInteger|})

  F({|Float|})
  F({|Double|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------
}

|}|})
