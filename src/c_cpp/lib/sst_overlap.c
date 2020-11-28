/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_overlap.h>
#include <sst/sst_overlap.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <stdlib.h>

/* end_includes */

sst_bool (sst_overlap)(
  void const * const p,
  size_t const pn,
  void const * const q,
  size_t const qn
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (p == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
    if (q == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
  }
  #endif
  if (pn == 0) {
    return SST_FALSE;
  }
  if (qn == 0) {
    return SST_FALSE;
  }
  {
    size_t i;
    for (i = 0; i != pn; ++i) {
      if (q == (unsigned char const *)p + i) {
        return SST_TRUE;
      }
    }
  }
  {
    size_t i;
    for (i = 0; i != qn; ++i) {
      if (p == (unsigned char const *)q + i) {
        return SST_TRUE;
      }
    }
  }
  return SST_FALSE;
}
