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

//
// Note that a taken-from entry can be reactivated by calling
// entry.pool(p). Pool implementations can use this to enable double
// release assertions by calling entry.take() as the last operation of
// pool.release(entry), and entry.pool(this) as the last operation of
// pool.acquire().
//

public final class PoolEntry<T> implements AutoCloseable {
  private final T object_;
  private Pool<T> pool_;

  public PoolEntry(final T object, final Pool<T> pool) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(pool != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    object_ = object;
    pool_ = pool;
  }

  public final T object() {
    return object_;
  }

  public final Pool<T> pool() {
    return pool_;
  }

  public final PoolEntry<T> pool(final Pool<T> p) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(p != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    pool_ = p;
    return this;
  }

  public final T take() {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(pool_ != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    pool_ = null;
    return object_;
  }

  public final void release() {
    if (pool_ != null) {
      pool_.release(this);
    }
  }

  @Override
  public final void close() {
    release();
  }
}
