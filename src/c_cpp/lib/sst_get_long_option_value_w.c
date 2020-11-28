/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_get_long_option_value_w.h>
#include <sst/sst_get_long_option_value_w.h>

#include <sst/sst_is_unvalued_long_option_w.h>
#include <sst/sst_is_valued_long_option_w.h>
#include <wchar.h>

wchar_t * (sst_get_long_option_value_w)(
  wchar_t * const * const argv,
  wchar_t const * const opt
) {
  if (argv == NULL) {
    return NULL;
  }
  if (sst_is_valued_long_option_w(argv[0], opt)) {
    return wcschr(argv[0], L'=') + 1;
  }
  if (sst_is_unvalued_long_option_w(argv[0], opt)) {
    return argv[1];
  }
  return NULL;
}
