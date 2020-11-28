//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_INTEGER_REP_HPP
#define SST_CATALOG_INTEGER_REP_HPP

namespace sst {

enum class integer_rep {
  pure_unsigned,
  twos_complement,
  ones_complement,
  sign_magnitude
};

} // namespace sst

#endif // SST_CATALOG_INTEGER_REP_HPP
