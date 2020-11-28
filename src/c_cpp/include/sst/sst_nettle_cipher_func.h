/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_NETTLE_CIPHER_FUNC_H
#define SST_SST_NETTLE_CIPHER_FUNC_H

#include <sst/SST_HAVE_SST_NETTLE_CIPHER_FUNC.h>
#if SST_HAVE_SST_NETTLE_CIPHER_FUNC

#include <nettle/nettle-types.h>
#include <sst/SST_HAVE_NETTLE_CIPHER_FUNC.h>

#if (SST_HAVE_NETTLE_CIPHER_FUNC)
  typedef nettle_cipher_func sst_nettle_cipher_func;
#else
  typedef nettle_crypt_func sst_nettle_cipher_func;
#endif

#endif

#endif
