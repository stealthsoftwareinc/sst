/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitxlty1.h>
#include <sst/sst_bitxltyf.h>
#include <src/SST_BITHF_OVERLAP.h>

#define MIN_BITS 63
#define MAX_BITS 64
SST_BITHF_OVERLAP(sst_bitxltyf, sst_bitxlty1, MIN_BITS, MAX_BITS)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
