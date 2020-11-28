/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SST_CATALOG_SST_PUBLIC_C_OBJECT_H
#define SST_CATALOG_SST_PUBLIC_C_OBJECT_H

#include <sst/catalog/SST_EXTERN_C.h>

#ifdef SST_PUBLIC_C_OBJECT
/* User override. */
#elif !defined(_WIN32) || !defined(DLL_EXPORT)
#define SST_PUBLIC_C_OBJECT SST_EXTERN_C
#elif defined(SST_BUILD)
#define SST_PUBLIC_C_OBJECT SST_EXTERN_C __declspec(dllexport)
#else
#define SST_PUBLIC_C_OBJECT SST_EXTERN_C __declspec(dllimport)
#endif

#endif /* SST_CATALOG_SST_PUBLIC_C_OBJECT_H */
