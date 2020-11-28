/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memone0.h>
#include <sst/sst_memone01.h>
#include <src/SST_MEMC_DISJOINT.h>

#define MIN_BYTES 0
#define MAX_BYTES 16
SST_MEMC_DISJOINT(sst_memone0, sst_memone01, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
