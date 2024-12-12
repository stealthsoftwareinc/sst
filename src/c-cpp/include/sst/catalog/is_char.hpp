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

#ifndef SST_CATALOG_IS_CHAR_HPP
#define SST_CATALOG_IS_CHAR_HPP

#include <type_traits>

#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/SST_DEFINE_BOOLEAN_TRAIT_1.hpp>
#include <sst/catalog/decay_t.hpp>
#include <sst/catalog/dependent_false.hpp>

namespace sst {

#define SST_F(X) (std::is_same<sst::decay_t<T>, X>::value)

namespace guts {
namespace is_char {

#if SST_CPP20_OR_LATER
SST_DEFINE_BOOLEAN_TRAIT_1(f1, T, (SST_F(char8_t)))
#else
SST_DEFINE_BOOLEAN_TRAIT_1(f1, T, (sst::dependent_false<T>::value))
#endif

} // namespace is_char
} // namespace guts

SST_DEFINE_BOOLEAN_TRAIT_1(is_char,
                           T,
                           (SST_F(char) || guts::is_char::f1<T>::value
                            || SST_F(char16_t) || SST_F(char32_t)
                            || SST_F(wchar_t)))

#undef SST_F

} // namespace sst

#endif // SST_CATALOG_IS_CHAR_HPP
