//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_SST_PUBLIC_CPP_FUNCTION_HPP
#define SST_CATALOG_SST_PUBLIC_CPP_FUNCTION_HPP

#ifdef SST_PUBLIC_CPP_FUNCTION
// User override.
#elif !defined(_WIN32) || !defined(DLL_EXPORT)
#define SST_PUBLIC_CPP_FUNCTION extern
#elif defined(SST_BUILD)
#define SST_PUBLIC_CPP_FUNCTION extern __declspec(dllexport)
#else
#define SST_PUBLIC_CPP_FUNCTION extern __declspec(dllimport)
#endif

#endif // SST_CATALOG_SST_PUBLIC_CPP_FUNCTION_HPP
