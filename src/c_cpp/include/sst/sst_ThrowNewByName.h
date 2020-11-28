/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_THROWNEWBYNAME_H
#define SST_SST_THROWNEWBYNAME_H

#include <sst/SST_HAVE_SST_THROWNEWBYNAME.h>
#if SST_HAVE_SST_THROWNEWBYNAME

/* begin_includes */

#include <jni.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION sst_bool (sst_ThrowNewByName)(
  JNIEnv *,
  char const *,
  char const *
);

#endif

#endif
