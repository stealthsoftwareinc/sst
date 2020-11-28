/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_AES_ENCRYPT_CF_H
#define SST_SST_AES_ENCRYPT_CF_H

#include <sst/SST_HAVE_SST_AES_ENCRYPT_CF.h>
#if SST_HAVE_SST_AES_ENCRYPT_CF

/* begin_includes */

#include <nettle/nettle-types.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_nettle_cipher_ctx.h>
#include <sst/sst_nettle_size.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION void (sst_aes_encrypt_cf)(
  sst_nettle_cipher_ctx *,
  sst_nettle_size,
  uint8_t *,
  uint8_t const *
);

#endif

#endif
