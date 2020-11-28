/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 */

#ifndef SST_FS_ERROR_H
#define SST_FS_ERROR_H

#ifdef __cplusplus

/* begin_includes */

#include <stdexcept>
#include <string>

/* end_includes */

namespace sst {
namespace fs {

struct error : std::runtime_error {

  explicit error(
    std::string const & what_arg
  ) : std::runtime_error(what_arg) {}

  explicit error(
    char const * const what_arg
  ) : std::runtime_error(what_arg) {}

};

} // namespace sst::fs
} // namespace sst

#endif // __cplusplus

#endif // SST_FS_ERROR_H
