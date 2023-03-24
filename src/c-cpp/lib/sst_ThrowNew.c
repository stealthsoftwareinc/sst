/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <sst/sst_ThrowNew.h>
#include <sst/sst_ThrowNew.h>

#include <sst/SST_WITH_SST_THROWNEW.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_InitCause.h>
#include <sst/sst_ThrowNewByName.h>
#include <sst/sst_bool.h>
#include <sst/sst_status.h>

#if SST_WITH_SST_THROWNEW

#include <assert.h>
#include <jni.h>
#include <stddef.h>

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
