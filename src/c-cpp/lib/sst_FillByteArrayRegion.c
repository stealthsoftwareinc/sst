/*
 * Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#include <sst/sst_FillByteArrayRegion.h>
#include <sst/sst_FillByteArrayRegion.h>

#include <sst/SST_WITH_SST_FILLBYTEARRAYREGION.h>
#include <sst/SST_ENABLE_UNDEFINED_BEHAVIOR_CHECKS.h>
#include <sst/SST_INVALID_ARRAY_SIZE.h>
#include <sst/SST_JSIZE_MAXVAL.h>
#include <sst/SST_NEGATIVE_ARRAY_INDEX.h>
#include <sst/SST_NEGATIVE_ARRAY_SIZE.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/sst_status.h>

#if SST_WITH_SST_FILLBYTEARRAYREGION

#include <assert.h>
#include <jni.h>
#include <stddef.h>

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
