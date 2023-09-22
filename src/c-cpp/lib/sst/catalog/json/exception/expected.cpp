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

// Include first to test independence.
#include <sst/catalog/json/exception.hpp>
// Include twice to test idempotence.
#include <sst/catalog/json/exception.hpp>
//

#include <string>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/json/types.hpp>

namespace sst {
namespace json {

#define SST_F(TYPE)                                                    \
  if (types & sst::json::types::TYPE()) {                              \
    types &= ~sst::json::types::TYPE();                                \
    if (comma == nullptr) {                                            \
      comma = ", ";                                                    \
    } else {                                                           \
      s += comma;                                                      \
      if (types == sst::json::types::none()) {                         \
        s += "or ";                                                    \
      }                                                                \
    }                                                                  \
    if (#TYPE[0] != 'n' || #TYPE[2] != 'l') {                          \
      s += "a";                                                        \
      if (#TYPE[0] == 'a' || #TYPE[0] == 'o') {                        \
        s += "n";                                                      \
      }                                                                \
      s += " ";                                                        \
    }                                                                  \
    s += #TYPE;                                                        \
  }

exception exception::expected(sst::json::types types) {
  SST_ASSERT(types != sst::json::types::none());
  if (types == ~sst::json::types::null()) {
    return exception("Value must not be null");
  }
  std::string s = "Value must be ";
  char const * comma = nullptr;
  SST_F(array)
  SST_F(boolean)
  SST_F(null)
  SST_F(number)
  SST_F(object)
  SST_F(string)
  return exception(std::move(s));
}

#undef SST_F

} // namespace json
} // namespace sst
