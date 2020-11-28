/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_SETBIT1_H
#define SST_SST_SETBIT1_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bit.h>
#include <stddef.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION unsigned char (sst_setbit1)(
  unsigned char,
  size_t,
  sst_bit
);

#endif
