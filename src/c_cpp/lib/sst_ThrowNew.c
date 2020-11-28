/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_ThrowNew.h>
#include <sst/sst_ThrowNew.h>

#include <sst/SST_HAVE_SST_THROWNEW.h>
#if SST_HAVE_SST_THROWNEW

/* begin_includes */

#include <assert.h>
#include <jni.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_InitCause.h>
#include <sst/sst_ThrowNewByName.h>
#include <sst/sst_bool.h>
#include <sst/sst_status.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_ThrowNew)(
  JNIEnv * const env,
  char const * const name,
  char const * const message,
  jthrowable const cause
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (env == NULL) {
      assert(!SST_NULL_POINTER);
      return SST_FALSE;
    }
    if (name == NULL) {
      assert(!SST_NULL_POINTER);
      return SST_FALSE;
    }
  }
  #endif
  if (!sst_ThrowNewByName(env, name, message)) {
    return SST_FALSE;
  }
  {
    jthrowable const obj = (*env)->ExceptionOccurred(env);
    if (obj == NULL) {
      return SST_FALSE;
    }
    if (!sst_InitCause(env, obj, cause)) {
      return SST_FALSE;
    }
  }
  return SST_TRUE;
}

#endif

typedef int prevent_an_empty_translation_unit;
