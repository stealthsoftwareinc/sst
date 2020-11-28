/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_strchr.h>
#include <sst/sst_strchr.h>

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_NULL_POINTER.h>
#include <stdlib.h>
#include <string.h>
#include <tgicmp.h>
#include <wficmp.h>

/* end_includes */

char * (sst_strchr)(
  char const * const s,
  char const c
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (s == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
  }
  #endif
  if (TGICMPGE(c, INT_MIN) && WFICMPLE(c, INT_MAX)) {
    return strchr(s, c);
  }
  {
    char const * p = s;
    for (;;) {
      if (*p == c) {
        return (char *)p;
      }
      if (*p == '\0') {
        return NULL;
      }
      ++p;
    }
  }
}
