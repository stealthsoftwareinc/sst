/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitone0.h>
#include <sst/sst_bitone0.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

void (sst_bitone0)(
  void * const s1,
  size_t const n1,
  size_t const r1,
  size_t const n,
  size_t const r
) {
  if (s1 == NULL) {
    assert(!SST_NULL_POINTER);
    abort();
  }
  if (n == 0 && r == 0) {
    return;
  }
  {
    size_t const cb = CHAR_BIT;
    size_t const r1q = r1 / cb;
    size_t const r1r = r1 % cb;
    size_t const rq = r / cb;
    size_t const rr = r % cb;
    size_t const eq = (r1r + rr) / cb;
    size_t const er = (r1r + rr) % cb;
    size_t const k = rq + eq + (er != 0);
    unsigned int const um = UCHAR_MAX;
    unsigned char * p1 = s1;
    p1 += n1;
    p1 += r1q;
    if (n < 2 && n + k == 1) {
      *p1 |= ((um << (cb - (n * cb + r))) & um) >> r1r;
    } else {
      *p1 |= um >> r1r;
      p1 += 1;
      if (k == 0) {
        (void)memset(p1, -1, n - 2);
        p1 += n - 2;
      } else if (n == 0) {
        (void)memset(p1, -1, k - 2);
        p1 += k - 2;
      } else {
        (void)memset(p1, -1, n - 1);
        p1 += n - 1;
        (void)memset(p1, -1, k - 1);
        p1 += k - 1;
      }
      if (er == 0) {
        *p1 = um;
      } else {
        *p1 |= um << (cb - er);
      }
    }
  }
}
