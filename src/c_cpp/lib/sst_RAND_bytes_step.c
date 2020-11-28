/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_RAND_bytes_step.h>
#include <sst/sst_RAND_bytes_step.h>

#include <sst/SST_HAVE_SST_RAND_BYTES_STEP.h>
#if SST_HAVE_SST_RAND_BYTES_STEP

/* begin_includes */

#include <assert.h>
#include <openssl/rand.h>
#include <stddef.h>
#include <wficmp.h>

/* end_includes */

int (sst_RAND_bytes_step)(
  unsigned char * buf,
  size_t num,
  int const step
) {
  int r;
  if (num != 0) {
    assert(step > 0);
  } else {
    assert(step >= 0);
  }
  do {
    int k;
    if (WFICMPLT(num, step)) {
      k = num;
    } else {
      k = step;
    }
    r = RAND_bytes(buf, k);
    if (r != 1) {
      return r;
    }
    if (buf != NULL) {
      buf += k;
    }
    num -= k;
  } while (num != 0);
  return r;
}

#endif

typedef int prevent_an_empty_translation_unit;
