/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memclr0.h>
#include <sst/sst_memclr01.h>
#include <src/SST_MEMC_DISJOINT.h>

#define MIN_BYTES 56
#define MAX_BYTES 64
SST_MEMC_DISJOINT(sst_memclr0, sst_memclr01, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
