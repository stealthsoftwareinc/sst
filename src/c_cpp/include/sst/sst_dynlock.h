/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_DYNLOCK_H
#define SST_SST_DYNLOCK_H

struct CRYPTO_dynlock_value;

struct CRYPTO_dynlock_value * sst_dynlock_create(
  char const *,
  int
);

void sst_dynlock_lock(
  int,
  struct CRYPTO_dynlock_value *,
  char const *,
  int
);

void sst_dynlock_destroy(
  struct CRYPTO_dynlock_value *,
  char const *,
  int
);

#endif
