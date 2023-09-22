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
 * <code>::sst_is_unvalued_option_w</code>
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

#ifndef SST_SST_IS_UNVALUED_OPTION_W_H
#define SST_SST_IS_UNVALUED_OPTION_W_H

/* begin_includes */

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

/**
 * Determines whether a string is an unvalued option fragment with any
 * name or a specific name.
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
 * The fragment is said to be
 * <i>valued</i>
 * if it contains an
 * &ldquo;<code>=</code>&rdquo;&nbsp;character,
 * or
 * <i>unvalued</i>
 * if not.
 * For example,
 * <code>-<b></b>-foo=bar</code>
 * and
 * <code>-<b></b>-foo</code>
 * are valued and unvalued long option fragments, respectively, and
 * <code>-<b></b>-foo</code>
 * is the name of both.
 * </p>
 * <p>
 * A string is called a
 * <i>short option fragment</i>
 * if it begins with one
 * &ldquo;<code>-</code>&rdquo;&nbsp;character
 * followed by one character except the
 * &ldquo;<code>-</code>&rdquo;&nbsp;character.
 * These two characters are called the
 * <i>name</i>
 * of the fragment.
 * The fragment is said to be
 * <i>valued</i>
 * if the name is followed by one or more characters, or
 * <i>unvalued</i>
 * if not.
 * For example,
 * <code>-xfoo</code>
 * and
 * <code>-x</code>
 * are valued and unvalued short option fragments, respectively, and
 * <code>-x</code>
 * is the name of both.
 * </p>
 * <p>
 * A string is called an
 * <i>option fragment</i>
 * if it is a long option fragment or a short option fragment.
 * Note that a string cannot be a long option fragment and a short
 * option fragment at the same time.
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
 * point to strings that are option fragments with the same name and the
 * <code>arg</code>
 * fragment is unvalued
 * </li>
 * <li>
 * <code>::SST_FALSE</code>
 * if and only if
 * <code>arg</code>
 * is a null pointer,
 * <code>arg</code>
 * or
 * <code>opt</code>
 * points to a string that is not an option fragment, the fragments have
 * different names, or the
 * <code>arg</code>
 * fragment is valued
 * </li>
 * </ul>
 *
 * @modifies
 * nothing
 *
 * @available
 * always
 *
 * @see <code>::sst_is_unvalued_option_a</code>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_EXTERN_C SST_DLL_EXPORT sst_bool (sst_is_unvalued_option_w)(
  wchar_t const *,
  wchar_t const *
);

#else

sst_bool sst_is_unvalued_option_w(
  wchar_t const * arg,
  wchar_t const * opt
);

#endif

#endif // SST_SST_IS_UNVALUED_OPTION_W_H
