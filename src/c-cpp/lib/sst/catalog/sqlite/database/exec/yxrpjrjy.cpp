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

#include <exception>
#include <functional>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/sqlite/error_code_exception.hpp>
#include <sst/catalog/sqlite/exception.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

namespace {

struct c_callback_cookie {
  std::function<void(int column_count,
                     char ** column_texts,
                     char ** column_names)> const & callback;
  std::exception_ptr exception;
};

extern "C" int c_callback(void * const cookie_ptr,
                          int const column_count,
                          char ** const column_texts,
                          char ** const column_names) {
  SST_ASSERT((cookie_ptr != nullptr));
  SST_ASSERT((column_count >= 0));
  SST_ASSERT((column_texts != nullptr));
  SST_ASSERT((column_names != nullptr));
  c_callback_cookie & cookie =
      *reinterpret_cast<c_callback_cookie *>(cookie_ptr);
  try {
    cookie.callback(column_count, column_texts, column_names);
    return 0;
  } catch (...) {
    cookie.exception = std::current_exception();
    return 1;
  }
}

} // namespace

database & database::exec(
    char const * const sql,
    std::function<void(int column_count,
                       char ** column_texts,
                       char ** column_names)> const & callback) {
  SST_ASSERT((handle() != nullptr));
  SST_ASSERT((sql != nullptr));
  c_callback_cookie cookie = {callback, nullptr};
  char * errmsg_ptr = nullptr;
  int const e =
      sqlite3_exec(handle(), sql, c_callback, &cookie, &errmsg_ptr);
  sst::basic_ptr<char> errmsg(errmsg_ptr,
                              [](char * const p) { sqlite3_free(p); });
  if (e != SQLITE_OK) {
    if (cookie.exception) {
      std::rethrow_exception(cookie.exception);
    }
    if (errmsg != nullptr) {
      try {
        throw sst::sqlite::exception(errmsg);
      } catch (sst::sqlite::exception const &) {
        std::throw_with_nested(
            sst::sqlite::error_code_exception("sqlite3_exec()", e));
      }
    }
    throw sst::sqlite::error_code_exception("sqlite3_exec()", e);
  }
  return *this;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE
