/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_JLONGPTR_TO_PTR_H
#define SST_SST_JLONGPTR_TO_PTR_H

#include <sst/SST_HAVE_SST_JLONGPTR_TO_PTR.h>
#if SST_HAVE_SST_JLONGPTR_TO_PTR

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_jlongptr.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION void * (sst_jlongptr_to_ptr)(
  sst_jlongptr
);

#endif

#endif
