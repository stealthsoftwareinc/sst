/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_FILLBYTEARRAYREGION_H
#define SST_SST_FILLBYTEARRAYREGION_H

#include <sst/SST_HAVE_SST_FILLBYTEARRAYREGION.h>
#if SST_HAVE_SST_FILLBYTEARRAYREGION

/* begin_includes */

#include <jni.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>

/* end_includes */

SST_PUBLIC_C_FUNCTION void (sst_FillByteArrayRegion)(
  JNIEnv *,
  jbyteArray,
  jsize,
  jsize,
  jbyte
);

#endif

#endif
