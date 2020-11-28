/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/config_private.h>

#include <sst/sst_init_crypto.h>
#include <sst/sst_init_crypto.h>

/* begin_includes */

#include <sst/SST_SUCCESS.h>
#include <sst/sst_status.h>
#include <stddef.h>

/* end_includes */

#if HAVE_ERR_LOAD_CRYPTO_STRINGS
  #include <openssl/err.h>
#endif

#if HAVE_OPENSSL_ADD_ALL_ALGORITHMS
  #include <openssl/evp.h>
#endif

#if HAVE_OPENSSL_CONFIG
  #include <openssl/conf.h>
#endif

sst_status (sst_init_crypto)(
  void
) {

  #if HAVE_ERR_LOAD_CRYPTO_STRINGS
  {
    ERR_load_crypto_strings();
  }
  #endif

  #if HAVE_OPENSSL_ADD_ALL_ALGORITHMS
  {
    OpenSSL_add_all_algorithms();
  }
  #endif

  #if HAVE_OPENSSL_CONFIG
  {
    OPENSSL_config(NULL);
  }
  #endif

  return SST_SUCCESS;

}
