/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memxgey1.h>
#include <sst/sst_memxgeyf.h>
#include <src/SST_MEMHF_OVERLAP.h>

#define MIN_BYTES 56
#define MAX_BYTES 64
SST_MEMHF_OVERLAP(sst_memxgeyf, sst_memxgey1, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
