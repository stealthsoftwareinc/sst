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

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/sqlite/error_code_exception.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

database & database::deserialize(char const * const schema,
                                 unsigned char * const buffer,
                                 sqlite3_int64 const size,
                                 bool const readonly,
                                 bool const copy,
                                 bool const resizable,
                                 sqlite3_int64 capacity,
                                 bool const deallocate) {
  SST_ASSERT((handle() != nullptr));
  SST_ASSERT((schema != nullptr));
  SST_ASSERT((buffer != nullptr || size == 0));
  SST_ASSERT((size >= 0));
  SST_ASSERT((readonly || capacity == 0 || capacity >= size));

  if (size == 0) {
    throw sst::sqlite::error_code_exception("sqlite3_deserialize()",
                                            SQLITE_ERROR);
  }

  if (capacity == 0) {
    capacity = size;
  }

  unsigned char * p;
  if (copy) {
    p = static_cast<unsigned char *>(sqlite3_malloc64(
        static_cast<sqlite3_uint64>(readonly ? size : capacity)));
    if (p == nullptr) {
      throw sst::sqlite::error_code_exception("sqlite3_deserialize()",
                                              SQLITE_NOMEM);
    }
    std::copy_n(buffer, size, p);
  } else {
    p = buffer;
  }

  unsigned int flags = 0U;
  if (readonly) {
    flags |= static_cast<unsigned int>(SQLITE_DESERIALIZE_READONLY);
  }
  if (!readonly && resizable) {
    flags |= static_cast<unsigned int>(SQLITE_DESERIALIZE_RESIZEABLE);
  }
  if (copy || deallocate) {
    flags |= static_cast<unsigned int>(SQLITE_DESERIALIZE_FREEONCLOSE);
  }

  int const e = sqlite3_deserialize(handle(),
                                    schema,
                                    p,
                                    size,
                                    readonly ? size : capacity,
                                    flags);
  if (e != SQLITE_OK) {
    // Note that sqlite3_deserialize() performs automatic deallocation
    // even when it fails, so we don't need to worry about p here.
    throw sst::sqlite::error_code_exception("sqlite3_deserialize()", e);
  }

  return *this;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE_SERIALIZATION
