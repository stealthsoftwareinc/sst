/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_STATUS_IMPLIES_H
#define SST_SST_STATUS_IMPLIES_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>
#include <sst/sst_status.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION sst_bool (sst_status_implies)(
  sst_status,
  sst_status
);

#endif
