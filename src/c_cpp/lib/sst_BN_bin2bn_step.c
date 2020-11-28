/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_BN_bin2bn_step.h>
#include <sst/sst_BN_bin2bn_step.h>

#include <sst/SST_HAVE_SST_BN_BIN2BN_STEP.h>
#if SST_HAVE_SST_BN_BIN2BN_STEP

/* begin_includes */

#include <assert.h>
#include <openssl/bn.h>
#include <stddef.h>
#include <wficmp.h>

/* end_includes */

BIGNUM * (sst_BN_bin2bn_step)(
  unsigned char const * s,
  size_t len,
  BIGNUM * const ret,
  BN_CTX * const ctx,
  int const step
) {
  if (len != 0) {
    assert(step > 0);
  } else {
    assert(step >= 0);
  }
  if (WFICMPLE(len, step)) {
    return BN_bin2bn(s, len, ret);
  }
  assert(ctx != NULL);
  BN_CTX_start(ctx);
  {
    BIGNUM * const x = BN_CTX_get(ctx);
    BIGNUM * const y = BN_CTX_get(ctx);
    if (y == NULL) {
      BN_CTX_end(ctx);
      return NULL;
    }
    if (BN_bin2bn(s, step, x) == NULL) {
      BN_CTX_end(ctx);
      return NULL;
    }
    if (s != NULL) {
      s += step;
    }
    len -= step;
    while (WFICMPGT(len, step)) {
      if (BN_lshift(y, x, step) != 1) {
        BN_CTX_end(ctx);
        return NULL;
      }
      if (BN_bin2bn(s, step, x) == NULL) {
        BN_CTX_end(ctx);
        return NULL;
      }
      if (BN_add(x, x, y) != 1) {
        BN_CTX_end(ctx);
        return NULL;
      }
      if (s != NULL) {
        s += step;
      }
      len -= step;
    }
    if (BN_lshift(y, x, len) != 1) {
      BN_CTX_end(ctx);
      return NULL;
    }
    {
      BIGNUM * const z = BN_bin2bn(s, len, ret);
      if (z == NULL) {
        BN_CTX_end(ctx);
        return NULL;
      }
      if (BN_add(z, z, y) != 1) {
        if (z != ret) {
          BN_free(z);
        }
        BN_CTX_end(ctx);
        return NULL;
      }
      BN_CTX_end(ctx);
      return z;
    }
  }
}

#endif

typedef int prevent_an_empty_translation_unit;
