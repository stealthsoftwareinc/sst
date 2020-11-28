/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_memnot1.h>
#include <sst/sst_memnot1.h>

unsigned char (sst_memnot1)(
  unsigned char const s1
) {
  return ~(unsigned int)s1;
}
