/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_snip_long_option_w.h>
#include <sst/sst_snip_long_option_w.h>

/* begin_includes */

#include <sst/sst_is_long_option_w.h>
#include <stddef.h>

/* end_includes */

wchar_t * (sst_snip_long_option_w)(
  wchar_t const * const arg,
  wchar_t const * const opt
) {
  if (sst_is_long_option_w(arg, opt)) {
    return (wchar_t *)arg + 2;
  }
  return (wchar_t *)arg;
}