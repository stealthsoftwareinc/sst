/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_MEMCLRF_H
#define SST_SST_MEMCLRF_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION void (sst_memclrf)(
  void *,
  size_t,
  void const *,
  size_t,
  size_t
);

#endif
