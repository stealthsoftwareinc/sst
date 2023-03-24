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

#include <sst/sst_RAND_bytes_step.h>
#include <sst/sst_RAND_bytes_step.h>

#include <sst/SST_WITH_SST_RAND_BYTES_STEP.h>

#if SST_WITH_SST_RAND_BYTES_STEP

#include <assert.h>
#include <openssl/rand.h>
#include <stddef.h>
#include <wficmp.h>

int (sst_RAND_bytes_step)(
  unsigned char * buf,
  size_t num,
  int const step
) {
  int r;
  if (num != 0) {
    assert(step > 0);
  } else {
    assert(step >= 0);
  }
  do {
    int k;
    if (WFICMPLT(num, step)) {
      k = num;
    } else {
      k = step;
    }
    r = RAND_bytes(buf, k);
    if (r != 1) {
      return r;
    }
    if (buf != NULL) {
      buf += k;
    }
    num -= k;
  } while (num != 0);
  return r;
}

#endif

typedef int prevent_an_empty_translation_unit;
