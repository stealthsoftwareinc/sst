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
#include <sst/catalog/sqlite/database.hpp>
// Include twice to test idempotence.
#include <sst/catalog/sqlite/database.hpp>
//

#include <sst/catalog/SST_WITH_SQLITE.h>

#if SST_WITH_SQLITE

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/sqlite/error_code_exception.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

sqlite3 * database::open(char const * const file) {
  SST_ASSERT((file != nullptr));
  sqlite3 * handle;
  int const e = sqlite3_open(file, &handle);
  if (e != SQLITE_OK) {
    throw sst::sqlite::error_code_exception(
        "sqlite3_open() failed to open " + sst::c_quote(file),
        e);
  }
  return handle;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE
