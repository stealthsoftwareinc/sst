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

#ifndef SST_CATALOG_POINTER_LT_HPP
#define SST_CATALOG_POINTER_LT_HPP

#include <functional>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/enable_if_t.hpp>

namespace sst {

//
// Note that C++ guarantees that std::less and friends define a total
// order over all pointers, not just those that point into the same
// object. See the following references:
//
//     * C++11 (N3337) 20.8.5p8
//     * C++14 (N4140) 20.9.5p14
//     * C++17 (N4659) 23.14.7p2
//     * C++20 (N4860) 20.14.7p2
//

template<
    class T1,
    class T2,
    sst::enable_if_t<
        (std::is_object<T1>::value || std::is_void<T1>::value)
        && (std::is_object<T2>::value || std::is_void<T2>::value)> = 0>
bool pointer_lt(T1 const * const p1, T2 const * const p2) {
  SST_ASSERT((p1 != nullptr));
  SST_ASSERT((p2 != nullptr));
  return std::less<void const *>()(static_cast<void const *>(p1),
                                   static_cast<void const *>(p2));
}

} // namespace sst

#endif // #ifndef SST_CATALOG_POINTER_LT_HPP
