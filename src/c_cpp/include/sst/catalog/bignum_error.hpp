//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_BIGNUM_ERROR_HPP
#define SST_CATALOG_BIGNUM_ERROR_HPP

#include <sst/config.h>

#if SST_HAVE_LIB_CRYPTO

#include <stdexcept>

namespace sst {

struct bignum_error : std::runtime_error {
  using std::runtime_error::runtime_error;
};

} // namespace sst

#endif // SST_HAVE_LIB_CRYPTO

#endif // SST_CATALOG_BIGNUM_ERROR_HPP
