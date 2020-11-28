/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_FIXLOCK_H
#define SST_SST_FIXLOCK_H

#include <sst/sst_status.h>

sst_status sst_fixlock_create(
  int
);

void sst_fixlock_lock(
  int,
  int,
  char const *,
  int
);

sst_status sst_fixlock_destroy(
  void
);

#endif
