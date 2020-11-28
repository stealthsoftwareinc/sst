/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitnot.h>
#include <sst/sst_bitnot.h>

/* begin_includes */

#include <assert.h>
#include <sst/sst_bitnotf.h>
#include <stddef.h>

/* end_includes */

void (sst_bitnot)(
  void * const s1,
  size_t const n1,
  size_t const r1,
  void const * const s2,
  size_t const n2,
  size_t const r2,
  size_t const n,
  size_t const r
) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  sst_bitnotf(s1, n1, r1, s2, n2, r2, n, r);
}
