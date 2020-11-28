/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memxgty1.h>
#include <sst/sst_memxgty1.h>

unsigned char (sst_memxgty1)(
  unsigned char const s1,
  unsigned char const s2
) {
  return s1 & ~(unsigned int)s2;
}
