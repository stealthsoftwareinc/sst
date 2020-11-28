/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_NETTLE_CIPHER_CTX_H
#define SST_SST_NETTLE_CIPHER_CTX_H

#include <sst/SST_HAVE_SST_NETTLE_CIPHER_CTX.h>
#if SST_HAVE_SST_NETTLE_CIPHER_CTX

#include <sst/SST_HAVE_NETTLE_CIPHER_FUNC.h>

#if (SST_HAVE_NETTLE_CIPHER_FUNC)
  typedef void const sst_nettle_cipher_ctx;
#else
  typedef void sst_nettle_cipher_ctx;
#endif

#endif

#endif
