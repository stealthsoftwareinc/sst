//
// Copyright (T) Stealth Software Technologies, Inc.
//
// For the complete copyright information, please see the
// associated README file.
//

#ifndef SST_CATALOG_C_STR_HPP
#define SST_CATALOG_C_STR_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_char.hpp>

//----------------------------------------------------------------------

namespace sst {
namespace guts {
namespace c_str {

#define SST_r (x.c_str())

template<class T,
         sst::enable_if_t<
             std::is_pointer<
                 decltype(std::declval<T const &>().c_str())>::value
             && (sst::is_char<decltype(*std::declval<T const &>()
                                            .c_str())>::value
                 || sst::is_byte<decltype(*std::declval<T const &>()
                                               .c_str())>::value)> = 0>
auto c_str(T const & x) noexcept(noexcept(SST_r)) -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

template<class T,
         sst::enable_if_t<sst::is_char<T>::value
                          || sst::is_byte<T>::value> = 0>
T const * c_str(T const * const x) noexcept {
  return x;
}

template<class T,
         sst::enable_if_t<sst::is_char<T>::value
                          || sst::is_byte<T>::value> = 0>
T * c_str(T * const x) noexcept {
  return x;
}

} // namespace c_str
} // namespace guts
} // namespace sst

//----------------------------------------------------------------------

namespace SST_GUTS {
namespace c_str {

using sst::guts::c_str::c_str;

#define SST_r (c_str(std::forward<T>(x)))

template<class T>
auto f(T && x) noexcept(noexcept(SST_r)) -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace c_str
} // namespace SST_GUTS

//----------------------------------------------------------------------

namespace sst {

namespace guts {
namespace c_str {
namespace no_adl {

#define SST_r (SST_GUTS::c_str::f(std::forward<T>(x)))

template<class T>
auto c_str(T && x) noexcept(noexcept(SST_r)) -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace no_adl
} // namespace c_str
} // namespace guts

// ADL never matches functions imported with "using namespace".
using namespace guts::c_str::no_adl;

} // namespace sst

//----------------------------------------------------------------------

#endif // SST_CATALOG_C_STR_HPP
