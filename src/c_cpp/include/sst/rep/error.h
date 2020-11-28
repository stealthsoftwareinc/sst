/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 */

#ifndef SST_REP_ERROR_H
#define SST_REP_ERROR_H

#ifdef __cplusplus

#include <stdexcept>
#include <string>

namespace sst {
namespace rep {

struct error : std::runtime_error {
  explicit error(std::string const & what_arg) :
      std::runtime_error(what_arg) {
  }
  explicit error(char const * const what_arg) :
      std::runtime_error(what_arg) {
  }
};

} // namespace rep
} // namespace sst

#endif // __cplusplus

#endif // SST_REP_ERROR_H
