/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_crop_long_option_w.h>
#include <sst/sst_crop_long_option_w.h>

#include <sst/sst_is_valued_long_option_w.h>
#include <wchar.h>

wchar_t * (sst_crop_long_option_w)(
  wchar_t * const arg,
  wchar_t const * const opt
) {
  if (sst_is_valued_long_option_w(arg, opt)) {
    wcschr(arg, L'=')[0] = L'\0';
  }
  return arg;
}
