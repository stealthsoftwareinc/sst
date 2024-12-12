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

#include <sst/sst_ocbsize.h>
#include <sst/sst_ocbsize.h>

/* begin_includes */

#include <limits.h>
#include <stddef.h>

/* end_includes */

size_t (sst_ocbsize)(
  size_t const n2,
  size_t const r2
) {
  size_t const nq = n2 / 8;
  size_t const nr = n2 % 8;
  size_t const rq = r2 / 8;
  size_t const rr = r2 % 8;
  size_t const cq = CHAR_BIT / 8;
  size_t const cr = CHAR_BIT % 8;
  size_t const aa = nr * cr + rr;
  size_t const bb = aa / 8 + (aa % 8 != 0);
  size_t const max = (size_t)(-1);
  if (
    n2 > max / cq ||
    nq * cr > max - n2 * cq ||
    rq + bb > max - n2 * cq - nq * cr
  ) {
    return 0;
  }
  return n2 * cq + nq * cr + rq + bb;
}
