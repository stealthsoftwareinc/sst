/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_is_long_option_a.h>
#include <sst/sst_is_long_option_a.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_is_long_option_a)(
  char const * const arg,
  char const * const opt
) {
  if (arg == NULL) {
    return SST_FALSE;
  }
  if (arg[0] != '-') {
    return SST_FALSE;
  }
  if (arg[1] != '-') {
    return SST_FALSE;
  }
  if (opt == NULL) {
    return SST_TRUE;
  }
  if (opt[0] != '-') {
    return SST_FALSE;
  }
  if (opt[1] != '-') {
    return SST_FALSE;
  }
  {
    char const * a = arg + 2;
    char const * o = opt + 2;
    while (*a != '\0' && *a != '=') {
      if (*a != *o) {
        return SST_FALSE;
      }
      ++a;
      ++o;
    }
    if (*o != '\0' && *o != '=') {
      return SST_FALSE;
    }
  }
  return SST_TRUE;
}
