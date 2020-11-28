/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnor1.h>
#include <sst/sst_memnor1.h>

unsigned char (sst_memnor1)(
  unsigned char const s1,
  unsigned char const s2
) {
  return ~(unsigned int)(s1 | s2);
}