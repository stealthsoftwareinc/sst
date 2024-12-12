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

#include <sst/sst_wall_time_null_dist.h>
#include <sst/sst_wall_time_null_dist.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/sst_wall_time_null.h>
#include <sst/sst_wall_time_null_live.h>
#include <sst/sst_wall_time_null_ut.h>
#include <string.h>

/* end_includes */

double (sst_wall_time_null_dist)(
  sst_wall_time_null const * const t1,
  sst_wall_time_null const * const t2
) {
  if (t1 == NULL) {
    return -1;
  }
  if (t2 == NULL) {
    return -1;
  }
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (
      memcmp(
        &t1->sst_magic,
        &sst_wall_time_null_live,
        sizeof(sst_wall_time_null_live)
      )
    ) {
      assert(!SST_WILD_POINTER);
      return -1;
    }
  }
  #endif
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (
      memcmp(
        &t2->sst_magic,
        &sst_wall_time_null_live,
        sizeof(sst_wall_time_null_live)
      )
    ) {
      assert(!SST_WILD_POINTER);
      return -1;
    }
  }
  #endif
  return -1;
}
