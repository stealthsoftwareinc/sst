/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memone1.h>
#include <sst/sst_memoneb.h>
#include <src/SST_MEMG_DISJOINT.h>

#define MIN_BYTES 0
#define MAX_BYTES 16
SST_MEMG_DISJOINT(sst_memoneb, sst_memone1, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
