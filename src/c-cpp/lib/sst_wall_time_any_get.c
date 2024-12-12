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
 * <code>::sst_wall_time_any_get</code>
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

#include <sst/sst_wall_time_any_get.h>
#include <sst/sst_wall_time_any_get.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_INTERNAL_ERROR_CHECKS.h>
#include <sst/SST_ENABLE_INVALID_ARGUMENT_CHECKS.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/SST_MISSING_CASE.h>
#include <sst/SST_NOT_SUPPORTED.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_WALL_CLOCK_ANY.h>
#include <sst/SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/SST_WALL_CLOCK_MAXVAL.h>
#include <sst/SST_WALL_CLOCK_NULL.h>
#include <sst/SST_WALL_CLOCK_UNKNOWN.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_clock.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_get.h>
#include <sst/sst_wall_time_any.h>
#include <sst/sst_wall_time_any_live.h>
#include <sst/sst_wall_time_any_ut.h>
#include <sst/sst_wall_time_null_get.h>
#include <string.h>

/* end_includes */

sst_status (sst_wall_time_any_get)(
  sst_wall_time_any * const t,
  sst_wall_clock const c
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
          &sst_wall_time_any_live,
          sizeof(sst_wall_time_any_live)
        )
      ;
    }
    #endif
    if (c > SST_WALL_CLOCK_MAXVAL) {
      t->sst_c = SST_WALL_CLOCK_UNKNOWN;
      t->sst_s = SST_INVALID_ARGUMENT;
      return t->sst_s;
    }
    if (c == SST_WALL_CLOCK_ANY) {
      t->sst_c = SST_WALL_CLOCK_UNKNOWN;
      t->sst_s = SST_INVALID_ARGUMENT;
      return t->sst_s;
    }
    if (c == SST_WALL_CLOCK_UNKNOWN) {
      t->sst_c = SST_WALL_CLOCK_UNKNOWN;
      t->sst_s = SST_INVALID_ARGUMENT;
      return t->sst_s;
    }
  }
  #endif
  t->sst_c = c;
  switch (t->sst_c) {
    case SST_WALL_CLOCK_CLOCK_MONOTONIC: {
      #if (SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC)
      {
        t->sst_s =
          sst_wall_time_CLOCK_MONOTONIC_get(
            &t->sst_t.sst_CLOCK_MONOTONIC
          )
        ;
      }
      #else
      {
        t->sst_s = SST_NOT_SUPPORTED;
      }
      #endif
    } break;
    case SST_WALL_CLOCK_NULL: {
      t->sst_s =
        sst_wall_time_null_get(
          &t->sst_t.sst_null
        )
      ;
    } break;
    default: {
      #if (SST_ENABLE_INTERNAL_ERROR_CHECKS)
      {
        assert(!SST_MISSING_CASE);
        t->sst_c = SST_WALL_CLOCK_UNKNOWN;
        t->sst_s = SST_MISSING_CASE;
      }
      #endif
    } break;
  }
  return t->sst_s;
}
