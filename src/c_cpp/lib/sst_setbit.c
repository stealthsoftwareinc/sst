/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_setbit.h>
#include <sst/sst_setbit.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_setbit1.h>
#include <stddef.h>

/* end_includes */

void (sst_setbit)(
  void * const s1,
  size_t const n1,
  size_t const r1,
  sst_bit const s2
) {
  unsigned char * const p1 = s1;
  size_t const r1n = r1 / CHAR_BIT;
  size_t const r1r = r1 % CHAR_BIT;
  assert(s1 != NULL);
  *(p1 + n1 + r1n) = sst_setbit1(*(p1 + n1 + r1n), r1r, s2);
}
