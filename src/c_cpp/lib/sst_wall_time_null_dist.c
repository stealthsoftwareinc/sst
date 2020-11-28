/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
