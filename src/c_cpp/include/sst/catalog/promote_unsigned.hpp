//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PROMOTE_UNSIGNED_HPP
#define SST_CATALOG_PROMOTE_UNSIGNED_HPP

#include <sst/catalog/integer_promote.hpp>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class T>
class promote_unsigned {
  SST_STATIC_ASSERT(std::is_integral<T>::value);

  using T1 = typename sst::integer_promote<T>::type;
  using T2 = typename std::make_unsigned<T1>::type;
  using T3 =
      typename std::conditional<std::is_const<T>::value,
                                typename std::add_const<T2>::type,
                                T2>::type;
  using T4 =
      typename std::conditional<std::is_volatile<T>::value,
                                typename std::add_volatile<T3>::type,
                                T3>::type;

public:
  using type = T4;
};

} // namespace sst

#endif // SST_CATALOG_PROMOTE_UNSIGNED_HPP
