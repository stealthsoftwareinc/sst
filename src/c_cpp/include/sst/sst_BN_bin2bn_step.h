/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_BN_BIN2BN_STEP_H
#define SST_SST_BN_BIN2BN_STEP_H

#include <sst/SST_HAVE_SST_BN_BIN2BN_STEP.h>
#if SST_HAVE_SST_BN_BIN2BN_STEP

/* begin_includes */

#include <openssl/bn.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION BIGNUM * (sst_BN_bin2bn_step)(
  unsigned char const *,
  size_t,
  BIGNUM *,
  BN_CTX *,
  int
);

#endif

#endif
