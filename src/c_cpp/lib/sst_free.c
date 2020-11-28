/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_free</code>
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

#include <sst/sst_free.h>
#include <sst/sst_free.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_ENABLE_DEAD_MEMORY_FILLING.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_INVALID_ARRAY_SIZE.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

void (sst_free)(
  void * const p,
  size_t const n
) {
  (void)n;
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (p == NULL && n != 0) {
      assert(!SST_INVALID_ARRAY_SIZE);
      abort();
    }
  }
  #endif
  if (p == NULL) {
    return;
  }
  #if (SST_ENABLE_DEAD_MEMORY_FILLING)
  {
    (void)memset(p, 0x33, n);
  }
  #endif
  free(p);
}
