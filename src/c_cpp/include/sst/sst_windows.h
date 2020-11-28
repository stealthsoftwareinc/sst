/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_WINDOWS
#define SST_WINDOWS

#include <sst/SST_HAVE_WINCRYPT_H.h>
#include <sst/SST_HAVE_WINDOWS.h>

#if (defined(TEXT))
  #error sst.h should be included before windows.h and friends
#endif

#if (SST_HAVE_WINDOWS)
  #include <windows.h>
#endif

#if (SST_HAVE_WINCRYPT_H)
  #include <wincrypt.h>
#endif

#endif
