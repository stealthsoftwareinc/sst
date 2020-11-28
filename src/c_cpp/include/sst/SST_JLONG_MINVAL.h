/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_JLONG_MINVAL_H
#define SST_SST_JLONG_MINVAL_H

#include <sst/SST_HAVE_SST_JLONG_MINVAL.h>
#if SST_HAVE_SST_JLONG_MINVAL

#include <sst/SST_JLONG_MAXVAL.h>

#define SST_JLONG_MINVAL ( \
  -SST_JLONG_MAXVAL - 1 \
)

#endif

#endif
