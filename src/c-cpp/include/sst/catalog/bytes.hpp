//
// Copyright (T) Stealth Software Technologies, Inc.
//
// For the complete copyright information, please see the
// associated README file.
//

#ifndef SST_CATALOG_BYTES_HPP
#define SST_CATALOG_BYTES_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/conditional_t.hpp>
#include <sst/catalog/data.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/remove_pointer_t.hpp>

namespace sst {

#define SST_a (sst::data(std::declval<Args &&>()...))
#define SST_b (sst::data(std::forward<Args>(args)...))

#define SST_r                                                          \
  (reinterpret_cast<sst::conditional_t<                                \
       std::is_const<sst::remove_pointer_t<decltype(SST_b)>>::value,   \
       unsigned char const *,                                          \
       unsigned char *>>(SST_b))

template<class... Args,
         sst::enable_if_t<sst::is_byte<decltype(*SST_a)>::value> = 0>
auto bytes(Args &&... args) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

#undef SST_a
#undef SST_b

} // namespace sst

#endif // #ifndef SST_CATALOG_BYTES_HPP
