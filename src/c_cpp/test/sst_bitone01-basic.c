/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bit.h>
#include <sst/sst_bitone01.h>
#include <src/SST_BITC1_BASIC.h>

SST_BITC1_BASIC(sst_bitone01)

int main(
  void
) {
  sst_bit const truth = 1;
  return main2(truth);
}
