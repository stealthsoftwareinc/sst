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

#ifndef SST_CATALOG_IS_EXACT_WIDTH_INTEGER_HPP
#define SST_CATALOG_IS_EXACT_WIDTH_INTEGER_HPP

#include <cstdint>
#include <type_traits>

namespace sst {

template<class, class = void>
struct is_exact_width_integer : std::false_type {};

template<class T>
struct is_exact_width_integer<
    T,
    typename std::enable_if<
        false
#ifdef INT8_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int8_t>::value
#endif
#ifdef UINT8_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint8_t>::value
#endif
#ifdef INT16_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int16_t>::value
#endif
#ifdef UINT16_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint16_t>::value
#endif
#ifdef INT32_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int32_t>::value
#endif
#ifdef UINT32_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint32_t>::value
#endif
#ifdef INT64_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::int64_t>::value
#endif
#ifdef UINT64_MAX
        || std::is_same<typename std::remove_cv<T>::type,
                        std::uint64_t>::value
#endif
        >::type> : std::true_type {
};

} // namespace sst

#endif // SST_CATALOG_IS_EXACT_WIDTH_INTEGER_HPP
