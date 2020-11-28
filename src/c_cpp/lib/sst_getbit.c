/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_getbit.h>
#include <sst/sst_getbit.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_getbit1.h>
#include <stddef.h>

/* end_includes */

sst_bit (sst_getbit)(
  void const * const s1,
  size_t const n1,
  size_t const r1
) {
  unsigned char const * const p1 = s1;
  size_t const r1n = r1 / CHAR_BIT;
  size_t const r1r = r1 % CHAR_BIT;
  assert(s1 != NULL);
  return sst_getbit1(*(p1 + n1 + r1n), r1r);
}
