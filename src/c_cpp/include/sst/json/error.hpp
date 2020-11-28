//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_JSON_ERROR_HPP
#define SST_JSON_ERROR_HPP

#include <exception>
#include <stdexcept>
#include <string>

namespace sst {
namespace json {

struct error : std::runtime_error {
  explicit error(std::string const & what_arg) :
      std::runtime_error(what_arg) {
  }
  explicit error(char const * const what_arg) :
      std::runtime_error(what_arg) {
  }
  explicit error(
      std::string const & prefix, std::exception const & suffix) :
      std::runtime_error(prefix + suffix.what()) {
  }
  explicit error(
      char const * const prefix, std::exception const & suffix) :
      error(std::string(prefix), suffix) {
  }
};

} // namespace json
} // namespace sst

#endif // SST_JSON_ERROR_HPP
