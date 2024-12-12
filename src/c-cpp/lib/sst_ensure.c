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
 * Defines the
 * <code>::sst_ensure</code>
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

#include <sst/sst_ensure.h>
#include <sst/sst_ensure.h>

/* begin_includes */

#include <sst/sst_realloc.h>
#include <stddef.h>

/* end_includes */

void * (sst_ensure)(
  void * const p,
  size_t * const n,
  size_t const k,
  size_t const s
) {
  size_t const size_max = (size_t)(-1);
  size_t const smooth_n = (p != NULL && n != NULL) ? *n : 0;
  size_t nn = smooth_n;
  if (nn >= s) {
    return p;
  }
  if (k == 0) {
    if (n != NULL) {
      *n = s;
    }
    return p;
  }
  do {
    if (nn == 0) {
      nn = 1;
    } else if (nn == 1) {
      nn = 2;
    } else if (nn <= size_max - nn / 2) {
      nn = nn + nn / 2;
    } else {
      nn = size_max;
    }
  } while (nn < s);
  for (;;) {
    if (nn <= size_max / k) {
      void * const pp = sst_realloc(p, smooth_n * k, nn * k);
      if (pp != NULL) {
        if (n != NULL) {
          *n = nn;
        }
        return pp;
      }
    }
    if (nn == s) {
      return NULL;
    }
    nn = s + (nn - s) / 2;
  }
}
