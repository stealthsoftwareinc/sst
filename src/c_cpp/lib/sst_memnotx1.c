/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnotx1.h>
#include <sst/sst_memnotx1.h>

unsigned char (sst_memnotx1)(
  unsigned char const s1,
  unsigned char const s2
) {
  (void)s2;
  return ~(unsigned int)s1;
}
