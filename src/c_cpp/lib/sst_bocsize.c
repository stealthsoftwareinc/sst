/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bocsize.h>
#include <sst/sst_bocsize.h>

/* begin_includes */

#include <limits.h>
#include <stddef.h>

/* end_includes */

size_t (sst_bocsize)(
  size_t const n2,
  size_t const r2
) {
  size_t const nq = n2 / CHAR_BIT;
  size_t const nr = n2 % CHAR_BIT;
  size_t const rq = r2 / CHAR_BIT;
  size_t const rr = r2 % CHAR_BIT;
  size_t const cq = 8 / CHAR_BIT;
  size_t const cr = 8 % CHAR_BIT;
  size_t const aa = nr * cr + rr;
  size_t const bb = aa / CHAR_BIT + (aa % CHAR_BIT != 0);
  size_t const max = (size_t)(-1);
  if (
    nq * cr > max - n2 * cq ||
    rq + bb > max - n2 * cq - nq * cr
  ) {
    return 0;
  }
  return n2 * cq + nq * cr + rq + bb;
}
