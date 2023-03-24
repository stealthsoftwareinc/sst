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

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

// TODO: In Java 8 or later, add a constructor that allows
// CompletableFuture<JdbcConnection>.supplyAsync(f, executor) to be used
// instead of executor.submit(f).

public final class JdbcConnectionFactory<
    F extends Future<JdbcConnection>> implements Supplier<F> {
  private final JdbcAddress address_;
  private final ExecutorService executor_;

  public JdbcConnectionFactory(final JdbcAddress address,
                               final ExecutorService executor) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(address != null);
        SST_ASSERT(executor != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    address_ = address;
    executor_ = executor;
  }

  @Override
  public final F get() {
    @SuppressWarnings("unchecked")
    final F future =
        (F)executor_.submit(new Callable<JdbcConnection>() {
          @Override
          public final JdbcConnection call() {
            return new JdbcConnection(address_);
          }
        });
    return future;
  }
}
