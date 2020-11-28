/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_PTR_TO_JLONGPTR_H
#define SST_SST_PTR_TO_JLONGPTR_H

#include <sst/SST_HAVE_SST_PTR_TO_JLONGPTR.h>
#if SST_HAVE_SST_PTR_TO_JLONGPTR

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_jlongptr.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION sst_jlongptr (sst_ptr_to_jlongptr)(
  void const *
);

#endif

#endif
