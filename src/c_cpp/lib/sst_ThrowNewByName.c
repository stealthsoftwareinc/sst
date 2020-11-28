/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_ThrowNewByName.h>
#include <sst/sst_ThrowNewByName.h>

#include <sst/SST_HAVE_SST_THROWNEWBYNAME.h>
#if SST_HAVE_SST_THROWNEWBYNAME

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

sst_bool (sst_ThrowNewByName)(
  JNIEnv * const env,
  char const * const name,
  char const * const message
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
  {
    jclass const clazz = (*env)->FindClass(env, name);
    if (clazz == NULL) {
      return SST_FALSE;
    }
    if ((*env)->ThrowNew(env, clazz, message) != 0) {
      return SST_FALSE;
    }
  }
  return SST_TRUE;
}

#endif

typedef int prevent_an_empty_translation_unit;
