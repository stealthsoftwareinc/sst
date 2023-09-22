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

#ifndef SST_CATALOG_IS_CONTIGUOUS_HPP
#define SST_CATALOG_IS_CONTIGUOUS_HPP

#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

namespace guts {
namespace is_contiguous {

//----------------------------------------------------------------------

// TODO: check for contiguous_iterator_tag

template<class, class = sst::enable_t>
struct helper_iterator : std::false_type {};

template<class T>
struct helper_iterator<
    T,
    sst::enable_if_t<
        std::is_pointer<T>::value
        || std::is_same<T,
                        typename std::array<sst::value_type_t<T>,
                                            1U>::iterator>::value
        || std::is_same<T,
                        typename std::array<sst::value_type_t<T>,
                                            1U>::const_iterator>::value
        || std::is_same<T,
                        typename std::basic_string<
                            sst::value_type_t<T>>::iterator>::value
        || std::is_same<T,
                        typename std::basic_string<sst::value_type_t<
                            T>>::const_iterator>::value
        || std::is_same<
            T,
            typename std::vector<sst::value_type_t<T>>::iterator>::value
        || std::is_same<T,
                        typename std::vector<sst::value_type_t<T>>::
                            const_iterator>::value>> : std::true_type {
};

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
struct helper : std::false_type {};

template<class T>
struct helper<T, sst::enable_if_t<sst::is_input_iterator<T>::value>>
    : helper_iterator<T> {};

template<class T>
struct helper<T[], sst::enable_t> : std::true_type {};

template<class T, std::size_t N>
struct helper<T[N], sst::enable_t> : std::true_type {};

template<class T, std::size_t N>
struct helper<std::array<T, N>, sst::enable_t> : std::true_type {};

template<class T, class Traits, class Allocator>
struct helper<std::basic_string<T, Traits, Allocator>, sst::enable_t>
    : std::true_type {};

template<class T, class Allocator>
struct helper<std::vector<T, Allocator>, sst::enable_t>
    : std::true_type {};

//----------------------------------------------------------------------

} // namespace is_contiguous
} // namespace guts

template<class T>
using is_contiguous =
    sst::guts::is_contiguous::helper<sst::remove_cvref_t<T>>;

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_EXPAND.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>

#define SST_F2(T, N, Q)                                                \
  SST_STATIC_ASSERT((N sst::is_contiguous<SST_EXPAND T Q>::value));

#define SST_F1(T, N)                                                   \
  SST_F2(T, N, )                                                       \
  SST_F2(T, N, &)                                                      \
  SST_F2(T, N, &&)                                                     \
  SST_F2(T, N, const)                                                  \
  SST_F2(T, N, const &)                                                \
  SST_F2(T, N, const &&)                                               \
  SST_F2(T, N, volatile)                                               \
  SST_F2(T, N, volatile &)                                             \
  SST_F2(T, N, volatile &&)                                            \
  SST_F2(T, N, const volatile)                                         \
  SST_F2(T, N, const volatile &)                                       \
  SST_F2(T, N, const volatile &&)

#define SST_Y(T) SST_F1(T, )

#define SST_N(T) SST_F1(T, !)

using SST_dunkhvkola = int const[];
using SST_guceascgag = int[];
using SST_xxwkvvznmc = int const[1];
using SST_zzrukamwrm = int[1];

SST_Y((SST_dunkhvkola))
SST_Y((SST_guceascgag))
SST_Y((SST_xxwkvvznmc))
SST_Y((SST_zzrukamwrm))
SST_Y((int *))
SST_Y((int const *))

SST_N((int))

#undef SST_N
#undef SST_Y
#undef SST_F1
#undef SST_F2

#endif // #if SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_IS_CONTIGUOUS_HPP
