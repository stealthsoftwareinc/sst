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

#include <sst/sst_wall_time_CLOCK_MONOTONIC_dist.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_dist.h>

#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_SUCCESS.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_live.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_ut.h>

#if SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC

#include <assert.h>
#include <string.h>
#include <time.h>

double (sst_wall_time_CLOCK_MONOTONIC_dist)(
  sst_wall_time_CLOCK_MONOTONIC const * const t1,
  sst_wall_time_CLOCK_MONOTONIC const * const t2
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
        &sst_wall_time_CLOCK_MONOTONIC_live,
        sizeof(sst_wall_time_CLOCK_MONOTONIC_live)
      )
    ) {
      assert(!SST_WILD_POINTER);
      return -1;
    }
  }
  #endif
  if (t1->sst_s != SST_SUCCESS) {
    return -1;
  }
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (
      memcmp(
        &t2->sst_magic,
        &sst_wall_time_CLOCK_MONOTONIC_live,
        sizeof(sst_wall_time_CLOCK_MONOTONIC_live)
      )
    ) {
      assert(!SST_WILD_POINTER);
      return -1;
    }
  }
  #endif
  if (t2->sst_s != SST_SUCCESS) {
    return -1;
  }
  {
    double const d =
      ((double)t1->sst_t.tv_sec - t2->sst_t.tv_sec) +
      (t1->sst_t.tv_nsec - t2->sst_t.tv_nsec) / 1000000000.0
    ;
    return d < 0 ? -d : d;
  }
}

#endif

typedef int prevent_an_empty_translation_unit;
