/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_jmemset.h>
#include <sst/sst_jmemset.h>

#include <sst/SST_HAVE_SST_JMEMSET.h>
#if SST_HAVE_SST_JMEMSET

/* begin_includes */

#include <assert.h>
#include <jni.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_NEGATIVE_ARRAY_SIZE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>
#include <stdlib.h>
#include <string.h>
#include <wficmp.h>

/* end_includes */

void * (sst_jmemset)(
  void * const s,
  int const c,
  jsize n
) {
  size_t const size_max = (size_t)(-1);
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (s == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
    if (n < 0) {
      assert(!SST_NEGATIVE_ARRAY_SIZE);
      abort();
    }
  }
  #endif
  {
    unsigned char * p = s;
    while (WFICMPGT(n, size_max)) {
      (void)memset(p, c, size_max);
      p += size_max;
      n -= size_max;
    }
    (void)memset(p, c, n);
  }
  return s;
}

#endif

typedef int prevent_an_empty_translation_unit;
