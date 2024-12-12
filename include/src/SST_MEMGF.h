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

#ifndef SRC_SST_MEMGF_H
#define SRC_SST_MEMGF_H

/* begin_includes */

#include <assert.h>
#include <stddef.h>

/* end_includes */

#define SST_MEMGF(sst_memGf, sst_memG1) \
  void (sst_memGf)( \
    void * const s1, \
    size_t const n1, \
    void const * const s2, \
    size_t const n2, \
    size_t n \
  ) { \
    unsigned char * p1 = s1; \
    unsigned char const * p2 = s2; \
    assert(s1 != NULL); \
    assert(s2 != NULL); \
    p1 += n1; \
    p2 += n2; \
    while (n != 0) { \
      *p1 = sst_memG1(*p2); \
      ++p1; \
      ++p2; \
      --n; \
    } \
  }

#endif
