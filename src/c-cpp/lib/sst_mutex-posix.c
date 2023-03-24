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
#if SST_MUTEX_IMP == SST_MUTEX_IMP_POSIX

/* begin_includes */

#include <pthread.h>
#include <sst/SST_FAILURE.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/SST_OUT_OF_MEMORY.h>
#include <sst/SST_RESTRICT.h>
#include <sst/SST_SUCCESS.h>
#include <sst/sst_status.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

struct sst_mutex_attr {
  unsigned char magic[sizeof(unsigned int)];
  pthread_mutexattr_t attr;
};

static unsigned int const attr_mlive =  (unsigned int)0x27DCA313U;
static unsigned int const attr_mdead = ~(unsigned int)0x27DCA313U;

sst_status sst_mutex_attr_create(
  struct sst_mutex_attr * * const SST_RESTRICT attr
) {
  if (attr == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  *attr = malloc(sizeof(**attr));
  if (*attr == NULL) {
    return SST_OUT_OF_MEMORY;
  }
  {
    int const e = pthread_mutexattr_init(&(*attr)->attr);
    if (e != 0) {
      free(*attr);
      *attr = NULL;
      return SST_FAILURE;
    }
  }
  (void)
    memcpy(
      (*attr)->magic,
      &attr_mlive,
      sizeof(unsigned int)
    )
  ;
  return SST_SUCCESS;
}

sst_status sst_mutex_attr_destroy(
  struct sst_mutex_attr * const attr
) {
  if (attr == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  if (
    memcmp(
      attr->magic,
      &attr_mlive,
      sizeof(unsigned int)
    )
  ) {
    return SST_INVALID_ARGUMENT;
  }
  {
    int const e = pthread_mutexattr_destroy(&attr->attr);
    (void)
      memcpy(
        attr->magic,
        &attr_mdead,
        sizeof(unsigned int)
      )
    ;
    free(attr);
    if (e != 0) {
      return SST_FAILURE;
    }
  }
  return SST_SUCCESS;
}

struct sst_mutex {
  unsigned char magic[sizeof(unsigned int)];
  pthread_mutex_t mtx;
};

static unsigned int const mtx_mlive =  (unsigned int)0xAE937764U;
static unsigned int const mtx_mdead = ~(unsigned int)0xAE937764U;

sst_status sst_mutex_create(
  struct sst_mutex * * const SST_RESTRICT mtx,
  struct sst_mutex_attr * attr
) {
  if (mtx == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  if (attr != NULL) {
    if (
      memcmp(
        attr->magic,
        &attr_mlive,
        sizeof(unsigned int)
      )
    ) {
      return SST_INVALID_ARGUMENT;
    }
  }
  *mtx = malloc(sizeof(**mtx));
  if (*mtx == NULL) {
    return SST_OUT_OF_MEMORY;
  }
  {
    int const attr_was_null = (attr == NULL);
    if (attr == NULL) {
      sst_status const s = sst_mutex_attr_create(&attr);
      if (s != SST_SUCCESS) {
        free(*mtx);
        *mtx = NULL;
        return s;
      }
    }
    {
      int const e = pthread_mutex_init(&(*mtx)->mtx, &attr->attr);
      if (attr_was_null) {
        (void)sst_mutex_attr_destroy(attr);
      }
      if (e != 0) {
        free(*mtx);
        *mtx = NULL;
        return SST_FAILURE;
      }
    }
  }
  (void)
    memcpy(
      (*mtx)->magic,
      &mtx_mlive,
      sizeof(unsigned int)
    )
  ;
  return SST_SUCCESS;
}

sst_status sst_mutex_destroy(
  struct sst_mutex * const mtx
) {
  if (mtx == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  if (
    memcmp(
      mtx->magic,
      &mtx_mlive,
      sizeof(unsigned int)
    )
  ) {
    return SST_INVALID_ARGUMENT;
  }
  {
    int const e = pthread_mutex_destroy(&mtx->mtx);
    (void)
      memcpy(
        mtx->magic,
        &mtx_mdead,
        sizeof(unsigned int)
      )
    ;
    free(mtx);
    if (e != 0) {
      return SST_FAILURE;
    }
  }
  return SST_SUCCESS;
}

sst_status sst_mutex_lock(
  struct sst_mutex * const mtx
) {
  if (mtx == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  if (
    memcmp(
      mtx->magic,
      &mtx_mlive,
      sizeof(unsigned int)
    )
  ) {
    return SST_INVALID_ARGUMENT;
  }
  {
    int const e = pthread_mutex_lock(&mtx->mtx);
    if (e != 0) {
      return SST_FAILURE;
    }
  }
  return SST_SUCCESS;
}

sst_status sst_mutex_unlock(
  struct sst_mutex * const mtx
) {
  if (mtx == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  if (
    memcmp(
      mtx->magic,
      &mtx_mlive,
      sizeof(unsigned int)
    )
  ) {
    return SST_INVALID_ARGUMENT;
  }
  {
    int const e = pthread_mutex_unlock(&mtx->mtx);
    if (e != 0) {
      return SST_FAILURE;
    }
  }
  return SST_SUCCESS;
}

#endif
