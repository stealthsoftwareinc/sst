/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_wall_time_CLOCK_MONOTONIC_dist.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_dist.h>

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_SUCCESS.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_live.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_ut.h>
#include <string.h>
#include <time.h>

/* end_includes */

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
