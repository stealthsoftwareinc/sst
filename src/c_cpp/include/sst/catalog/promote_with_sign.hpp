//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_PROMOTE_WITH_SIGN_HPP
#define SST_CATALOG_PROMOTE_WITH_SIGN_HPP

#include <sst/catalog/promote_unsigned.hpp>
#include <sst/language.h>
#include <type_traits>

namespace sst {

template<class T>
class promote_with_sign {
  SST_STATIC_ASSERT(std::is_integral<T>::value);
  using T1 = typename std::conditional<
      std::is_signed<T>::value,
      decltype(+T()),
      typename promote_unsigned<T>::type>::type;
  using T2 =
      typename std::conditional<std::is_const<T>::value,
                                typename std::add_const<T1>::type,
                                T1>::type;
  using T3 =
      typename std::conditional<std::is_volatile<T>::value,
                                typename std::add_volatile<T2>::type,
                                T2>::type;

public:
  using type = T3;
};

} // namespace sst

#endif // SST_CATALOG_PROMOTE_WITH_SIGN_HPP
