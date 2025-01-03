/*
 * Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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
 * <code>::sst_strchr</code>
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

#ifndef SST_SST_STRCHR_H
#define SST_SST_STRCHR_H

/* begin_includes */

#include <limits.h>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <string.h>

/* end_includes */

/**
 * Locates the first occurrence of a character in a null-terminated
 * string.
 * <p>
 * This function is like the
 * <code>strchr</code>
 * function, but it uses the
 * <code>char</code>&nbsp;type
 * instead of the
 * <code>int</code>&nbsp;type
 * for the
 * <code>c</code>&nbsp;parameter,
 * as it is arguable whether the range of the
 * <code>char</code>&nbsp;type
 * is guaranteed to be a subrange of the range of the
 * <code>int</code>&nbsp;type.
 * If the range of the
 * <code>char</code>&nbsp;type
 * is indeed a subrange of the range of the
 * <code>int</code>&nbsp;type,
 * which should almost always be true in practice, then this function
 * will additionally be defined as a function-like macro that uses the
 * <code>strchr</code>
 * function.
 * The macro can be suppressed by using parentheses around the function
 * name when calling it.
 * </p>
 *
 * @param s
 * a pointer to a null-terminated string to search.
 * If
 * <code>s</code>
 * is a null pointer or does not point to a null-terminated string, or
 * if another thread modifies the string while this function is being
 * called, then the behavior is undefined.
 * This function never modifies the string.
 *
 * @param c
 * a character to search for
 *
 * @return
 * <ul>
 * <li>
 * a null pointer if and only if
 * <code>c</code>
 * is not the null character and does not occur in the string pointed to
 * by&nbsp;<code>s</code>
 * </li>
 * <li>
 * a pointer to the null terminator of the string pointed to
 * by&nbsp;<code>s</code>
 * if and only if
 * <code>c</code>
 * is the null character
 * </li>
 * <li>
 * a pointer to the first occurrence
 * of&nbsp;<code>c</code>
 * in the string pointed to
 * by&nbsp;<code>s</code>
 * if and only if
 * <code>c</code>
 * occurs in the string
 * </li>
 * </ul>
 *
 * @available
 * always
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

SST_EXTERN_C SST_DLL_EXPORT char * (sst_strchr)(
  char const *,
  char
);

#else

char * sst_strchr(
  char const * s,
  char c
);

#if (CHAR_MAX <= INT_MAX)
  #define sst_strchr(s, c) strchr((s), (char)(c))
#endif

#endif

#endif // SST_SST_STRCHR_H
