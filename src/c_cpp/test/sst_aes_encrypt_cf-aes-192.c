/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/config_private.h>

#include <sst/SST_HAVE_SST_AES_ENCRYPT_CF.h>
#include <sst/sst_aes_encrypt_cf.h>
#include <TEST_EXIT.h>

#if ( \
  HAVE_AES_BLOCK_SIZE && \
  HAVE_AES_CTX && \
  HAVE_AES_ENCRYPT && \
  HAVE_AES_SET_ENCRYPT_KEY && \
  HAVE_NETTLE_AES_H && \
  HAVE_NETTLE_NETTLE_TYPES_H && \
  HAVE_UINT8_T_IN_NETTLE_NETTLE_TYPES_H && \
  SST_HAVE_SST_AES_ENCRYPT_CF && \
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
    uint8_t const key[24] = {0};
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
