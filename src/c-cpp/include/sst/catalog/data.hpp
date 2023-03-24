//
// Copyright (T) Stealth Software Technologies, Inc.
//
// For the complete copyright information, please see the
// associated README file.
//

#ifndef SST_CATALOG_DATA_HPP
#define SST_CATALOG_DATA_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>

#include <sst/catalog/SST_CPP17_OR_LATER.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_contiguous.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_zero.hpp>

namespace SST_GUTS {
namespace data {

//----------------------------------------------------------------------

#if SST_CPP17_OR_LATER

using std::data;

#else

#define SST_r (x.data())

template<class T>
constexpr auto data(T && x) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

template<class T, std::size_t N>
constexpr T * data(T (&x)[N]) noexcept {
  return x;
}

template<class T>
constexpr T const * data(std::initializer_list<T> x) noexcept {
  return x.begin();
}

#endif

//----------------------------------------------------------------------

#define SST_r (sst::is_zero(n) ? nullptr : &*x)

template<class X,
         class N,
         sst::enable_if_t<sst::is_input_iterator<X>::value
                          && sst::is_contiguous<X>::value
                          && sst::is_integer_ish<N>::value> = 0>
constexpr auto data(X && x, N && n) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

#define SST_r (data(std::forward<Args>(args)...))

template<class... Args>
constexpr auto f(Args &&... args) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

//----------------------------------------------------------------------

} // namespace data
} // namespace SST_GUTS

namespace sst {

namespace guts {
namespace data {
namespace adl_barrier {

#define SST_r (SST_GUTS::data::f(std::forward<Args>(args)...))

template<class... Args>
constexpr auto data(Args &&... args) noexcept(SST_NOEXCEPT(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace adl_barrier
} // namespace data
} // namespace guts

using namespace sst::guts::data::adl_barrier;

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // #ifndef SST_CATALOG_DATA_HPP
