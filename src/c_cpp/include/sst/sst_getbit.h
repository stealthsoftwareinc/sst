/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_GETBIT_H
#define SST_SST_GETBIT_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bit.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION sst_bit (sst_getbit)(
  void const *,
  size_t,
  size_t
);

#endif
