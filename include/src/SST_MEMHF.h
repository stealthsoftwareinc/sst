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

#ifndef SRC_SST_MEMHF_H
#define SRC_SST_MEMHF_H

/* begin_includes */

#include <assert.h>
#include <stddef.h>

/* end_includes */

#define SST_MEMHF(sst_memHf, sst_memH1) \
  void (sst_memHf)( \
    void * const s1, \
    size_t const n1, \
    void const * const s2, \
    size_t const n2, \
    void const * const s3, \
    size_t const n3, \
    size_t n \
  ) { \
    unsigned char * p1 = s1; \
    unsigned char const * p2 = s2; \
    unsigned char const * p3 = s3; \
    assert(s1 != NULL); \
    assert(s2 != NULL); \
    assert(s3 != NULL); \
    p1 += n1; \
    p2 += n2; \
    p3 += n3; \
    while (n != 0) { \
      *p1 = sst_memH1(*p2, *p3); \
      ++p1; \
      ++p2; \
      ++p3; \
      --n; \
    } \
  }

#endif
