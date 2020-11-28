/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_snip_long_option_a.h>
#include <sst/sst_snip_long_option_a.h>

/* begin_includes */

#include <sst/sst_is_long_option_a.h>

/* end_includes */

char * (sst_snip_long_option_a)(
  char const * const arg,
  char const * const opt
) {
  if (sst_is_long_option_a(arg, opt)) {
    return (char *)arg + 2;
  }
  return (char *)arg;
}
