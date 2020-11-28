/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_BITCLR2B_H
#define SST_SST_BITCLR2B_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION void (sst_bitclr2b)(
  void *,
  size_t,
  size_t,
  void const *,
  size_t,
  size_t,
  void const *,
  size_t,
  size_t,
  size_t,
  size_t
);

#endif
