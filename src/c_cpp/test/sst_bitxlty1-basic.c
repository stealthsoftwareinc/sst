/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bit.h>
#include <sst/sst_bitxlty1.h>
#include <src/SST_BITH1_BASIC.h>

SST_BITH1_BASIC(sst_bitxlty1)

int main(
  void
) {
  sst_bit const truth[2][2] = {{0, 1}, {0, 0}};
  unsigned long int const prints = 10;
  return main2(truth, prints);
}
