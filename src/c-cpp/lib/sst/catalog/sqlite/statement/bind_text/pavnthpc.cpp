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
#include <sst/catalog/sqlite/statement.hpp>
// Include twice to test idempotence.
#include <sst/catalog/sqlite/statement.hpp>
//

#include <sst/catalog/SST_WITH_SQLITE.h>

#if SST_WITH_SQLITE

#include <string>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/sqlite/error_code_exception.hpp>
#include <sst/catalog/type_max.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

statement & statement::bind_text(int const index,
                                 std::string const & text) {
  SST_ASSERT((handle() != nullptr));
  SST_ASSERT((index >= 1));
  if (text.size() > sst::type_max<sqlite3_uint64>::value) {
    return bind_text(index, text.c_str());
  }
  int const e =
      sqlite3_bind_text64(handle(),
                          index,
                          text.c_str(),
                          static_cast<sqlite3_uint64>(text.size()),
                          nullptr,
                          SQLITE_UTF8);
  if (e != SQLITE_OK) {
    throw sst::sqlite::error_code_exception("sqlite3_bind_text64()", e);
  }
  return *this;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE
