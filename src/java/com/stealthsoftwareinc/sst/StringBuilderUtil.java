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

/**
 * The StringBuilderUtil static class is a collection of helper functions
 * to transform StringBuilders in ways that it does not natively support.
 */
public class StringBuilderUtil {
  
  /**
   * Replaces all occurences of a string with the given replacement, starting
   * at the given index, and going until the end. All parameters should not
   * be null, and the search key should not be an empty string.
   *
   * @param builder "this" StringBuilder.
   * @param search The string to search for.
   * @param repacement the string to replace instances of the search string.
   * @param from The index from which to start replacing.
   * @return "this" StringBuilder.
   */
  public static StringBuilder replaceAllFrom(StringBuilder builder,
    String search, String replacement, int from) {
    int idx = builder.indexOf(search, from);
    while(idx >= 0) {
      // StringBuilder handles differing lengths already.
      builder.replace(idx, idx + search.length(), replacement);
      idx = builder.indexOf(search, idx + replacement.length());
    }
    return builder;
  }

  /**
   * Replaces all occurences of a string with the given replacement.
   * All parameters should not be null, and the search key should not be an
   * empty string.
   *
   * This is a convenience for
   * {@code StringBuilderUtil.replaceAllFrom(builder, search, replacement, 0) }
   *
   * @param builder "this" StringBuilder.
   * @param search The string to search for.
   * @param repacement the string to replace instances of the search string.
   * @return "this" StringBuilder.
   */
  public static StringBuilder replaceAll(StringBuilder builder, String search,
    String replacement) {
      return StringBuilderUtil.replaceAllFrom(builder, search, replacement, 0);
  }
}
