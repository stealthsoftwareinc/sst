/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitnor1.h>
#include <sst/sst_bitnorb.h>
#include <src/SST_BITHB_OVERLAP.h>

#define MIN_BITS 0
#define MAX_BITS 2
SST_BITHB_OVERLAP(sst_bitnorb, sst_bitnor1, MIN_BITS, MAX_BITS)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
