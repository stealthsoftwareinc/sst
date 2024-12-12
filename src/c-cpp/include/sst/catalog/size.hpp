//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#ifndef SST_CATALOG_SIZE_HPP
#define SST_CATALOG_SIZE_HPP

#include <cstddef>
#include <iterator>
#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/is_char.hpp>

//----------------------------------------------------------------------
//
// This overload will be called to fall back to ADL when none of our
// overloads in sst::guts::size_no_adl match.
//

namespace SST_GUTS {
namespace size_adl {

#define SST_r (size(std::forward<C>(c)))

template<class C>
constexpr auto f(C && c) noexcept(noexcept(SST_r)) -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace size_adl
} // namespace SST_GUTS

//----------------------------------------------------------------------

namespace sst {

namespace guts {
namespace size_no_adl {

// When an array's element type is a type that cannot be used for a
// string literal, report the full array size.
template<class T,
         std::size_t N,
         sst::enable_if_t<!sst::is_char<T>::value> = 0>
constexpr std::size_t size(T const (&)[N]) noexcept {
  return N;
}

// When an array's element type is a type that can be used for a string
// literal, report the full array size minus an assumed null terminator.
// This feels wrong, but it's almost always what is wanted in practice
// because this overload is almost always called on a string literal.
template<class T,
         std::size_t N,
         sst::enable_if_t<sst::is_char<T>::value> = 0>
constexpr std::size_t size(T const (&)[N]) noexcept {
  return N - static_cast<std::size_t>(1);
}

SST_DEFINE_BOOLEAN_TRAIT_1(has_member_function,
                           C,
                           (SST_COMPILES(std::declval<C &&>().size())))

#define SST_r (std::forward<C>(c).size())

template<class C, sst::enable_if_t<has_member_function<C>::value> = 0>
constexpr auto size(C && c) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

#define SST_r (SST_GUTS::size_adl::f(std::forward<C>(c)))

template<class C, sst::enable_if_t<!has_member_function<C>::value> = 0>
constexpr auto size(C && c) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace size_no_adl
} // namespace guts

// ADL never matches functions imported with "using namespace".
using namespace guts::size_no_adl;

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <cstddef>

#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F(A, B)                                                    \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<decltype((A)), decltype((B))>::value));            \
  SST_STATIC_ASSERT(((A) == (B)));

SST_F((sst::size("")), (std::size_t(0)))
SST_F((sst::size("a")), (std::size_t(1)))
SST_F((sst::size("ab")), (std::size_t(2)))
SST_F((sst::size("abc")), (std::size_t(3)))

SST_F((sst::size(u8"")), (std::size_t(0)))
SST_F((sst::size(u8"a")), (std::size_t(1)))
SST_F((sst::size(u8"ab")), (std::size_t(2)))
SST_F((sst::size(u8"abc")), (std::size_t(3)))

SST_F((sst::size(u"")), (std::size_t(0)))
SST_F((sst::size(u"a")), (std::size_t(1)))
SST_F((sst::size(u"ab")), (std::size_t(2)))
SST_F((sst::size(u"abc")), (std::size_t(3)))

SST_F((sst::size(U"")), (std::size_t(0)))
SST_F((sst::size(U"a")), (std::size_t(1)))
SST_F((sst::size(U"ab")), (std::size_t(2)))
SST_F((sst::size(U"abc")), (std::size_t(3)))

SST_F((sst::size(L"")), (std::size_t(0)))
SST_F((sst::size(L"a")), (std::size_t(1)))
SST_F((sst::size(L"ab")), (std::size_t(2)))
SST_F((sst::size(L"abc")), (std::size_t(3)))

extern char SST_gfoishtsbvzoygxn[26960];
SST_F((sst::size(SST_gfoishtsbvzoygxn)), (std::size_t(26959)))

extern int SST_uemfxmzbnvaucbpq[30935];
SST_F((sst::size(SST_uemfxmzbnvaucbpq)), (std::size_t(30935)))

struct SST_ccufhkdhgcjtwpdm {
  constexpr unsigned long long size() const & {
    return 5394719131815956459ULL;
  }
};
SST_F((sst::size(SST_ccufhkdhgcjtwpdm())), (5394719131815956459ULL))

struct SST_wbihaqbaxsyiveee {
  friend constexpr unsigned long long
  size(SST_wbihaqbaxsyiveee const &) {
    return 4597317360665341689ULL;
  }
};
SST_F((sst::size(SST_wbihaqbaxsyiveee())), (4597317360665341689ULL))

struct SST_ktglrfcgwzozudaf {
  constexpr unsigned long long size() const & {
    return 8115258231532815313ULL;
  }
  friend constexpr unsigned long long
  size(SST_ktglrfcgwzozudaf const &) {
    return 8552906936696424961ULL;
  }
};
SST_F((sst::size(SST_ktglrfcgwzozudaf())), (8115258231532815313ULL))

#undef SST_F

#endif // SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_SIZE_HPP
