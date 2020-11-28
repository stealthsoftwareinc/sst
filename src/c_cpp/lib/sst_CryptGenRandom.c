/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_CryptGenRandom.h>
#include <sst/sst_CryptGenRandom.h>

#include <sst/SST_HAVE_SST_CRYPTGENRANDOM.h>
#if SST_HAVE_SST_CRYPTGENRANDOM

/* begin_includes */

#include <sst/sst_CryptGenRandom_step.h>
#include <sst/sst_windows.h>
#include <stddef.h>

/* end_includes */

BOOL (sst_CryptGenRandom)(
  HCRYPTPROV const hProv,
  size_t const dwLen,
  BYTE * const pbBuffer
) {
  return sst_CryptGenRandom_step(hProv, dwLen, pbBuffer, 16384);
}

#endif

typedef int prevent_an_empty_translation_unit;
