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

#ifndef SST_CATALOG_OVERLAP_HPP
#define SST_CATALOG_OVERLAP_HPP

#include <type_traits>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/conditional_t.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/pointer_lt.hpp>

namespace sst {

template<class T1,
         class N1,
         class T2,
         class N2,
         sst::enable_if_t<
             (std::is_object<T1>::value || std::is_void<T1>::value)
             && sst::is_integer<N1>::value
             && (std::is_object<T2>::value || std::is_void<T2>::value)
             && sst::is_integer<N2>::value> = 0>
bool overlap(T1 const * const p1,
             N1 const n1,
             T2 const * const p2,
             N2 const n2) {
  SST_ASSERT((p1 != nullptr));
  SST_ASSERT((!sst::is_negative(n1)));
  SST_ASSERT((p2 != nullptr));
  SST_ASSERT((!sst::is_negative(n2)));
  void const * const q1 =
      static_cast<sst::conditional_t<std::is_void<T1>::value,
                                     unsigned char,
                                     T1> const *>(p1)
      + n1;
  void const * const q2 =
      static_cast<sst::conditional_t<std::is_void<T2>::value,
                                     unsigned char,
                                     T2> const *>(p2)
      + n2;
  return sst::pointer_lt(p1, q1) && sst::pointer_lt(p2, q2)
         && sst::pointer_lt(p2, q1) && sst::pointer_lt(p1, q2);
}

template<
    class T1,
    class N1,
    class T2,
    sst::enable_if_t<
        (std::is_object<T1>::value || std::is_void<T1>::value)
        && sst::is_integer<N1>::value
        && (std::is_object<T2>::value || std::is_void<T2>::value)> = 0>
bool overlap(T1 const * const p1, N1 const n1, T2 const * const p2) {
  return sst::overlap(p1, n1, p2, 1);
}

template<class T1,
         class T2,
         class N2,
         sst::enable_if_t<
             (std::is_object<T1>::value || std::is_void<T1>::value)
             && (std::is_object<T2>::value || std::is_void<T2>::value)
             && sst::is_integer<N2>::value> = 0>
bool overlap(T1 const * const p1, T2 const * const p2, N2 const n2) {
  return sst::overlap(p1, 1, p2, n2);
}

template<
    class T1,
    class T2,
    sst::enable_if_t<
        (std::is_object<T1>::value || std::is_void<T1>::value)
        && (std::is_object<T2>::value || std::is_void<T2>::value)> = 0>
bool overlap(T1 const * const p1, T2 const * const p2) {
  return sst::overlap(p1, 1, p2, 1);
}

} // namespace sst

#endif // #ifndef SST_CATALOG_OVERLAP_HPP
