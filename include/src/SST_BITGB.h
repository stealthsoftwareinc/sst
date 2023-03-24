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

#ifndef SRC_SST_BITGB_H
#define SRC_SST_BITGB_H

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_getbit1.h>
#include <sst/sst_setbit1.h>
#include <stddef.h>

/* end_includes */

#define SST_BITGB(sst_bitGb, sst_bitG1) \
  void (sst_bitGb)( \
    void * const s1, \
    size_t const n1, \
    size_t r1, \
    void const * const s2, \
    size_t const n2, \
    size_t r2, \
    size_t n, \
    size_t r \
  ) { \
    unsigned char * p1 = s1; \
    unsigned char const * p2 = s2; \
    assert(s1 != NULL); \
    assert(s2 != NULL); \
    p1 += n1; \
    p2 += n2; \
    p1 += r1 / CHAR_BIT; \
    p2 += r2 / CHAR_BIT; \
    r1 %= CHAR_BIT; \
    r2 %= CHAR_BIT; \
    p1 += n; \
    p2 += n; \
    p1 += r / CHAR_BIT; \
    p2 += r / CHAR_BIT; \
    r1 += r % CHAR_BIT; \
    r2 += r % CHAR_BIT; \
    p1 += r1 / CHAR_BIT; \
    p2 += r2 / CHAR_BIT; \
    r1 %= CHAR_BIT; \
    r2 %= CHAR_BIT; \
    while (n != 0 || r != 0) { \
      if (r1 != 0) { \
        --r1; \
      } else { \
        --p1; \
        r1 = CHAR_BIT - 1; \
      } \
      if (r2 != 0) { \
        --r2; \
      } else { \
        --p2; \
        r2 = CHAR_BIT - 1; \
      } \
      { \
        sst_bit const x = sst_getbit1(*p2, r2); \
        *p1 = sst_setbit1(*p1, r1, sst_bitG1(x)); \
      } \
      if (r != 0) { \
        --r; \
      } else { \
        --n; \
        r = CHAR_BIT - 1; \
      } \
    } \
  }

#endif
