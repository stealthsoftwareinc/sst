/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_crop_option_w.h>
#include <sst/sst_crop_option_w.h>

/* begin_includes */

#include <sst/sst_crop_long_option_w.h>
#include <sst/sst_crop_short_option_w.h>
#include <sst/sst_is_long_option_w.h>
#include <stddef.h>

/* end_includes */

wchar_t * (sst_crop_option_w)(
  wchar_t * const arg,
  wchar_t const * const opt
) {
  if (sst_is_long_option_w(arg, opt)) {
    return sst_crop_long_option_w(arg, opt);
  }
  return sst_crop_short_option_w(arg, opt);
}
