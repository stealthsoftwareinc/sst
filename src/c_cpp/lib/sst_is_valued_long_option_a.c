/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_is_valued_long_option_a.h>
#include <sst/sst_is_valued_long_option_a.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_is_long_option_a.h>
#include <string.h>

/* end_includes */

sst_bool (sst_is_valued_long_option_a)(
  char const * const arg,
  char const * const opt
) {
  if (!sst_is_long_option_a(arg, opt)) {
    return SST_FALSE;
  }
  if (strchr(arg, '=') == NULL) {
    return SST_FALSE;
  }
  return SST_TRUE;
}
