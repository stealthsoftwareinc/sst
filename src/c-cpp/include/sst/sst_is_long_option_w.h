/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_is_long_option_w</code>
 * function.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_IS_LONG_OPTION_W_H
#define SST_SST_IS_LONG_OPTION_W_H

/* begin_includes */

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

/**
 * Determines whether a string is a long option fragment with any name
 * or a specific name.
 * <p>
 * A string is called a
 * <i>long option fragment</i>
 * if it begins with two
 * &ldquo;<code>-</code>&rdquo;&nbsp;characters.
 * The longest leading substring that does not contain an
 * &ldquo;<code>=</code>&rdquo;&nbsp;character
 * is called the
 * <i>name</i>
 * of the fragment.
 * For example,
 * <code>-<b></b>-foo=bar</code>
 * and
 * <code>-<b></b>-foo</code>
 * are long option fragments, and
 * <code>-<b></b>-foo</code>
 * is the name of both.
 * </p>
 *
 * @param arg
 * the string to check.
 * If
 * <code>arg</code>
 * is not a null pointer and does not point to a string, or if another
 * thread modifies the string while this function is being called, then
 * the behavior is undefined.
 * This function never modifies the string.
 *
 * @param opt
 * the name to check for.
 * If
 * <code>opt</code>
 * is not a null pointer and does not point to a string, or if another
 * thread modifies the string while this function is being called, then
 * the behavior is undefined.
 * If
 * <code>opt</code>
 * is a null pointer and
 * <code>arg</code>
 * is not, then
 * <code>opt</code>
 * is implicitly adjusted to the value of
 * <code>arg</code>.
 * This function never modifies the string.
 *
 * @return
 * <ul>
 * <li>
 * <code>::SST_TRUE</code>
 * if and only if
 * <code>arg</code>
 * and
 * <code>opt</code>
 * point to strings that are long option fragments with the same name
 * </li>
 * <li>
 * <code>::SST_FALSE</code>
 * if and only if
 * <code>arg</code>
 * is a null pointer,
 * <code>arg</code>
 * or
 * <code>opt</code>
 * points to a string that is not a long option fragment, or the
 * fragments have different names
 * </li>
 * </ul>
 *
 * @modifies
 * nothing
 *
 * @available
 * always
 *
 * @see <code>::sst_is_long_option_a</code>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * <ol>
 * <li>
 * The following calls return
 * <code>::SST_TRUE</code>:
 * @code{.c}
 * sst_is_long_option_w(L"--foo", NULL);
 * sst_is_long_option_w(L"--foo", L"--foo");
 * sst_is_long_option_w(L"--foo", L"--foo=bar");
 * sst_is_long_option_w(L"--foo=bar", NULL);
 * sst_is_long_option_w(L"--foo=bar", L"--foo");
 * sst_is_long_option_w(L"--foo=bar", L"--foo=bar");
 * sst_is_long_option_w(L"--foo=bar", L"--foo=baz");
 * @endcode
 * </li>
 * <li>
 * The following calls return
 * <code>::SST_FALSE</code>:
 * @code{.c}
 * sst_is_long_option_w(NULL, NULL);
 * sst_is_long_option_w(NULL, L"foo");
 * sst_is_long_option_w(NULL, L"--foo");
 * sst_is_long_option_w(NULL, L"--foo=bar");
 * sst_is_long_option_w(L"foo", NULL);
 * sst_is_long_option_w(L"foo", L"foo");
 * sst_is_long_option_w(L"foo", L"--foo");
 * sst_is_long_option_w(L"foo", L"--foo=bar");
 * sst_is_long_option_w(L"--foo", L"foo");
 * sst_is_long_option_w(L"--foo", L"--bar");
 * sst_is_long_option_w(L"--foo", L"--bar=baz");
 * sst_is_long_option_w(L"--foo=bar", L"foo");
 * sst_is_long_option_w(L"--foo=bar", L"--baz");
 * sst_is_long_option_w(L"--foo=bar", L"--baz=bar");
 * @endcode
 * </li>
 * </ol>
 */

#ifndef SST_DOXYGEN

SST_EXTERN_C SST_DLL_EXPORT sst_bool (sst_is_long_option_w)(
  wchar_t const *,
  wchar_t const *
);

#else

sst_bool sst_is_long_option_w(
  wchar_t const * arg,
  wchar_t const * opt
);

#endif

#endif // #ifndef SST_SST_IS_LONG_OPTION_W_H
