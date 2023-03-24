/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <sst/sst_BN_bin2bn_step.h>
#include <sst/sst_BN_bin2bn_step.h>

#include <sst/SST_WITH_SST_BN_BIN2BN_STEP.h>

#if SST_WITH_SST_BN_BIN2BN_STEP

#include <assert.h>
#include <openssl/bn.h>
#include <stddef.h>
#include <wficmp.h>

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
