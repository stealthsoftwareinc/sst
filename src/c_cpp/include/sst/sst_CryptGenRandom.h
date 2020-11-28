/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_CRYPTGENRANDOM_H
#define SST_SST_CRYPTGENRANDOM_H

#include <sst/SST_HAVE_SST_CRYPTGENRANDOM.h>
#if SST_HAVE_SST_CRYPTGENRANDOM

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_windows.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION BOOL (sst_CryptGenRandom)(
  HCRYPTPROV,
  size_t,
  BYTE *
);

#endif

#endif
