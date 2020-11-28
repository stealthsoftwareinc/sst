/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_get_short_option_value_a.h>
#include <sst/sst_get_short_option_value_a.h>

/* begin_includes */

#include <sst/sst_is_unvalued_short_option_a.h>
#include <sst/sst_is_valued_short_option_a.h>
#include <stddef.h>

/* end_includes */

char * (sst_get_short_option_value_a)(
  char * const * const argv,
  char const * const opt
) {
  if (argv == NULL) {
    return NULL;
  }
  if (sst_is_valued_short_option_a(argv[0], opt)) {
    return argv[0] + 2;
  }
  if (sst_is_unvalued_short_option_a(argv[0], opt)) {
    return argv[1];
  }
  return NULL;
}
