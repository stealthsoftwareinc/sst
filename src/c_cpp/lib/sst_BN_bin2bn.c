/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_BN_bin2bn.h>
#include <sst/sst_BN_bin2bn.h>

#include <sst/SST_HAVE_SST_BN_BIN2BN.h>
#if SST_HAVE_SST_BN_BIN2BN

/* begin_includes */

#include <assert.h>
#include <openssl/bn.h>
#include <sst/sst_BN_bin2bn_step.h>
#include <stddef.h>

/* end_includes */

BIGNUM * (sst_BN_bin2bn)(
  unsigned char const * const s,
  size_t const len,
  BIGNUM * const ret,
  BN_CTX * const ctx
) {
  if (len > 1) {
    assert(ctx != NULL);
  }
  return sst_BN_bin2bn_step(s, len, ret, ctx, 16384);
}

#endif

typedef int prevent_an_empty_translation_unit;
