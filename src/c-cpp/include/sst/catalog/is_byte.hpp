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

#ifndef SST_CATALOG_IS_BYTE_HPP
#define SST_CATALOG_IS_BYTE_HPP

#include <type_traits>

#include <sst/catalog/SST_CPP17_OR_LATER.h>
#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

#if SST_CPP17_OR_LATER
#include <cstddef>
#endif

namespace sst {

#define SST_F(X) (std::is_same<sst::remove_cvref_t<T>, X>::value)

namespace guts {
namespace is_byte {

#if SST_CPP17_OR_LATER
using x_std_byte = std::byte;
#else
using x_std_byte = unsigned char;
#endif

#if SST_CPP20_OR_LATER
using x_char8_t = char8_t;
#else
using x_char8_t = unsigned char;
#endif

} // namespace is_byte
} // namespace guts

SST_DEFINE_BOOLEAN_TRAIT_1(is_byte,
                           T,
                           (SST_F(char) || SST_F(signed char)
                            || SST_F(unsigned char)
                            || SST_F(guts::is_byte::x_std_byte)
                            || SST_F(guts::is_byte::x_char8_t)))

#undef SST_F

} // namespace sst

#endif // #ifndef SST_CATALOG_IS_BYTE_HPP
