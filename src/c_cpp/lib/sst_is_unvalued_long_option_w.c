/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_is_unvalued_long_option_w.h>
#include <sst/sst_is_unvalued_long_option_w.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_is_long_option_w.h>
#include <sst/sst_is_valued_long_option_w.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_is_unvalued_long_option_w)(
  wchar_t const * const arg,
  wchar_t const * const opt
) {
  if (!sst_is_long_option_w(arg, opt)) {
    return SST_FALSE;
  }
  if (sst_is_valued_long_option_w(arg, opt)) {
    return SST_FALSE;
  }
  return SST_TRUE;
}
