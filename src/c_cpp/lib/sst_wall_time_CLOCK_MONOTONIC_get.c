/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_wall_time_CLOCK_MONOTONIC_get.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_get.h>

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

/* begin_includes */

#include <errno.h>
#include <sst/SST_ENABLE_INVALID_ARGUMENT_CHECKS.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_FAILURE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_SUCCESS.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_live.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_ut.h>
#include <string.h>
#include <time.h>

/* end_includes */

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
