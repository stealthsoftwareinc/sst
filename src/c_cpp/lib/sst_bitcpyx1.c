/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitcpyx1.h>
#include <sst/sst_bitcpyx1.h>

#include <sst/sst_bit.h>

sst_bit (sst_bitcpyx1)(
  sst_bit const s1,
  sst_bit const s2
) {
  (void)s2;
  return !!s1;
}
