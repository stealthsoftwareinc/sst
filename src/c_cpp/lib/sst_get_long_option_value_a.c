/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_get_long_option_value_a.h>
#include <sst/sst_get_long_option_value_a.h>

/* begin_includes */

#include <sst/sst_is_unvalued_long_option_a.h>
#include <sst/sst_is_valued_long_option_a.h>
#include <string.h>

/* end_includes */

char * (sst_get_long_option_value_a)(
  char * const * const argv,
  char const * const opt
) {
  if (argv == NULL) {
    return NULL;
  }
  if (sst_is_valued_long_option_a(argv[0], opt)) {
    return strchr(argv[0], '=') + 1;
  }
  if (sst_is_unvalued_long_option_a(argv[0], opt)) {
    return argv[1];
  }
  return NULL;
}
