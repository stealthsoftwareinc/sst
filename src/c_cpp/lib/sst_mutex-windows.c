/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_mutex.h>
#if SST_MUTEX_IMP == SST_MUTEX_IMP_WINDOWS

#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/SST_NOT_SUPPORTED.h>
#include <sst/SST_RESTRICT.h>
#include <sst/sst_status.h>

sst_status sst_mutex_attr_create(
  struct sst_mutex_attr * * const SST_RESTRICT attr
) {
  if (attr == NULL) {
    return SST_INVALID_ARGUMENT;
  }
  return SST_NOT_SUPPORTED;
}

sst_status sst_mutex_attr_destroy(
  struct sst_mutex_attr * const SST_RESTRICT attr
) {
  (void)attr;
  return SST_INVALID_ARGUMENT;
}

sst_status sst_mutex_create(
  struct sst_mutex * * const SST_RESTRICT mtx,
  struct sst_mutex_attr * const SST_RESTRICT attr
) {
  if (mtx == NULL || attr != NULL) {
    return SST_INVALID_ARGUMENT;
  }
  return SST_NOT_SUPPORTED;
}

sst_status sst_mutex_destroy(
  struct sst_mutex * const SST_RESTRICT mtx
) {
  (void)mtx;
  return SST_INVALID_ARGUMENT;
}

sst_status sst_mutex_lock(
  struct sst_mutex * const SST_RESTRICT mtx
) {
  (void)mtx;
  return SST_INVALID_ARGUMENT;
}

sst_status sst_mutex_unlock(
  struct sst_mutex * const SST_RESTRICT mtx
) {
  (void)mtx;
  return SST_INVALID_ARGUMENT;
}

#endif
