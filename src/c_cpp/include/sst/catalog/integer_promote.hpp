//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PROMOTE_HPP
#define SST_CATALOG_PROMOTE_HPP

#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class T>
class integer_promote {
  SST_STATIC_ASSERT(std::is_integral<T>());
  using T1 = decltype(+T());
  using T2 = typename std::
      conditional<+std::is_const<T>(), T1 const, T1>::type;
  using T3 = typename std::
      conditional<+std::is_volatile<T>(), T2 volatile, T2>::type;

public:
  using type = T3;
};

} // namespace sst

#endif // SST_CATALOG_PROMOTE_HPP
