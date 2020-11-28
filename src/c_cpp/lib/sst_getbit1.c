/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_getbit1.h>
#include <sst/sst_getbit1.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/sst_bit.h>
#include <sst/sst_status.h>
#include <stdlib.h>

/* end_includes */

sst_bit (sst_getbit1)(
  unsigned char const s1,
  size_t const r1
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (r1 >= CHAR_BIT) {
      assert(!SST_INVALID_ARGUMENT);
      abort();
    }
  }
  #endif
  {
    unsigned int const m = 1U << (CHAR_BIT - 1 - r1);
    return (s1 & m) != 0;
  }
}
