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

//
// To implement sst::json::get_as(src, ...), the first technique in the
// following list that works will be used:
//
//    1. return Dst(src, ...);
//    2. return Dst::from_json(src, ...);
//    3. Dst dst; sst::json::get_to(src, dst, ...); return dst;
//

#ifndef SST_CATALOG_JSON_GET_AS_HPP
#define SST_CATALOG_JSON_GET_AS_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_static_castable.hpp>
#include <sst/catalog/json/get_to.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/json/get_as.hpp>
#include <sst/private/json/get_to.hpp>

//----------------------------------------------------------------------
// Determine the technique
//----------------------------------------------------------------------

namespace sst {
namespace json {
namespace guts {
namespace get_as {

template<class, class, class, class...>
struct use_technique_1 : std::false_type {};

template<class Dst, class Json>
struct use_technique_1<
    sst::enable_if_t<
        SST_COMPILES(sst::remove_cvref_t<Dst>(std::declval<Json>()))
        && !sst::is_static_castable<Json,
                                    sst::remove_cvref_t<Dst>>::value>,
    Dst,
    Json> : std::true_type {};

template<class Dst, class Json, class Arg1, class... Args>
struct use_technique_1<
    sst::enable_if_t<SST_COMPILES(
        sst::remove_cvref_t<Dst>(std::declval<Json>(),
                                 std::declval<Arg1>(),
                                 std::declval<Args>()...))>,
    Dst,
    Json,
    Arg1,
    Args...> : std::true_type {};

template<class, class, class, class...>
struct use_technique_2 : std::false_type {};

template<class Dst, class Json, class... Args>
struct use_technique_2<
    sst::enable_if_t<
        !use_technique_1<sst::enable_t, Dst, Json, Args...>::value
        && std::is_same<decltype(sst::remove_cvref_t<Dst>::from_json(
                            std::declval<Json>(),
                            std::declval<Args>()...)),
                        sst::remove_cvref_t<Dst>>::value>,
    Dst,
    Json,
    Args...> : std::true_type {};

template<class, class, class, class...>
struct use_technique_3 : std::false_type {};

template<class Dst, class Json, class... Args>
struct use_technique_3<
    sst::enable_if_t<
        !use_technique_1<sst::enable_t, Dst, Json, Args...>::value
        && !use_technique_2<sst::enable_t, Dst, Json, Args...>::value
        && SST_COMPILES(sst::remove_cvref_t<Dst>())
        && SST_COMPILES(sst::json::get_to(
            std::declval<Json>(),
            std::declval<sst::remove_cvref_t<Dst> &>(),
            std::declval<Args>()...))>,
    Dst,
    Json,
    Args...> : std::true_type {};

} // namespace get_as
} // namespace guts
} // namespace json
} // namespace sst

//----------------------------------------------------------------------
// Use the technique
//----------------------------------------------------------------------

namespace sst {
namespace json {

template<class Dst, class... Args>
class get_as_functor<
    sst::enable_if_t<guts::get_as::use_technique_1<sst::enable_t,
                                                   Dst,
                                                   Args...>::value>,
    Dst,
    Args...> {

  using dst_t = sst::remove_cvref_t<Dst>;

public:

#define SST_r (dst_t(std::forward<Args2>(args)...))

  template<class... Args2>
  auto operator()(Args2 &&... args) const noexcept(noexcept(SST_r))
      -> decltype(SST_r) {
    return SST_r;
  }

#undef SST_r

}; //

template<class Dst, class... Args>
class get_as_functor<
    sst::enable_if_t<guts::get_as::use_technique_2<sst::enable_t,
                                                   Dst,
                                                   Args...>::value>,
    Dst,
    Args...> {

  using dst_t = sst::remove_cvref_t<Dst>;

public:

#define SST_r (dst_t::from_json(std::forward<Args2>(args)...))

  template<class... Args2>
  auto operator()(Args2 &&... args) const noexcept(noexcept(SST_r))
      -> decltype(SST_r) {
    return SST_r;
  }

#undef SST_r

}; //

template<class Dst, class Json, class... Args>
class get_as_functor<
    sst::enable_if_t<
        guts::get_as::
            use_technique_3<sst::enable_t, Dst, Json, Args...>::value>,
    Dst,
    Json,
    Args...> {

  using dst_t = sst::remove_cvref_t<Dst>;

public:

  template<class Json2, class... Args2>
  dst_t operator()(Json2 && src, Args2 &&... args) const
      noexcept(noexcept(dst_t()) && noexcept(
          sst::json::get_to(std::forward<Json2>(src),
                            std::declval<dst_t &>(),
                            std::forward<Args2>(args)...))) {
    dst_t dst;
    sst::json::get_to(std::forward<Json2>(src),
                      dst,
                      std::forward<Args2>(args)...);
    return dst;
  }

}; //

} // namespace json
} // namespace sst

//----------------------------------------------------------------------

#endif // SST_CATALOG_JSON_GET_AS_HPP
