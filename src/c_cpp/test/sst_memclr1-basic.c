/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitclr1.h>
#include <sst/sst_memclr1.h>
#include <src/SST_MEMG1_BASIC.h>

SST_MEMG1_BASIC(sst_memclr1, sst_bitclr1)

int main(
  void
) {
  unsigned long int const prints = 10;
  unsigned long int const trials = 1;
  return main2(prints, trials);
}
