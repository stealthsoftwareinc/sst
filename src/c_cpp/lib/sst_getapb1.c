/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_getapb1.h>
#include <sst/sst_getapb1.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/sst_bit.h>
#include <sst/sst_status.h>
#include <stdlib.h>

/* end_includes */

sst_bit (sst_getapb1)(
  unsigned char const s1,
  size_t const k1,
  size_t const r1
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (k1 == 0) {
      assert(!SST_INVALID_ARGUMENT);
      abort();
    }
    if (k1 > CHAR_BIT) {
      assert(!SST_INVALID_ARGUMENT);
      abort();
    }
    if (r1 >= k1) {
      assert(!SST_INVALID_ARGUMENT);
      abort();
    }
  }
  #endif
  {
    unsigned int const m = 1U << (k1 - 1 - r1);
    return (s1 & m) != 0;
  }
}
