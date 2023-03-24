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
#include <sst/catalog/sqlite/database.hpp>
// Include twice to test idempotence.
#include <sst/catalog/sqlite/database.hpp>
//

#include <sst/catalog/SST_WITH_SQLITE_SERIALIZATION.h>

#if SST_WITH_SQLITE_SERIALIZATION

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/sqlite/error_code_exception.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

database & database::deserialize(char const * const schema,
                                 unsigned char const * const buffer,
                                 sqlite3_int64 const size) {
  SST_ASSERT((handle() != nullptr));
  SST_ASSERT((schema != nullptr));
  SST_ASSERT((buffer != nullptr || size == 0));
  SST_ASSERT((size >= 0));
  unsigned char const dummy{};
  unsigned char const * const p = buffer == nullptr ? &dummy : buffer;
  int const e = sqlite3_deserialize(handle(),
                                    schema,
                                    const_cast<unsigned char *>(p),
                                    size,
                                    size,
                                    SQLITE_DESERIALIZE_READONLY);
  if (e != SQLITE_OK) {
    throw sst::sqlite::error_code_exception("sqlite3_deserialize()", e);
  }
  return *this;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE_SERIALIZATION
