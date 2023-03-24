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

#include <sst/sst_wall_time_CLOCK_MONOTONIC_get.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_get.h>

#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/SST_ENABLE_INVALID_ARGUMENT_CHECKS.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_FAILURE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_SUCCESS.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_live.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_ut.h>

#if SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC

#include <errno.h>
#include <string.h>
#include <time.h>

sst_status (sst_wall_time_CLOCK_MONOTONIC_get)(
  sst_wall_time_CLOCK_MONOTONIC * const t
) {
  #if (SST_ENABLE_INVALID_ARGUMENT_CHECKS)
  {
    if (t == NULL) {
      return SST_NULL_POINTER;
    }
    #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
    {
      (void)
        memcpy(
          &t->sst_magic,
          &sst_wall_time_CLOCK_MONOTONIC_live,
          sizeof(sst_wall_time_CLOCK_MONOTONIC_live)
        )
      ;
    }
    #endif
  }
  #endif
  {
    clockid_t const c = CLOCK_MONOTONIC;
    if (clock_gettime(c, &t->sst_t) == 0) {
      t->sst_e = 0;
      t->sst_s = SST_SUCCESS;
    } else {
      t->sst_e = errno;
      switch (t->sst_e) {
        default: {
          t->sst_s = SST_FAILURE;
        } break;
      }
    }
  }
  return t->sst_s;
}

#endif

typedef int prevent_an_empty_translation_unit;
