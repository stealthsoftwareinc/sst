/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnotx.h>
#include <sst/sst_memnotx.h>

/* begin_includes */

#include <assert.h>
#include <sst/sst_memnotxf.h>
#include <stddef.h>

/* end_includes */

void (sst_memnotx)(
  void * const s1,
  size_t const n1,
  void const * const s2,
  size_t const n2,
  void const * const s3,
  size_t const n3,
  size_t const n
) {
  assert(s1 != NULL);
  assert(s2 != NULL);
  assert(s3 != NULL);
  sst_memnotxf(s1, n1, s2, n2, s3, n3, n);
}