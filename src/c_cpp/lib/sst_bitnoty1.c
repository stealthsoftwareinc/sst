/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_bitnoty1.h>
#include <sst/sst_bitnoty1.h>

#include <sst/sst_bit.h>

sst_bit (sst_bitnoty1)(
  sst_bit const s1,
  sst_bit const s2
) {
  (void)s1;
  return !s2;
}
