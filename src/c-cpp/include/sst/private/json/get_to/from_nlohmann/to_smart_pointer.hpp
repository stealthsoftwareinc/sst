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

#ifndef SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_TO_SMART_POINTER_HPP
#define SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_TO_SMART_POINTER_HPP

#include <type_traits>
#include <utility>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_smart_pointer.hpp>
#include <sst/catalog/json/get_as.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/json/get_as.hpp>
#include <sst/private/json/get_to.hpp>
#include <sst/private/json/guts/get_to/from_nlohmann/have_sst_from_nlohmann.hpp>

namespace sst {
namespace json {

template<class Src, class Dst>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && !sst::json::guts::get_to::from_nlohmann_json::
                            have_sst_from_nlohmann_json<Src, Dst>::value
                     && sst::is_smart_pointer<Dst>::value>,
    void,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using dst_value_t =
      sst::remove_cvref_t<decltype(*std::declval<dst_t>())>;

public:

  // Note that we need *dst = std::move(x) to be noexcept to achieve
  // strong exception safety. Otherwise, it could corrupt *dst.
  template<class DstValue = dst_value_t,
           sst::enable_if_t<
               std::is_move_assignable<DstValue>::value
               && noexcept(std::declval<DstValue &>() =
                               std::declval<DstValue &&>())> = 0>
  dst_t & operator()(src_t const & src, dst_t & dst) const {
    dst_value_t x = sst::json::get_as<dst_value_t>(src);
    if (dst == nullptr) {
      dst.reset(new dst_value_t(std::move(x)));
    } else {
      *dst = std::move(x);
    }
    return dst;
  }

  template<
      class DstValue = dst_value_t,
      sst::enable_if_t<!std::is_move_assignable<DstValue>::value> = 0>
  dst_t & operator()(src_t const & src, dst_t & dst) const {
    dst_value_t x = sst::json::get_as<dst_value_t>(src);
    dst.reset(new dst_value_t(std::move(x)));
    return dst;
  }

}; //

} // namespace json
} // namespace sst

#endif // #ifndef SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_TO_SMART_POINTER_HPP
