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

#include <sst/sst_wall_time_any_dist.h>
#include <sst/sst_wall_time_any_dist.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/SST_WALL_CLOCK_NULL.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_dist.h>
#include <sst/sst_wall_time_any.h>
#include <sst/sst_wall_time_any_live.h>
#include <sst/sst_wall_time_any_ut.h>
#include <sst/sst_wall_time_null_dist.h>
#include <string.h>

/* end_includes */

double (sst_wall_time_any_dist)(
  sst_wall_time_any const * const t1,
  sst_wall_time_any const * const t2
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
        &sst_wall_time_any_live,
        sizeof(sst_wall_time_any_live)
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
        &sst_wall_time_any_live,
        sizeof(sst_wall_time_any_live)
      )
    ) {
      assert(!SST_WILD_POINTER);
      return -1;
    }
  }
  #endif
  if (t1->sst_c != t2->sst_c) {
    return -1;
  }
  switch (t1->sst_c) {
    case SST_WALL_CLOCK_CLOCK_MONOTONIC: {
      #if (SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC)
      {
        return
          sst_wall_time_CLOCK_MONOTONIC_dist(
            &t1->sst_t.sst_CLOCK_MONOTONIC,
            &t2->sst_t.sst_CLOCK_MONOTONIC
          )
        ;
      }
      #else
      {
        return -1;
      }
      #endif
    } break;
    case SST_WALL_CLOCK_NULL: {
      return
        sst_wall_time_null_dist(
          &t1->sst_t.sst_null,
          &t2->sst_t.sst_null
        )
      ;
    } break;
    default: {
      return -1;
    } break;
  }
}
