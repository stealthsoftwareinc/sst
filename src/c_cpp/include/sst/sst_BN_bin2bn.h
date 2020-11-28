/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_BN_BIN2BN_H
#define SST_SST_BN_BIN2BN_H

#include <sst/SST_HAVE_SST_BN_BIN2BN.h>
#if SST_HAVE_SST_BN_BIN2BN

/* begin_includes */

#include <openssl/bn.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION BIGNUM * (sst_BN_bin2bn)(
  unsigned char const *,
  size_t,
  BIGNUM *,
  BN_CTX *
);

#endif

#endif
