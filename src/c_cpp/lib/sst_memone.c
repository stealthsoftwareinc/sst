/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memone.h>
#include <sst/sst_memone.h>

/* begin_includes */

#include <assert.h>
#include <sst/sst_memonef.h>
#include <stddef.h>

/* end_includes */

void (sst_memone)(
  void * const s1,
  size_t const n1,
  void const * const s2,
  size_t const n2,
  size_t const n
) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  sst_memonef(s1, n1, s2, n2, n);
}
