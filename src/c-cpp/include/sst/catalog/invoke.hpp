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

#ifndef SST_CATALOG_INVOKE_HPP
#define SST_CATALOG_INVOKE_HPP

#include <functional>
#include <type_traits>
#include <utility>

#include <sst/catalog/enable_if_t.hpp>

namespace sst {

template<class Callable,
         class... Args,
         sst::enable_if_t<std::is_member_pointer<
             typename std::decay<Callable>::type>::value> = 0>
auto constexpr invoke(Callable && func, Args &&... args) noexcept(
    noexcept(std::mem_fn(func)(std::forward<Args>(args)...)))
    -> decltype(std::mem_fn(func)(std::forward<Args>(args)...)) {
  return std::mem_fn(func)(std::forward<Args>(args)...);
}

template<class Callable,
         class... Args,
         sst::enable_if_t<!std::is_member_pointer<
             typename std::decay<Callable>::type>::value> = 0>
auto constexpr invoke(Callable && func, Args &&... args) noexcept(
    noexcept(std::forward<Callable>(func)(std::forward<Args>(args)...)))
    -> decltype(std::forward<Callable>(func)(
        std::forward<Args>(args)...)) {
  return std::forward<Callable>(func)(std::forward<Args>(args)...);
}

} // namespace sst

#endif // #ifndef SST_CATALOG_INVOKE_HPP
