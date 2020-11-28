/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_CTR_CRYPT_H
#define SST_SST_CTR_CRYPT_H

#include <sst/SST_HAVE_SST_CTR_CRYPT.h>
#if SST_HAVE_SST_CTR_CRYPT

/* begin_includes */

#include <nettle/nettle-types.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_nettle_cipher_ctx.h>
#include <sst/sst_nettle_cipher_func.h>
#include <sst/sst_nettle_size.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION void (sst_ctr_crypt)(
  sst_nettle_cipher_ctx *,
  sst_nettle_cipher_func *,
  sst_nettle_size,
  uint8_t *,
  size_t,
  uint8_t *,
  uint8_t const *
);

#endif

#endif
