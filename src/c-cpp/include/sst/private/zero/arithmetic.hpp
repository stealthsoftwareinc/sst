//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

#ifndef SST_PRIVATE_ZERO_ARITHMETIC_HPP
#define SST_PRIVATE_ZERO_ARITHMETIC_HPP

#include <type_traits>

#include <sst/catalog/SST_CONSTEVAL.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_arithmetic_ish.hpp>
#include <sst/catalog/is_arithmetic_like.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/zero.hpp>

namespace sst {

//----------------------------------------------------------------------

namespace guts {
namespace zero {
namespace arithmetic {

SST_DEFINE_BOOLEAN_TRAIT_1(
    has_function,
    T,
    (std::is_same<
        sst::remove_cvref_t<decltype(sst::remove_cvref_t<T>::zero())>,
        sst::remove_cvref_t<T>>::value))

} // namespace arithmetic
} // namespace zero
} // namespace guts

//----------------------------------------------------------------------

#define SST_r (sst::remove_cvref_t<T>())

template<class T>
class zero_functor<sst::enable_if_t<sst::is_arithmetic_like<T>::value>,
                   T> {

public:

  SST_CONSTEVAL auto operator()() const noexcept -> decltype(SST_r) {
    return SST_r;
  }

}; //

#undef SST_r

//----------------------------------------------------------------------

#define SST_r (sst::remove_cvref_t<T>::zero())

template<class T>
class zero_functor<
    sst::enable_if_t<!sst::is_arithmetic_like<T>::value
                     && sst::is_arithmetic_ish<T>::value
                     && guts::zero::arithmetic::has_function<T>::value>,
    T> {

public:

  constexpr auto operator()() const noexcept(noexcept(SST_r))
      -> decltype(SST_r) {
    return SST_r;
  }

}; //

#undef SST_r

//----------------------------------------------------------------------

#define SST_r (sst::remove_cvref_t<T>())

template<class T>
class zero_functor<
    sst::enable_if_t<
        !sst::is_arithmetic_like<T>::value
        && sst::is_arithmetic_ish<T>::value
        && !guts::zero::arithmetic::has_function<T>::value>,
    T> {

public:

  constexpr auto operator()() const noexcept(noexcept(SST_r))
      -> decltype(SST_r) {
    return SST_r;
  }

}; //

#undef SST_r

//----------------------------------------------------------------------

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F2(T)                                                      \
  SST_STATIC_ASSERT((std::is_same<decltype(sst::zero<T>()),            \
                                  sst::remove_cvref_t<T>>::value));    \
  SST_STATIC_ASSERT((sst::zero<T>() == sst::remove_cvref_t<T>()));     \
  SST_STATIC_ASSERT((noexcept(sst::zero<T>())))

#define SST_F(T)                                                       \
  SST_F2(T);                                                           \
  SST_F2(T const);                                                     \
  SST_F2(T volatile);                                                  \
  SST_F2(T const volatile);                                            \
  SST_F2(T const &);                                                   \
  SST_F2(T volatile &);                                                \
  SST_F2(T const volatile &)

SST_F(bool);
SST_F(char);
SST_F(char16_t);
SST_F(char32_t);
SST_F(double);
SST_F(float);
SST_F(int);
SST_F(long);
SST_F(long double);
SST_F(long long);
SST_F(short);
SST_F(signed char);
SST_F(unsigned char);
SST_F(unsigned int);
SST_F(unsigned long);
SST_F(unsigned long long);
SST_F(unsigned short);
SST_F(wchar_t);

#undef SST_F
#undef SST_F2

#endif

//----------------------------------------------------------------------

#endif // #ifndef SST_PRIVATE_ZERO_ARITHMETIC_HPP
