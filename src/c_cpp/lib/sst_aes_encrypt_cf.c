/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_aes_encrypt_cf.h>
#include <sst/sst_aes_encrypt_cf.h>

#include <sst/SST_HAVE_SST_AES_ENCRYPT_CF.h>
#if SST_HAVE_SST_AES_ENCRYPT_CF

#include <nettle/aes.h>
#include <nettle/nettle-types.h>
#include <sst/sst_nettle_cipher_ctx.h>
#include <sst/sst_nettle_size.h>

void (sst_aes_encrypt_cf)(
  sst_nettle_cipher_ctx * const ctx,
  sst_nettle_size const length,
  uint8_t * const dst,
  uint8_t const * const src
) {
  aes_encrypt(ctx, length, dst, src);
}

#endif

typedef int prevent_an_empty_translation_unit;
