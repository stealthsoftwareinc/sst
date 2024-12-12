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

import java.lang.reflect.InvocationTargetException;

public final class DefaultConstructorSupplier<T>
    implements Supplier<T> {

  private final Class<T> clazz_;

  public DefaultConstructorSupplier(final Class<T> clazz) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(clazz != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    clazz_ = clazz;
  }

  @Override
  public T get() {
    try {
      return clazz_.getDeclaredConstructor().newInstance();
    } catch (final IllegalAccessException e) {
      throw new UncheckedException(e);
    } catch (final InstantiationException e) {
      throw new UncheckedException(e);
    } catch (final InvocationTargetException e) {
      throw new UncheckedException(e);
    } catch (final NoSuchMethodException e) {
      throw new UncheckedException(e);
    }
  }
}
