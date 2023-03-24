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

import java.util.concurrent.ConcurrentMap;

/**
 * Provides static methods for working with maps.
 */

public final class Maps {
  private Maps() {
  }

  //--------------------------------------------------------------------
  // getOrPut
  //--------------------------------------------------------------------

  public static final <K, V> V getOrPut(final ConcurrentMap<K, V> map,
                                        final K key,
                                        final Supplier<V> supplier) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(map != null);
        SST_ASSERT(supplier != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final V a = map.get(key);
    if (a != null) {
      return a;
    }
    final V b = map.putIfAbsent(key, supplier.get());
    if (b != null) {
      return b;
    }
    return map.get(key);
  }

  public static final <K, V> V getOrPut(final ConcurrentMap<K, V> map,
                                        final K key,
                                        final Class<V> valueClass) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(map != null);
        SST_ASSERT(valueClass != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return getOrPut(map,
                    key,
                    new DefaultConstructorSupplier<V>(valueClass));
  }

  //--------------------------------------------------------------------
}

|}|})
