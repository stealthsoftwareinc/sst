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

#ifndef SST_PRIVATE_JSON_GET_FROM_FILE_STRING_HPP
#define SST_PRIVATE_JSON_GET_FROM_FILE_STRING_HPP

#include <string>
#include <type_traits>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/private/json/get_from_file.hpp>

namespace sst {
namespace json {

//----------------------------------------------------------------------

template<class T, class Json, class Path>
class get_from_file_functor<
    sst::enable_if_t<
        std::is_convertible<Path, std::string const &>::value
        && !std::is_convertible<Path, char const *>::value>,
    T,
    Json,
    Path> {

public:

#define SST_r (sst::json::get_from_file<T, Json>(path.c_str()))

  auto operator()(std::string const & path) const -> decltype(SST_r) {
    return SST_r;
  }

#undef SST_r

}; //

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_GET_FROM_FILE_STRING_HPP
