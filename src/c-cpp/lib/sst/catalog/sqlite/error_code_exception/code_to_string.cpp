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

// Include first to test independence.
#include <sst/catalog/sqlite/error_code_exception.hpp>
// Include twice to test idempotence.
#include <sst/catalog/sqlite/error_code_exception.hpp>
//

#include <sst/catalog/SST_WITH_SQLITE.h>

#if SST_WITH_SQLITE

#include <iterator>
#include <string>

#include <sst/catalog/to_string.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {
namespace guts {
namespace error_code_exception {

std::string code_to_string::operator()(code_t const code) const {
  std::string s = "SQLite error code ";
  sst::to_string(code, std::back_inserter(s));
  char const * const t = sqlite3_errstr(code);
  if (t != nullptr) {
    s += ": ";
    s += t;
  }
  return s;
}

} // namespace error_code_exception
} // namespace guts
} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE
