/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_wall_time_null_get.h>
#include <sst/sst_wall_time_null_get.h>

/* begin_includes */

#include <sst/SST_ALWAYS_FAILS.h>
#include <sst/SST_ENABLE_INVALID_ARGUMENT_CHECKS.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_null.h>
#include <sst/sst_wall_time_null_live.h>
#include <sst/sst_wall_time_null_ut.h>
#include <string.h>

/* end_includes */

sst_status (sst_wall_time_null_get)(
  sst_wall_time_null * const t
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
          &sst_wall_time_null_live,
          sizeof(sst_wall_time_null_live)
        )
      ;
    }
    #endif
  }
  #else
  {
    (void)t;
  }
  #endif
  return SST_ALWAYS_FAILS;
}
