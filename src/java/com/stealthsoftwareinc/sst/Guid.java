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

import java.util.Arrays;

public final class Guid implements Comparable<Guid>, ToBytes, ToJson {
  private final byte[] bytes_;

  //--------------------------------------------------------------------

  public Guid(final int size) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(size >= 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    bytes_ = new byte[size];
    Rand.cryptoRng().nextBytes(bytes_);
  }

  public Guid() {
    this(16);
  }

  //--------------------------------------------------------------------
  // Comparisons
  //--------------------------------------------------------------------

  @Override
  public final int compareTo(final Guid other) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(other != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final int n = Math.min(bytes_.length, other.bytes_.length);
    for (int i = 0; i < n; ++i) {
      if (bytes_[i] < other.bytes_[i]) {
        return -1;
      }
      if (bytes_[i] > other.bytes_[i]) {
        return 1;
      }
    }
    if (bytes_.length < other.bytes_.length) {
      return -1;
    }
    if (bytes_.length > other.bytes_.length) {
      return 1;
    }
    return 0;
  }

  @Override
  public final boolean equals(final Object other) {
    return other instanceof Guid
        && Arrays.equals(bytes_, ((Guid)other).bytes_);
  }

  @Override
  public final int hashCode() {
    final int n = Math.min(bytes_.length, 4);
    int x = 0;
    for (int i = 0; i < n; ++i) {
      x = (x << 8) | bytes_[i];
    }
    return x;
  }

  //--------------------------------------------------------------------
  // Binary representation
  //--------------------------------------------------------------------

  @Override
  public final byte[] toBytes() {
    return bytes_.clone();
  }

  private Guid(final byte[] src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    bytes_ = src.clone();
  }

  public static final Guid fromBytes(final byte[] src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return new Guid(src);
  }

  //--------------------------------------------------------------------
  // String representation
  //--------------------------------------------------------------------

  @Override
  public final String toString() {
    return Rep.toHex(bytes_);
  }

  private Guid(final CharSequence src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    bytes_ = Rep.fromHex(src);
  }

  public static final Guid fromString(final CharSequence src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return new Guid(src);
  }

  //--------------------------------------------------------------------
  // JSON representation
  //--------------------------------------------------------------------

  @Override
  public final String toJson() {
    return toString();
  }

  private Guid(final Object src,
               final CreateFromJson<Guid> createFromJsonTag) {
    this(Json.expectString(src));
  }

  public static final CreateFromJson<Guid> fromJson() {
    return new CreateFromJson<Guid>() {
      @Override
      public final Guid createFromJson(final Object src) {
        return new Guid(src, this);
      }
    };
  }

  //--------------------------------------------------------------------
}
