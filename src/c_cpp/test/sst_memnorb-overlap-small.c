/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnor1.h>
#include <sst/sst_memnorb.h>
#include <src/SST_MEMHB_OVERLAP.h>

#define MIN_BYTES 0
#define MAX_BYTES 16
SST_MEMHB_OVERLAP(sst_memnorb, sst_memnor1, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
