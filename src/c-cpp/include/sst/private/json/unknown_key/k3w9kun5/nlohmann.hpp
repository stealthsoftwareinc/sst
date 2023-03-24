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

#ifndef SST_PRIVATE_JSON_UNKNOWN_KEY_K3W9KUN5_NLOHMANN_HPP
#define SST_PRIVATE_JSON_UNKNOWN_KEY_K3W9KUN5_NLOHMANN_HPP

#include <sst/catalog/json/exception.hpp>
#include <sst/catalog/json/expect_object.hpp>
#include <sst/catalog/json/quote.hpp>

namespace sst {
namespace json {

template<class NlohmannJson>
void unknown_key(NlohmannJson const & src) {
  sst::json::expect_object(src);
  auto const it = src.begin();
  if (it != src.end()) {
    // TODO: Use sst::json::smart_quote.
    throw sst::json::exception("Unknown key: ."
                               + sst::json::quote(it.key()));
  }
}

} // namespace json
} // namespace sst

#endif // #ifndef SST_PRIVATE_JSON_UNKNOWN_KEY_K3W9KUN5_NLOHMANN_HPP
