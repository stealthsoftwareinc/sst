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

#ifndef SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_SST_FROM_NLOHMANN_HPP
#define SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_SST_FROM_NLOHMANN_HPP

#include <exception>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/json/guts/get_to/from_nlohmann/have_sst_from_nlohmann.hpp>

namespace sst {
namespace json {

template<class Src, class Dst>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && sst::json::guts::get_to::from_nlohmann_json::
                         have_sst_from_nlohmann_json<Src, Dst>::value>,
    void,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t & operator()(src_t const & src, dst_t & dst) const {
    try {
      sst_from_nlohmann_json(src, dst);
      return dst;
    } catch (...) {
      std::throw_with_nested(sst::json::exception::invalid_value());
    }
  }

}; //

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_SST_FROM_NLOHMANN_HPP
