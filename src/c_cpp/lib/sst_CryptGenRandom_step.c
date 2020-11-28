/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_CryptGenRandom_step.h>
#include <sst/sst_CryptGenRandom_step.h>

#include <sst/SST_HAVE_SST_CRYPTGENRANDOM_STEP.h>
#if SST_HAVE_SST_CRYPTGENRANDOM_STEP

/* begin_includes */

#include <assert.h>
#include <sst/sst_windows.h>
#include <stddef.h>

/* end_includes */

BOOL (sst_CryptGenRandom_step)(
  HCRYPTPROV const hProv,
  size_t dwLen,
  BYTE * pbBuffer,
  DWORD const step
) {
  BOOL r;
  if (dwLen != 0) {
    assert(step != 0);
  }
  do {
    DWORD const k = dwLen < step ? dwLen : step;
    r = CryptGenRandom(hProv, k, pbBuffer);
    if (r == 0) {
      return r;
    }
    if (pbBuffer != NULL) {
      pbBuffer += k;
    }
    dwLen -= k;
  } while (dwLen != 0);
  return r;
}

#endif

typedef int prevent_an_empty_translation_unit;
