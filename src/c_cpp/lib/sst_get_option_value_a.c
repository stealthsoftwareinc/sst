/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_get_option_value_a.h>
#include <sst/sst_get_option_value_a.h>

/* begin_includes */

#include <sst/sst_get_long_option_value_a.h>
#include <sst/sst_get_short_option_value_a.h>
#include <stddef.h>

/* end_includes */

char * (sst_get_option_value_a)(
  char * const * const argv,
  char const * const opt
) {
  {
    char * const val = sst_get_long_option_value_a(argv, opt);
    if (val != NULL) {
      return val;
    }
  }
  {
    char * const val = sst_get_short_option_value_a(argv, opt);
    if (val != NULL) {
      return val;
    }
  }
  return NULL;
}
