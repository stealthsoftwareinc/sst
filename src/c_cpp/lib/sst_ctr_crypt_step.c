/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_ctr_crypt_step.h>
#include <sst/sst_ctr_crypt_step.h>

#include <sst/SST_HAVE_SST_CTR_CRYPT_STEP.h>
#if SST_HAVE_SST_CTR_CRYPT_STEP

/* begin_includes */

#include <assert.h>
#include <nettle/ctr.h>
#include <nettle/nettle-types.h>
#include <sst/sst_nettle_cipher_ctx.h>
#include <sst/sst_nettle_cipher_func.h>
#include <sst/sst_nettle_size.h>
#include <stddef.h>

/* end_includes */

void (sst_ctr_crypt_step)(
  sst_nettle_cipher_ctx * const ctx,
  sst_nettle_cipher_func * const f,
  sst_nettle_size const block_size,
  uint8_t * const ctr,
  size_t length,
  uint8_t * dst,
  uint8_t const * src,
  sst_nettle_size const step
) {
  if (length != 0) {
    assert(step != 0);
    assert(step >= block_size);
  }
  do {
    sst_nettle_size k;
    if (length <= step) {
      k = length;
    } else if (block_size != 0) {
      k = (step / block_size) * block_size;
    } else {
      k = step;
    }
    ctr_crypt(ctx, f, block_size, ctr, k, dst, src);
    if (src != NULL) {
      src += k;
    }
    if (dst != NULL) {
      dst += k;
    }
    length -= k;
  } while (length != 0);
}

#endif

typedef int prevent_an_empty_translation_unit;
