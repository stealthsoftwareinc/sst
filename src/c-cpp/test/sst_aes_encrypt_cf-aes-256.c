/*
 * Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#include <sst/config_private.h>

#include <sst/SST_WITH_SST_AES_ENCRYPT_CF.h>
#include <sst/sst_aes_encrypt_cf.h>
#include <TEST_EXIT.h>

#if ( \
  WITH_AES_BLOCK_SIZE && \
  WITH_AES_CTX && \
  WITH_AES_ENCRYPT && \
  WITH_AES_SET_ENCRYPT_KEY && \
  WITH_NETTLE_AES_H && \
  WITH_NETTLE_NETTLE_TYPES_H && \
  WITH_UINT8_T_IN_NETTLE_NETTLE_TYPES_H && \
  SST_WITH_SST_AES_ENCRYPT_CF && \
  1 \
)

/* begin_includes */

#include <nettle/aes.h>
#include <nettle/nettle-types.h>
#include <string.h>

/* end_includes */

int main(
  void
) {
  struct aes_ctx ctx;
  {
    uint8_t const key[32] = {0};
    aes_set_encrypt_key(&ctx, sizeof(key), key);
  }
  {
    uint8_t const src[AES_BLOCK_SIZE] = {0};
    uint8_t dst1[sizeof(src)] = {1};
    uint8_t dst2[sizeof(src)] = {2};
    aes_encrypt(&ctx, sizeof(src), dst1, src);
    sst_aes_encrypt_cf(&ctx, sizeof(src), dst2, src);
    if (memcmp(dst1, dst2, sizeof(src)) != 0) {
      return TEST_EXIT_FAIL;
    }
  }
  return TEST_EXIT_PASS;
}

#else

int main(
  void
) {
  return TEST_EXIT_SKIP;
}

#endif
