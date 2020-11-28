/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnoty1.h>
#include <sst/sst_memnotyf.h>
#include <src/SST_MEMHF_OVERLAP.h>

#define MIN_BYTES 56
#define MAX_BYTES 64
SST_MEMHF_OVERLAP(sst_memnotyf, sst_memnoty1, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
