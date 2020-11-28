/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memclr0.h>
#include <sst/sst_memclr0.h>

/* begin_includes */

#include <assert.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

void (sst_memclr0)(
  void * const s1,
  size_t const n1,
  size_t const n
) {
  unsigned char * const p1 = s1;
  if (p1 == NULL) {
    assert(!SST_NULL_POINTER);
    abort();
  }
  if (n == 0) {
    return;
  }
  (void)memset(p1 + n1, 0, n);
}
