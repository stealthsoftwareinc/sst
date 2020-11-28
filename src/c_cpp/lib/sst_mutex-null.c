/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
