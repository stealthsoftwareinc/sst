/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_SST_GMP_H
#define SST_SST_GMP_H

#include <sst/SST_HAVE_GMP_H.h>
#include <sst/SST_HAVE_OBSTACK_H.h>

#if (defined(__GNU_MP_VERSION))
  #error sst.h should be included before gmp.h
#endif

#if (SST_HAVE_GMP_H)
  #if (SST_HAVE_OBSTACK_H)
    #include <obstack.h>
  #endif
  #include <stdarg.h>
  #include <stdio.h>
  #include <gmp.h>
#endif

#endif
