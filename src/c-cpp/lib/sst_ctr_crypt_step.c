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

#include <sst/sst_ctr_crypt_step.h>
#include <sst/sst_ctr_crypt_step.h>

#include <sst/SST_WITH_SST_CTR_CRYPT_STEP.h>
#include <sst/sst_nettle_cipher_ctx.h>
#include <sst/sst_nettle_cipher_func.h>
#include <sst/sst_nettle_size.h>

#if SST_WITH_SST_CTR_CRYPT_STEP

#include <assert.h>
#include <nettle/ctr.h>
#include <nettle/nettle-types.h>
#include <stddef.h>

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
