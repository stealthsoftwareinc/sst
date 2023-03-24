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

#include <sst/catalog/SST_WITH_SQLITE.h>

#if SST_WITH_SQLITE

#include <iterator>
#include <string>
#include <vector>

#include <sst/catalog/SST_ASSERT.h>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

std::vector<database::view_list_entry>
database::view_list(char const * const schema) {
  SST_ASSERT((handle() != nullptr));
  std::vector<view_list_entry> list;
  if (schema != nullptr) {
    std::string sql = "SELECT name FROM ";
    quote_identifier(schema, std::back_inserter(sql));
    sql += ".sqlite_master WHERE type = 'view';";
    exec(sql, [&](int, char ** const column_texts, char **) {
      list.emplace_back();
      list.back().schema = schema;
      list.back().view = column_texts[0];
    });
  } else {
    std::string sql;
    std::vector<database_list_entry> const xs = database_list();
    for (database_list_entry const & x : xs) {
      sql = "SELECT name FROM ";
      quote_identifier(x.schema.c_str(), std::back_inserter(sql));
      sql += ".sqlite_master WHERE type = 'view';";
      exec(sql, [&](int, char ** const column_texts, char **) {
        list.emplace_back();
        list.back().schema = x.schema;
        list.back().view = column_texts[0];
      });
    }
  }
  return list;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE
