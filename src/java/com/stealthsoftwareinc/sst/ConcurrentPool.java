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

import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

public final class ConcurrentPool<T> implements Pool<T> {
  private final Queue<PoolEntry<T>> queue_;
  private final Supplier<T> factory_;

  public ConcurrentPool(final Class<T> type) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(type != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    queue_ = new ConcurrentLinkedQueue<PoolEntry<T>>();
    factory_ = new DefaultConstructorSupplier<T>(type);
  }

  public ConcurrentPool(final Supplier<T> factory) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(factory != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    queue_ = new ConcurrentLinkedQueue<PoolEntry<T>>();
    factory_ = factory;
  }

  @Override
  public PoolEntry<T> acquire() {
    final PoolEntry<T> entry = queue_.poll();
    if (entry != null) {
      if (!SST_NDEBUG) {
        entry.pool(this);
      }
      return entry;
    }
    return new PoolEntry<T>(factory_.get(), this);
  }

  @Override
  public void release(final PoolEntry<T> entry) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(entry != null);
        SST_ASSERT(entry.pool() == this);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    queue_.add(entry);
    if (!SST_NDEBUG) {
      entry.take();
    }
  }
}
