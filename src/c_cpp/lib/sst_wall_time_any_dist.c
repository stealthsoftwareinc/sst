/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_wall_time_any_dist.h>
#include <sst/sst_wall_time_any_dist.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
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
      #if (SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC)
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
