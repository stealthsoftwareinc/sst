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
 * <code>::sst_overlap</code>
 * function.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_OVERLAP_H
#define SST_SST_OVERLAP_H

/* begin_includes */

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

/**
 * Determines whether two objects overlap.
 *
 * @param p
 * a pointer that points to an object or one past the end of an object.
 * If
 * <code>p</code>
 * does not point to an object nor one past the end of an object, then
 * the behavior is undefined.
 * If
 * <code>p</code>
 * points to an object and the object does not contain at least
 * <code>pn</code>
 * bytes, then the behavior is undefined.
 * If
 * <code>p</code>
 * points one past the end of a maximal object and
 * <code>pn</code>
 * is not zero, then the behavior is undefined.
 *
 * @param pn
 * the number of bytes to consider from the object pointed to by
 * <code>p</code>,
 * or zero if
 * <code>p</code>
 * points one past the end of a maximal object
 *
 * @param q
 * a pointer that points to an object or one past the end of an object.
 * If
 * <code>q</code>
 * does not point to an object nor one past the end of an object, then
 * the behavior is undefined.
 * If
 * <code>q</code>
 * points to an object and the object does not contain at least
 * <code>qn</code>
 * bytes, then the behavior is undefined.
 * If
 * <code>q</code>
 * points one past the end of a maximal object and
 * <code>qn</code>
 * is not zero, then the behavior is undefined.
 *
 * @param qn
 * the number of bytes to consider from the object pointed to by
 * <code>q</code>,
 * or zero if
 * <code>q</code>
 * points one past the end of a maximal object
 *
 * @return
 * <code>::SST_TRUE</code>
 * if
 * <code>pn</code>
 * and
 * <code>qn</code>
 * are not zero and the first
 * <code>pn</code>
 * bytes of the object pointed to by
 * <code>p</code>
 * overlap the first
 * <code>qn</code>
 * bytes of the object pointed to by
 * <code>q</code>,
 * or
 * <code>::SST_FALSE</code>
 * if not
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_EXTERN_C SST_DLL_EXPORT sst_bool (sst_overlap)(
  void const *,
  size_t,
  void const *,
  size_t
);

#else

sst_bool sst_overlap(
  void const * p,
  size_t pn,
  void const * q,
  size_t qn
);

#endif

#endif // SST_SST_OVERLAP_H
