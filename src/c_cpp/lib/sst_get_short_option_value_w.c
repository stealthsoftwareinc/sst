/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_get_short_option_value_w.h>
#include <sst/sst_get_short_option_value_w.h>

/* begin_includes */

#include <sst/sst_is_unvalued_short_option_w.h>
#include <sst/sst_is_valued_short_option_w.h>
#include <stddef.h>

/* end_includes */

wchar_t * (sst_get_short_option_value_w)(
  wchar_t * const * const argv,
  wchar_t const * const opt
) {
  if (argv == NULL) {
    return NULL;
  }
  if (sst_is_valued_short_option_w(argv[0], opt)) {
    return argv[0] + 2;
  }
  if (sst_is_unvalued_short_option_w(argv[0], opt)) {
    return argv[1];
  }
  return NULL;
}
