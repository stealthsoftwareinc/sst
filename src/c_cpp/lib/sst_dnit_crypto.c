/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/config_private.h>

#include <sst/sst_dnit_crypto.h>
#include <sst/sst_dnit_crypto.h>

#include <sst/SST_SUCCESS.h>
#include <sst/sst_status.h>

#if HAVE_OPENSSL_CONFIG
  #if HAVE_CONF_MODULES_FREE
    #include <openssl/conf.h>
  #endif
#endif

#if HAVE_OPENSSL_ADD_ALL_ALGORITHMS
  #if HAVE_EVP_CLEANUP
    #include <openssl/evp.h>
  #endif
#endif

#if HAVE_ERR_LOAD_CRYPTO_STRINGS
  #if HAVE_ERR_FREE_STRINGS
    #include <openssl/err.h>
  #endif
#endif

sst_status (sst_dnit_crypto)(
  void
) {

  #if HAVE_OPENSSL_CONFIG
    #if HAVE_CONF_MODULES_FREE
    {
      CONF_modules_free();
    }
    #endif
  #endif

  #if HAVE_OPENSSL_ADD_ALL_ALGORITHMS
    #if HAVE_EVP_CLEANUP
    {
      EVP_cleanup();
    }
    #endif
  #endif

  #if HAVE_ERR_LOAD_CRYPTO_STRINGS
    #if HAVE_ERR_FREE_STRINGS
    {
      ERR_free_strings();
    }
    #endif
  #endif

  return SST_SUCCESS;

}
