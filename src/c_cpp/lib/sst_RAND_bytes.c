/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_RAND_bytes.h>
#include <sst/sst_RAND_bytes.h>

#include <sst/SST_HAVE_SST_RAND_BYTES.h>
#if SST_HAVE_SST_RAND_BYTES

/* begin_includes */

#include <sst/sst_RAND_bytes_step.h>
#include <stddef.h>

/* end_includes */

int (sst_RAND_bytes)(
  unsigned char * const buf,
  size_t const num
) {
  return sst_RAND_bytes_step(buf, num, 16384);
}

#endif

typedef int prevent_an_empty_translation_unit;
