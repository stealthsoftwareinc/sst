/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_ctr_crypt.h>
#include <sst/sst_ctr_crypt.h>

#include <sst/SST_HAVE_SST_CTR_CRYPT.h>
#if SST_HAVE_SST_CTR_CRYPT

/* begin_includes */

#include <nettle/nettle-types.h>
#include <sst/sst_ctr_crypt_step.h>
#include <sst/sst_nettle_cipher_ctx.h>
#include <sst/sst_nettle_cipher_func.h>
#include <sst/sst_nettle_size.h>
#include <stddef.h>

/* end_includes */

void (sst_ctr_crypt)(
  sst_nettle_cipher_ctx * const ctx,
  sst_nettle_cipher_func * const f,
  sst_nettle_size const block_size,
  uint8_t * const ctr,
  size_t const length,
  uint8_t * const dst,
  uint8_t const * const src
) {
  sst_nettle_size const k = 16384;
  sst_nettle_size const step = block_size > k ? block_size : k;
  sst_ctr_crypt_step(ctx, f, block_size, ctr, length, dst, src, step);
}

#endif

typedef int prevent_an_empty_translation_unit;
