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

#ifndef SST_PRIVATE_JSON_GET_AS_FILE_FROM_NLOHMANN_HPP
#define SST_PRIVATE_JSON_GET_AS_FILE_FROM_NLOHMANN_HPP

#include <exception>
#include <fstream>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/is_nlohmann.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/write.hpp>
#include <sst/private/json/get_as_file.hpp>

namespace sst {
namespace json {

//----------------------------------------------------------------------
// src, dst, indent
//----------------------------------------------------------------------

template<class Src, class Dst>
class get_as_file_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value>,
    void,
    Src,
    Dst,
    int> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_char_t = typename src_t::string_t::value_type;

public:

  template<class T = src_char_t,
           sst::enable_if_t<sst::is_byte<T>::value> = 0>
  void operator()(src_t const & src,
                  dst_t const & dst,
                  int const indent = 2) const {
    try {
      std::ofstream f;
      f.exceptions(f.badbit | f.failbit);
      auto * const rdbuf = f.rdbuf();
      SST_ASSERT(rdbuf != nullptr);
      rdbuf->pubsetbuf(nullptr, 0);
      try {
        f.open(dst);
      } catch (...) {
        std::throw_with_nested(
            sst::json::exception("Error opening file for writing"));
      }
      try {
        auto s = src.dump(indent < 0 ? -1 : indent, ' ', true);
        s += static_cast<src_char_t>('\n');
        sst::write(sst::c_str(s), s.size(), f);
        f.close();
      } catch (typename src_t::type_error const & e) {
        std::throw_with_nested(
            sst::json::exception("Error encoding file"));
      } catch (...) {
        std::throw_with_nested(
            sst::json::exception("Error writing file"));
      }
    } catch (sst::json::exception const & e) {
      std::throw_with_nested(e.add_file(dst));
    }
  }

}; //

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class Src, class Dst>
class get_as_file_functor<
    sst::enable_if_t<sst::json::is_nlohmann<Src>::value>,
    void,
    Src,
    Dst>
    : public get_as_file_functor<sst::enable_t, void, Src, Dst, int> {};

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_GET_AS_FILE_FROM_NLOHMANN_HPP
