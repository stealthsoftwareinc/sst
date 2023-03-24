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

#include <sst/sst_mutex.h>
#if SST_MUTEX_IMP == SST_MUTEX_IMP_NULL

/* begin_includes */

#include <sst/SST_NOT_SUPPORTED.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_WILD_POINTER.h>
#include <sst/sst_status.h>
#include <stddef.h>

/* end_includes */

sst_status sst_mutex_attr_create(
  struct sst_mutex_attr * * const attr
) {
  if (attr == NULL) {
    return SST_NULL_POINTER;
  }
  return SST_NOT_SUPPORTED;
}

sst_status sst_mutex_attr_destroy(
  struct sst_mutex_attr * const attr
) {
  if (attr == NULL) {
    return SST_NULL_POINTER;
  }
  return SST_WILD_POINTER;
}

sst_status sst_mutex_create(
  struct sst_mutex * * const mtx,
  struct sst_mutex_attr * const attr
) {
  if (mtx == NULL) {
    return SST_NULL_POINTER;
  }
  if (attr != NULL) {
    return SST_WILD_POINTER;
  }
  return SST_NOT_SUPPORTED;
}

sst_status sst_mutex_destroy(
  struct sst_mutex * const mtx
) {
  if (mtx == NULL) {
    return SST_NULL_POINTER;
  }
  return SST_WILD_POINTER;
}

sst_status sst_mutex_lock(
  struct sst_mutex * const mtx
) {
  if (mtx == NULL) {
    return SST_NULL_POINTER;
  }
  return SST_WILD_POINTER;
}

sst_status sst_mutex_unlock(
  struct sst_mutex * const mtx
) {
  if (mtx == NULL) {
    return SST_NULL_POINTER;
  }
  return SST_WILD_POINTER;
}

#endif
