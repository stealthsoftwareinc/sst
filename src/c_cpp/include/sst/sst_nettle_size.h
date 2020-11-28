/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_NETTLE_SIZE_H
#define SST_SST_NETTLE_SIZE_H

#include <sst/SST_HAVE_SST_NETTLE_SIZE.h>
#if SST_HAVE_SST_NETTLE_SIZE

/* begin_includes */

#include <sst/SST_HAVE_NETTLE_CRYPT_FUNC_SIZE_T.h>
#include <stddef.h>

/* end_includes */

#if (SST_HAVE_NETTLE_CRYPT_FUNC_SIZE_T)
  typedef size_t sst_nettle_size;
#else
  typedef unsigned int sst_nettle_size;
#endif

#endif

#endif
