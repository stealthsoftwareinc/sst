/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_is_unvalued_option_a.h>
#include <sst/sst_is_unvalued_option_a.h>

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_is_unvalued_long_option_a.h>
#include <sst/sst_is_unvalued_short_option_a.h>

sst_bool (sst_is_unvalued_option_a)(
  char const * const arg,
  char const * const opt
) {
  if (sst_is_unvalued_long_option_a(arg, opt)) {
    return SST_TRUE;
  }
  if (sst_is_unvalued_short_option_a(arg, opt)) {
    return SST_TRUE;
  }
  return SST_FALSE;
}
