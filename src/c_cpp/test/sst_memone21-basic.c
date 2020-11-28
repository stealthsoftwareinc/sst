/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitone21.h>
#include <sst/sst_memone21.h>
#include <src/SST_MEMH1_BASIC.h>

SST_MEMH1_BASIC(sst_memone21, sst_bitone21)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
