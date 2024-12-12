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

import com.stealthsoftwareinc.sst.ConfigH;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import com.stealthsoftwareinc.sst.InvalidOperationStatus;
import com.stealthsoftwareinc.sst.NegativeArrayIndexStatus;
import com.stealthsoftwareinc.sst.NegativeArraySizeStatus;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.OversizeArrayIndexStatus;
import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.security.SecureRandom;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

/**
 * Provides various static methods for random number generation.
 *
 * When looking at the code for this class, you may notice that certain
 * temporary arrays seem to be wasteful.
 * This is because Java's
 * <code>{@link java.util.Random}</code>
 * class cannot fill an array slice with random bytes.
 * It can only fill an entire array.
 * This forces us to be wasteful in certain situations where we could
 * otherwise reuse temporaries.
 */

public final class Rand {
  private Rand() {
  }

  //--------------------------------------------------------------------
  // cryptoRng
  //--------------------------------------------------------------------

  private static final ThreadLocal<Random> cryptoRng_ =
      new ThreadLocal<Random>() {
        @Override
        protected Random initialValue() {
          return null;
        }
      };

  public static final Random cryptoRng() {
    Random r = cryptoRng_.get();
    if (r == null) {
      r = new SecureRandom();
      cryptoRng_.set(r);
    }
    return r;
  }

  //--------------------------------------------------------------------

  public static final Random defaultSrc() {
    return new SecureRandom();
  }

  public static final int defaultMaxMemory() {
    return 1 * 1024 * 1024;
  }

  //--------------------------------------------------------------------
  // Generating random bytes into a ByteBuffer
  //--------------------------------------------------------------------

  public static final void bytes(final Random src,
                                 final ByteBuffer dst,
                                 final int dstLength,
                                 final int maxMemory) {
    if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
      if (dst == null) {
        throw(NullPointerStatus) new NullPointerStatus("dst == null")
            .initCause(null);
      }
      if (dst.isReadOnly()) {
        throw(InvalidOperationStatus) new InvalidOperationStatus(
            "dst.isReadOnly()")
            .initCause(null);
      }
      if (dstLength > dst.remaining()) {
        throw(OversizeArrayIndexStatus) new OversizeArrayIndexStatus(
            "dstLength > dst.remaining()")
            .initCause(null);
      }
    }
    if (src == null) {
      bytes(defaultSrc(), dst, dstLength, maxMemory);
      return;
    }
    if (maxMemory < 0) {
      bytes(src, dst, dstLength, defaultMaxMemory());
      return;
    }
    final int nMax = Math.max(maxMemory, 1);
    int i = 0;
    if (dstLength - i >= nMax) {
      final int n = nMax;
      final byte[] xs = new byte[n];
      do {
        src.nextBytes(xs);
        dst.put(xs);
        i += n;
      } while (dstLength - i >= nMax);
    }
    if (dstLength - i != 0) {
      final int n = dstLength - i;
      final byte[] xs = new byte[n];
      src.nextBytes(xs);
      dst.put(xs);
      i += n;
    }
  }

  public static final void
  bytes(final Random src, final ByteBuffer dst, final int dstLength) {
    bytes(src, dst, dstLength, defaultMaxMemory());
  }

  public static final void bytes(final Random src,
                                 final ByteBuffer dst) {
    if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
      if (dst == null) {
        throw(NullPointerStatus) new NullPointerStatus("dst == null")
            .initCause(null);
      }
    }
    bytes(src, dst, dst.remaining());
  }

  //--------------------------------------------------------------------
}

|}|})
