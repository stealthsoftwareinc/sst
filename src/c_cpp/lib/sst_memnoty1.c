/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnoty1.h>
#include <sst/sst_memnoty1.h>

unsigned char (sst_memnoty1)(
  unsigned char const s1,
  unsigned char const s2
) {
  (void)s1;
  return ~(unsigned int)s2;
}
