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

#ifndef SST_CATALOG_JSON_SET_FROM_FILE_HPP
#define SST_CATALOG_JSON_SET_FROM_FILE_HPP

#include <exception>
#include <fstream>
#include <string>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/if_chain_t.hpp>
#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/get_to.hpp>

// TODO: Use SST_DEFINE_ALGORITHM

namespace sst {
namespace json {

//----------------------------------------------------------------------

namespace guts {
namespace set_from_file {

template<class T, class Json = T, class CharT = char, class Src>
T & helper(Src const & src, T & dst) {
  try {
    std::basic_ifstream<CharT> f;
    f.exceptions(f.badbit | f.failbit);
    try {
      f.open(src);
    } catch (...) {
      std::throw_with_nested(
          sst::json::exception("Error opening file for reading"));
    }
    try {
      return sst::json::get_to(Json::parse(f), dst);
    } catch (sst::json::exception const &) {
      throw;
    } catch (typename Json::parse_error const &) {
      std::throw_with_nested(
          sst::json::exception("Error parsing file"));
    } catch (...) {
      std::throw_with_nested(
          sst::json::exception("Error reading file"));
    }
  } catch (sst::json::exception const & e) {
    std::throw_with_nested(e.add_file(src));
  }
}

} // namespace set_from_file
} // namespace guts

//----------------------------------------------------------------------

template<class Json_ = void,
         class T,
         class Json = sst::if_chain_t<std::is_void<Json_>, T, Json_>,
         class CharT = char>
T & set_from_file(std::string const & src, T & dst) {
  return sst::json::guts::set_from_file::helper<T, Json, CharT>(src,
                                                                dst);
}

//----------------------------------------------------------------------

template<class Json_ = void,
         class T,
         class Json = sst::if_chain_t<std::is_void<Json_>, T, Json_>,
         class CharT = char>
T & set_from_file(char const * const src, T & dst) {
  SST_ASSERT((src != nullptr));
  return sst::json::guts::set_from_file::helper<T, Json, CharT>(src,
                                                                dst);
}

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_CATALOG_JSON_SET_FROM_FILE_HPP
