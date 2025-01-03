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

#ifndef SST_PRIVATE_JSON_GET_FROM_FILE_BASIC_IFSTREAM_HPP
#define SST_PRIVATE_JSON_GET_FROM_FILE_BASIC_IFSTREAM_HPP

#include <fstream>
#include <istream>

#include <sst/catalog/enable_t.hpp>
#include <sst/private/json/get_from_file.hpp>

namespace sst {
namespace json {

//----------------------------------------------------------------------

template<class T, class Json, class... Args>
class get_from_file_functor<sst::enable_t,
                            T,
                            Json,
                            std::basic_ifstream<Args...> &>
    : public sst::json::get_from_file_functor<
          sst::enable_t,
          T,
          Json,
          std::basic_istream<Args...> &> {};

//----------------------------------------------------------------------

template<class T, class Json, class... Args>
class get_from_file_functor<sst::enable_t,
                            T,
                            Json,
                            std::basic_ifstream<Args...> &&>
    : public sst::json::get_from_file_functor<
          sst::enable_t,
          T,
          Json,
          std::basic_istream<Args...> &> {};

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_GET_FROM_FILE_BASIC_IFSTREAM_HPP
