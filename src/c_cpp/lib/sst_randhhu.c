/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_randhhu.h>
#include <sst/sst_randhhu.h>

/* begin_includes */

#include <limits.h>
#include <stdlib.h>

/* end_includes */

unsigned char sst_randhhu(
  void
) {
  unsigned int i;
  unsigned int x = 0;
  for (i = UCHAR_MAX; i != 0; i >>= 15) {
    x = (x << 15) | (rand() & 0x7FFF);
  }
  return x;
}
