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

#include <sst/sst_jmemset.h>
#include <sst/sst_jmemset.h>

#include <sst/SST_WITH_SST_JMEMSET.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_NEGATIVE_ARRAY_SIZE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>

#if SST_WITH_SST_JMEMSET

#include <assert.h>
#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <wficmp.h>

void * (sst_jmemset)(
  void * const s,
  int const c,
  jsize n
) {
  size_t const size_max = (size_t)(-1);
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (s == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
    if (n < 0) {
      assert(!SST_NEGATIVE_ARRAY_SIZE);
      abort();
    }
  }
  #endif
  {
    unsigned char * p = s;
    while (WFICMPGT(n, size_max)) {
      (void)memset(p, c, size_max);
      p += size_max;
      n -= size_max;
    }
    (void)memset(p, c, n);
  }
  return s;
}

#endif

typedef int prevent_an_empty_translation_unit;
