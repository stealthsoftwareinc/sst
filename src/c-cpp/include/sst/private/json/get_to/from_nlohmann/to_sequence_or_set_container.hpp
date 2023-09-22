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

#ifndef SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_TO_SEQUENCE_OR_SET_CONTAINER_HPP
#define SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_TO_SEQUENCE_OR_SET_CONTAINER_HPP

#include <exception>
#include <iterator>

#include <sst/catalog/code_point_decoder.hpp>
#include <sst/catalog/code_point_encoder.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/from_hex.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_sequence_container.hpp>
#include <sst/catalog/is_set_container.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/expect.hpp>
#include <sst/catalog/json/expect_array.hpp>
#include <sst/catalog/json/get_as.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/json/types.hpp>
#include <sst/catalog/pick_utf_encoding.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/text_encoding.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/json/get_as.hpp>
#include <sst/private/json/get_to.hpp>
#include <sst/private/json/guts/get_to/from_nlohmann/have_sst_from_nlohmann.hpp>

namespace sst {
namespace json {

namespace guts {
namespace get_to {
namespace from_nlohmann_json {
namespace to_sequence_or_set_container {

template<class src_t, class dst_t>
void do_array_src(src_t const & src, dst_t & dst) {
  using dst_value_t = sst::value_type_t<dst_t>;
  dst.clear();
  for (decltype(+src.size()) i = 0; i != src.size(); ++i) {
    try {
      dst.insert(dst.end(), sst::json::get_as<dst_value_t>(src[i]));
    } catch (sst::json::exception const & e) {
      std::throw_with_nested(e.add_index(i));
    }
  }
}

} // namespace to_sequence_or_set_container
} // namespace from_nlohmann_json
} // namespace get_to
} // namespace guts

template<class Src, class Dst>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && !sst::json::guts::get_to::from_nlohmann_json::
                            have_sst_from_nlohmann_json<Src, Dst>::value
                     && !sst::json::is_nlohmann<Dst>::value
                     && (sst::is_sequence_container<Dst>::value
                         || sst::is_set_container<Dst>::value)
                     && sst::is_char<sst::value_type_t<Dst>>::value>,
    void,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using dst_value_t = sst::value_type_t<Dst>;

  static constexpr sst::text_encoding src_encoding =
      sst::text_encoding::utf_8;
  static constexpr sst::text_encoding dst_encoding =
      sst::pick_utf_encoding<dst_value_t>();

public:

  template<sst::text_encoding X = dst_encoding,
           sst::enable_if_t<X == sst::text_encoding::utf_8> = 0>
  dst_t & operator()(src_t const & src, dst_t & dst) const {
    if (src.is_array()) {
      using namespace guts::get_to::from_nlohmann_json::
          to_sequence_or_set_container;
      do_array_src(src, dst);
    } else if (src.is_string()) {
      dst.clear();
      for (auto const & c :
           src.template get_ref<typename src_t::string_t const &>()) {
        dst.insert(dst.end(), static_cast<dst_value_t>(c));
      }
    } else {
      sst::json::expect(src,
                        sst::json::types::array()
                            | sst::json::types::string());
    }
    return dst;
  }

  template<sst::text_encoding X = dst_encoding,
           sst::enable_if_t<X != sst::text_encoding::utf_8> = 0>
  dst_t & operator()(src_t const & src, dst_t & dst) const {
    if (src.is_array()) {
      using namespace guts::get_to::from_nlohmann_json::
          to_sequence_or_set_container;
      do_array_src(src, dst);
    } else if (src.is_string()) {
      dst.clear();
      auto decoder = sst::code_point_decoder<src_encoding>();
      auto encoder = sst::code_point_encoder<dst_encoding>();
      for (auto const & c :
           src.template get_ref<typename src_t::string_t const &>()) {
        decoder.put(c);
        if (decoder.ready()) {
          encoder.put(decoder.get());
          auto const p = encoder.get();
          auto const n = encoder.size();
          for (decltype(+n) j = 0; j != n; ++j) {
            dst.insert(dst.end(), static_cast<dst_value_t>(p[j]));
          }
        }
      }
      decoder.flush();
      if (decoder.ready()) {
        encoder.put(decoder.get());
        auto const p = encoder.get();
        auto const n = encoder.size();
        for (decltype(+n) j = 0; j != n; ++j) {
          dst.insert(dst.end(), static_cast<dst_value_t>(p[j]));
        }
      }
    } else {
      sst::json::expect(src,
                        sst::json::types::array()
                            | sst::json::types::string());
    }
    return dst;
  }

}; //

template<class Src, class Dst>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && !sst::json::guts::get_to::from_nlohmann_json::
                            have_sst_from_nlohmann_json<Src, Dst>::value
                     && !sst::json::is_nlohmann<Dst>::value
                     && (sst::is_sequence_container<Dst>::value
                         || sst::is_set_container<Dst>::value)
                     && !sst::is_char<sst::value_type_t<Dst>>::value
                     && sst::is_byte<sst::value_type_t<Dst>>::value>,
    void,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using dst_value_t = sst::value_type_t<Dst>;

public:

  dst_t & operator()(src_t const & src, dst_t & dst) const {
    if (src.is_array()) {
      using namespace guts::get_to::from_nlohmann_json::
          to_sequence_or_set_container;
      do_array_src(src, dst);
    } else if (src.is_string()) {
      dst.clear();
      sst::from_hex(
          src.template get_ref<typename src_t::string_t const &>(),
          std::inserter(dst, dst.end()));
    } else {
      sst::json::expect(src,
                        sst::json::types::array()
                            | sst::json::types::string());
    }
    return dst;
  }

}; //

template<class Src, class Dst>
class get_to_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value
                     && !sst::json::guts::get_to::from_nlohmann_json::
                            have_sst_from_nlohmann_json<Src, Dst>::value
                     && !sst::json::is_nlohmann<Dst>::value
                     && (sst::is_sequence_container<Dst>::value
                         || sst::is_set_container<Dst>::value)
                     && !sst::is_char<sst::value_type_t<Dst>>::value
                     && !sst::is_byte<sst::value_type_t<Dst>>::value>,
    void,
    Src,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using dst_value_t = sst::value_type_t<Dst>;

public:

  dst_t & operator()(src_t const & src, dst_t & dst) const {
    sst::json::expect_array(src);
    using namespace guts::get_to::from_nlohmann_json::
        to_sequence_or_set_container;
    do_array_src(src, dst);
    return dst;
  }

}; //

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_GET_TO_FROM_NLOHMANN_TO_SEQUENCE_OR_SET_CONTAINER_HPP
