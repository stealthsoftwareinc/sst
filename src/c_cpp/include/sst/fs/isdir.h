/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 */

#ifndef SST_FS_ISDIR_H
#define SST_FS_ISDIR_H

#ifdef __cplusplus

#include <sst/SST_HAVE_POSIX.h>
#include <sst/catalog/SST_PUBLIC_CPP_FUNCTION.hpp>

#if SST_HAVE_POSIX

#include <string>

namespace sst {
namespace fs {

SST_PUBLIC_CPP_FUNCTION
bool isdir(std::string const & path);

} // namespace fs
} // namespace sst

#endif // SST_HAVE_POSIX

#endif // __cplusplus

#endif // SST_FS_ISDIR_H
