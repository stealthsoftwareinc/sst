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

#ifndef SST_PRIVATE_GUTS_TO_STRING_HAS_MEMBER_FUNCTION_HPP
#define SST_PRIVATE_GUTS_TO_STRING_HAS_MEMBER_FUNCTION_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {
namespace guts {
namespace to_string {

template<class, class, class, class...>
struct has_member_function_helper : std::false_type {};

template<class Arg, class Src, class... Args>
struct has_member_function_helper<
    sst::enable_if_t<SST_COMPILES(
        std::declval<sst::remove_cvref_t<Src> const &>()
            .template to_string<Arg>(
                std::forward<Args>(std::declval<Args>())...))>,
    Arg,
    Src,
    Args...> : std::true_type {};

template<class Arg, class Src, class... Args>
using has_member_function =
    has_member_function_helper<sst::enable_t, Arg, Src, Args...>;

} // namespace to_string
} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_TO_STRING_HAS_MEMBER_FUNCTION_HPP
