/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_RAND_BYTES_H
#define SST_SST_RAND_BYTES_H

#include <sst/SST_HAVE_SST_RAND_BYTES.h>
#if SST_HAVE_SST_RAND_BYTES

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION int (sst_RAND_bytes)(
  unsigned char *,
  size_t
);

#endif

#endif
