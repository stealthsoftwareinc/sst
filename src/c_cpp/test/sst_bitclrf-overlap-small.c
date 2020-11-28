/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitclr1.h>
#include <sst/sst_bitclrf.h>
#include <src/SST_BITGF_OVERLAP.h>

#define MIN_BITS 0
#define MAX_BITS 2
SST_BITGF_OVERLAP(sst_bitclrf, sst_bitclr1, MIN_BITS, MAX_BITS)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
