//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_CHECKED_ERROR_HPP
#define SST_CATALOG_CHECKED_ERROR_HPP

#include <stdexcept>

namespace sst {

struct checked_error : std::range_error {
  using std::range_error::range_error;
};

} // namespace sst

#endif // SST_CATALOG_CHECKED_ERROR_HPP
