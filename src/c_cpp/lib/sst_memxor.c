/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memxor.h>
#include <sst/sst_memxor.h>

/* begin_includes */

#include <assert.h>
#include <sst/sst_memxorf.h>
#include <stddef.h>

/* end_includes */

void (sst_memxor)(
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
  sst_memxorf(s1, n1, s2, n2, s3, n3, n);
}