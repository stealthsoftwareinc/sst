/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_crop_short_option_a.h>
#include <sst/sst_crop_short_option_a.h>

#include <sst/sst_is_valued_short_option_a.h>

char * (sst_crop_short_option_a)(
  char * const arg,
  char const * const opt
) {
  if (sst_is_valued_short_option_a(arg, opt)) {
    arg[2] = '\0';
  }
  return arg;
}
