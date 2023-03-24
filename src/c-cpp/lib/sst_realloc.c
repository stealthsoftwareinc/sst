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
 * Defines the
 * <code>::sst_realloc</code>
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

#include <sst/sst_realloc.h>
#include <sst/sst_realloc.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_DEAD_MEMORY_FILLING.h>
#include <sst/SST_ENABLE_LIVE_MEMORY_FILLING.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_INVALID_ARRAY_SIZE.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

void * (sst_realloc)(
  void * const p,
  size_t const n,
  size_t const s
) {
  (void)n;
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (p == NULL && n != 0) {
      assert(!SST_INVALID_ARRAY_SIZE);
      abort();
    }
  }
  #endif
  if (p == NULL) {
    void * const pp = realloc(NULL, (s == 0) ? 1 : s);
    if (pp == NULL) {
      return NULL;
    }
    #if (SST_ENABLE_LIVE_MEMORY_FILLING)
    {
      (void)memset(pp, 0x11, s);
    }
    #endif
    return pp;
  }
  #if (SST_ENABLE_DEAD_MEMORY_FILLING)
  {
    void * const pp = realloc(NULL, (s == 0) ? 1 : s);
    if (pp == NULL) {
      return NULL;
    }
    (void)memcpy(pp, p, (s < n) ? s : n);
    (void)memset(p, 0x33, n);
    free(p);
    #if (SST_ENABLE_LIVE_MEMORY_FILLING)
    {
      if (s > n) {
        (void)memset((unsigned char *)pp + n, 0x11, s - n);
      }
    }
    #endif
    return pp;
  }
  #else
  {
    void * const pp = realloc(p, (s == 0) ? 1 : s);
    if (pp == NULL) {
      return NULL;
    }
    #if (SST_ENABLE_LIVE_MEMORY_FILLING)
    {
      if (s > n) {
        (void)memset((unsigned char *)pp + n, 0x11, s - n);
      }
    }
    #endif
    return pp;
  }
  #endif
}
