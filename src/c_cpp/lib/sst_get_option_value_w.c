/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_get_option_value_w.h>
#include <sst/sst_get_option_value_w.h>

/* begin_includes */

#include <sst/sst_get_long_option_value_w.h>
#include <sst/sst_get_short_option_value_w.h>
#include <stddef.h>

/* end_includes */

wchar_t * (sst_get_option_value_w)(
  wchar_t * const * const argv,
  wchar_t const * const opt
) {
  {
    wchar_t * const val = sst_get_long_option_value_w(argv, opt);
    if (val != NULL) {
      return val;
    }
  }
  {
    wchar_t * const val = sst_get_short_option_value_w(argv, opt);
    if (val != NULL) {
      return val;
    }
  }
  return NULL;
}
