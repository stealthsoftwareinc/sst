/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_InitCause.h>
#include <sst/sst_InitCause.h>

#include <sst/SST_HAVE_SST_INITCAUSE.h>
#if SST_HAVE_SST_INITCAUSE

/* begin_includes */

#include <assert.h>
#include <jni.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_status.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_InitCause)(
  JNIEnv * const env,
  jthrowable const obj,
  jthrowable const cause
) {
  #if (SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS)
  {
    if (env == NULL) {
      assert(!SST_NULL_POINTER);
      return SST_FALSE;
    }
    if (obj == NULL) {
      assert(!SST_NULL_POINTER);
      return SST_FALSE;
    }
  }
  #endif
  {
    jclass const clazz = (*env)->FindClass(env, "java/lang/Throwable");
    if (clazz == NULL) {
      return SST_FALSE;
    }
    {
      jmethodID const method = (*env)->GetMethodID(
        env, clazz, "initCause",
        "(Ljava/lang/Throwable;)Ljava/lang/Throwable;"
      );
      if (method == NULL) {
        return SST_FALSE;
      }
      (void)(*env)->CallObjectMethod(env, obj, method, cause);
    }
  }
  return SST_TRUE;
}

#endif

typedef int prevent_an_empty_translation_unit;
