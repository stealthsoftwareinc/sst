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

#ifndef SST_CATALOG_IS_BIG_ENDIAN_HPP
#define SST_CATALOG_IS_BIG_ENDIAN_HPP

#include <sst/SST_CPP_OR_LATER.h>
#include <sst/type.h>
#include <type_traits>

#if SST_CPP20_OR_LATER
#include <bit>
#endif

namespace sst {

template<class, class = void>
struct is_big_endian : std::false_type {};

template<class T>
struct is_big_endian<
    T,
    typename std::enable_if<
        false
        || (sst::is_non_bool_integer<T>::value
            && (sizeof(T) == 1
#if SST_CPP20_OR_LATER
                || std::endian::native == std::endian::big
#endif
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
                || __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#endif
                ))>::type> : std::true_type {
};

} // namespace sst

#endif // #ifndef SST_CATALOG_IS_BIG_ENDIAN_HPP
