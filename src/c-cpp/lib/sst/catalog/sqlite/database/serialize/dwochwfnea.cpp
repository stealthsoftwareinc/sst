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

#include <algorithm>
#include <new>
#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/checked_resize.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

std::vector<unsigned char>
database::serialize(char const * const schema) {
  SST_ASSERT((handle() != nullptr));
  SST_ASSERT((schema != nullptr));
  sqlite3_int64 size = 0;
  sst::basic_ptr<unsigned char> buffer(
      sqlite3_serialize(handle(),
                        schema,
                        &size,
                        SQLITE_SERIALIZE_NOCOPY),
      [](unsigned char *) {});
  if (buffer == nullptr) {
    buffer = sst::basic_ptr<unsigned char>(
        sqlite3_serialize(handle(), schema, &size, 0U),
        [](unsigned char * const p) { sqlite3_free(p); });
    if (buffer == nullptr) {
      throw std::bad_alloc();
    }
  }
  std::vector<unsigned char> v;
  sst::checked_resize(v, size);
  if (size > 0) {
    std::copy_n(buffer.get(), size, v.data());
  }
  return v;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE_SERIALIZATION
