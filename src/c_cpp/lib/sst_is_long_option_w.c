/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_is_long_option_w.h>
#include <sst/sst_is_long_option_w.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_is_long_option_w)(
  wchar_t const * const arg,
  wchar_t const * const opt
) {
  if (arg == NULL) {
    return SST_FALSE;
  }
  if (arg[0] != L'-') {
    return SST_FALSE;
  }
  if (arg[1] != L'-') {
    return SST_FALSE;
  }
  if (opt == NULL) {
    return SST_TRUE;
  }
  if (opt[0] != L'-') {
    return SST_FALSE;
  }
  if (opt[1] != L'-') {
    return SST_FALSE;
  }
  {
    wchar_t const * a = arg + 2;
    wchar_t const * o = opt + 2;
    while (*a != L'\0' && *a != L'=') {
      if (*a != *o) {
        return SST_FALSE;
      }
      ++a;
      ++o;
    }
    if (*o != L'\0' && *o != L'=') {
      return SST_FALSE;
    }
  }
  return SST_TRUE;
}
