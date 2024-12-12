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

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Buffers</code>
 * Java class.
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import com.stealthsoftwareinc.sst.ConfigH;
import com.stealthsoftwareinc.sst.NegativeArrayIndexStatus;
import com.stealthsoftwareinc.sst.NegativeArraySizeStatus;
import com.stealthsoftwareinc.sst.NegativeListIndexStatus;
import com.stealthsoftwareinc.sst.NegativeListSizeStatus;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.OutOfRangeStatus;
import com.stealthsoftwareinc.sst.OversizeArrayIndexStatus;
import com.stealthsoftwareinc.sst.OversizeListIndexStatus;
import java.nio.ByteBuffer;

/* end_imports */

/**
 * Provides various static methods for working with NIO buffers.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Buffers
{

/**
 * Prevents objects of this class from being constructed.
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

private Buffers(
) {
}

/**
 *
 * @param src
 * the buffer to read from
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final int getUbigAsBytes(
  final ByteBuffer src,
  final int length,
  final byte[] dst
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
    if (length < 0) {
      throw (NegativeListSizeStatus)
        new NegativeListSizeStatus(
          "length is negative"
        ).initCause(null)
      ;
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst is a null reference"
        ).initCause(null)
      ;
    }
    if (length > dst.length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "length is larger than dst.length"
        ).initCause(null)
      ;
    }
    if (length > src.remaining()) {
      throw (OversizeListIndexStatus)
        new OversizeListIndexStatus(
          "there are fewer than length bytes remaining in src"
        ).initCause(null)
      ;
    }
  }
  int i = 0;
  for (int j = 0; j != length; ++j) {
    final byte b = src.get();
    if (i != 0 || b != 0) {
      dst[i] = b;
      ++i;
    }
  }
  return i;
}

/**
 *
 * @param src
 * the buffer to read from
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final int getUbigAsBytes(
  final ByteBuffer src,
  final int length,
  final byte[] dst,
  final int offset
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
    if (length < 0) {
      throw (NegativeListSizeStatus)
        new NegativeListSizeStatus(
          "length is negative"
        ).initCause(null)
      ;
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst is a null reference"
        ).initCause(null)
      ;
    }
    if (offset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "offset is negative"
        ).initCause(null)
      ;
    }
    if (offset > dst.length - length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "offset + length is larger than dst.length"
        ).initCause(null)
      ;
    }
    if (length > src.remaining()) {
      throw (OversizeListIndexStatus)
        new OversizeListIndexStatus(
          "there are fewer than length bytes remaining in src"
        ).initCause(null)
      ;
    }
  }
  int i = 0;
  for (int j = 0; j != length; ++j) {
    final byte b = src.get();
    if (i != 0 || b != 0) {
      dst[offset + i] = b;
      ++i;
    }
  }
  return i;
}

/**
 *
 * @param src
 * the buffer to read from
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final int getUbigAsBytes(
  final ByteBuffer src,
  final int index,
  final int length,
  final byte[] dst,
  final int offset
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
    if (index < 0) {
      throw (NegativeListIndexStatus)
        new NegativeListIndexStatus(
          "index is negative"
        ).initCause(null)
      ;
    }
    if (length < 0) {
      throw (NegativeListSizeStatus)
        new NegativeListSizeStatus(
          "length is negative"
        ).initCause(null)
      ;
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst is a null reference"
        ).initCause(null)
      ;
    }
    if (offset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "offset is negative"
        ).initCause(null)
      ;
    }
    if (offset > dst.length - length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "offset + length is larger than dst.length"
        ).initCause(null)
      ;
    }
    if (index > src.limit() - length) {
      throw (OversizeListIndexStatus)
        new OversizeListIndexStatus(
          "index + length is larger than src.limit()"
        ).initCause(null)
      ;
    }
  }
  int i = 0;
  for (int j = 0; j != length; ++j) {
    final byte b = src.get(index + j);
    if (i != 0 || b != 0) {
      dst[offset + i] = b;
      ++i;
    }
  }
  return i;
}

/**
 * Relative
 * <i>get</i>
 * method for reading an unsigned big integer value as a
 * <code>long</code>.
 *
 * @param src
 * the buffer to read from
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final long getUbigAsLong(
  final ByteBuffer src
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
  }
  return
    Buffers.getUbigAsLong(
      src,
      src.remaining()
    )
  ;
}

/**
 * Relative
 * <i>get</i>
 * method for reading an unsigned big integer value as a
 * <code>long</code>.
 *
 * @param src
 * the buffer to read from
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final long getUbigAsLong(
  final ByteBuffer src,
  final int length
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
    if (length < 0) {
      throw (NegativeListSizeStatus)
        new NegativeListSizeStatus(
          "length is negative"
        ).initCause(null)
      ;
    }
    if (length > src.remaining()) {
      throw (OversizeListIndexStatus)
        new OversizeListIndexStatus(
          "there are fewer than length bytes remaining in src"
        ).initCause(null)
      ;
    }
  }
  final int CHAR_BIT = 8;
  final long limit = (Long.MAX_VALUE >> (CHAR_BIT - 1)) >> 1;
  long v = 0;
  boolean take = false;
  for (int i = 0; i != length; ++i) {
    final int b = src.get() & 0xFF;
    if (take || b != 0) {
      if (v > limit) {
        throw (OutOfRangeStatus)
          new OutOfRangeStatus(
          ).initCause(null)
        ;
      }
      v <<= CHAR_BIT - 1;
      v <<= 1;
      v |= b;
      take = true;
    }
  }
  return v;
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final long getUbigAsLong(
  final byte[] src,
  final int length
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
    if (length < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "length is negative"
        ).initCause(null)
      ;
    }
    if (length > src.length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "length is larger than src.length"
        ).initCause(null)
      ;
    }
  }
  return
    Buffers.getUbigAsLong(
      src,
      0,
      length
    )
  ;
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final long getUbigAsLong(
  final byte[] src,
  final int offset,
  final int length
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
    if (offset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "offset is negative"
        ).initCause(null)
      ;
    }
    if (length < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "length is negative"
        ).initCause(null)
      ;
    }
    if (offset > src.length - length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "offset + length is larger than src.length"
        ).initCause(null)
      ;
    }
  }
  return
    Buffers.getUbigAsLong(
      ByteBuffer.wrap(src, offset, length)
    )
  ;
}

/**
 * Relative
 * <i>get</i>
 * method for reading an unsigned
 * <code>long</code>
 * value as an
 * <code>int</code>.
 *
 * @param src
 * the buffer to read from
 *
 * @return
 * the unsigned
 * <code>long</code>
 * value at
 * <code>src</code>'s
 * current position
 *
 * @throws java.nio.BufferUnderflowException
 * (priority&nbsp;2)
 * if and only if there are fewer than eight bytes remaining
 * in&nbsp;<code>src</code>
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>src</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OutOfRangeStatus
 * (priority&nbsp;3)
 * if and only if the value is larger than
 * <code>{@link java.lang.Integer#MAX_VALUE}</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final int getUlongAsInt(
  final ByteBuffer src
) {
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (src == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "src is a null reference"
        ).initCause(null)
      ;
    }
  }
  final long v = src.getLong();
  if (v < 0) {
    throw (OutOfRangeStatus)
      new OutOfRangeStatus(
        "the value is larger than Integer.MAX_VALUE"
      ).initCause(null)
    ;
  }
  if (v > Integer.MAX_VALUE) {
    throw (OutOfRangeStatus)
      new OutOfRangeStatus(
        "the value is larger than Integer.MAX_VALUE"
      ).initCause(null)
    ;
  }
  return (int)v;
}

}
