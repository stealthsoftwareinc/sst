/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memcpy1.h>
#include <sst/sst_memcpyf.h>
#include <src/SST_MEMGF_OVERLAP.h>

#define MIN_BYTES 56
#define MAX_BYTES 64
SST_MEMGF_OVERLAP(sst_memcpyf, sst_memcpy1, MIN_BYTES, MAX_BYTES)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
