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

#include <sst/sst_bitclr0.h>
#include <sst/sst_bitclr0.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

void (sst_bitclr0)(
  void * const s1,
  size_t const n1,
  size_t const r1,
  size_t const n,
  size_t const r
) {
  if (s1 == NULL) {
    assert(!SST_NULL_POINTER);
    abort();
  }
  if (n == 0 && r == 0) {
    return;
  }
  {
    size_t const cb = CHAR_BIT;
    size_t const r1q = r1 / cb;
    size_t const r1r = r1 % cb;
    size_t const rq = r / cb;
    size_t const rr = r % cb;
    size_t const eq = (r1r + rr) / cb;
    size_t const er = (r1r + rr) % cb;
    size_t const k = rq + eq + (er != 0);
    unsigned int const um = UCHAR_MAX;
    unsigned char * p1 = s1;
    p1 += n1;
    p1 += r1q;
    if (n < 2 && n + k == 1) {
      *p1 &= ~(((um << (cb - (n * cb + r))) & um) >> r1r);
    } else {
      *p1 &= ~(um >> r1r);
      p1 += 1;
      if (k == 0) {
        (void)memset(p1, 0, n - 2);
        p1 += n - 2;
      } else if (n == 0) {
        (void)memset(p1, 0, k - 2);
        p1 += k - 2;
      } else {
        (void)memset(p1, 0, n - 1);
        p1 += n - 1;
        (void)memset(p1, 0, k - 1);
        p1 += k - 1;
      }
      if (er == 0) {
        *p1 = 0;
      } else {
        *p1 &= ~(um << (cb - er));
      }
    }
  }
}
