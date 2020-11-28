/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_FillByteArrayRegion.h>
#include <sst/sst_FillByteArrayRegion.h>

#include <sst/SST_HAVE_SST_FILLBYTEARRAYREGION.h>
#if SST_HAVE_SST_FILLBYTEARRAYREGION

/* begin_includes */

#include <assert.h>
#include <jni.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_INVALID_ARRAY_SIZE.h>
#include <sst/SST_JSIZE_MAXVAL.h>
#include <sst/SST_NEGATIVE_ARRAY_INDEX.h>
#include <sst/SST_NEGATIVE_ARRAY_SIZE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>
#include <stddef.h>

/* end_includes */

void (sst_FillByteArrayRegion)(
  JNIEnv * const env,
  jbyteArray const array,
  jsize const start,
  jsize const len,
  jbyte const value
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (env == NULL) {
      assert(!SST_NULL_POINTER);
      return;
    }
    if (array == NULL) {
      assert(!SST_NULL_POINTER);
      return;
    }
    if (start < 0) {
      assert(!SST_NEGATIVE_ARRAY_INDEX);
      return;
    }
    if (len < 0) {
      assert(!SST_NEGATIVE_ARRAY_SIZE);
      return;
    }
    if (start > SST_JSIZE_MAXVAL - len) {
      assert(!SST_INVALID_ARRAY_SIZE);
      return;
    }
  }
  #endif
  {
    jbyte buf[128] = {0};
    jsize const n = sizeof(buf) / sizeof(*buf);
    if (value != 0) {
      jsize i;
      for (i = 0; i != n; ++i) {
        buf[i] = value;
      }
    }
    {
      jsize i = 0;
      do {
        jsize const k = len - i < n ? len - i : n;
        (*env)->SetByteArrayRegion(
          env, array, start + i, k, buf
        );
        i += k;
      } while (i != len);
    }
  }
}

#endif

typedef int prevent_an_empty_translation_unit;
