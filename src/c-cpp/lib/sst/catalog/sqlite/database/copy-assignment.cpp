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
#include <set>
#include <string>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/sqlite/error_code_exception.hpp>

namespace sst {
namespace sqlite {

database & database::operator=(database const & src_) {
  database & src = const_cast<database &>(src_);
  database & dst = *this;
  SST_ASSERT((src.handle() != nullptr));
  SST_ASSERT((dst.handle() != nullptr));
  std::string sql;
  std::set<std::string> src_schemas;
  std::set<std::string> dst_schemas;
  for (database_list_entry & entry : src.database_list()) {
    src_schemas.emplace(std::move(entry.schema));
  }
  for (database_list_entry & entry : dst.database_list()) {
    dst_schemas.emplace(std::move(entry.schema));
  }
  for (std::string const & src_schema : src_schemas) {
    if (!dst_schemas.erase(src_schema)) {
      if (src_schema == "temp") {
        exec("DROP TABLE IF EXISTS temp.x; CREATE TEMP TABLE x (x);");
      } else {
        sql = "ATTACH ':memory:' AS ";
        quote_identifier(src_schema.c_str(), std::back_inserter(sql));
        sql += ";";
        exec(sql);
      }
    }
    sqlite3_backup * const backup =
        sqlite3_backup_init(dst,
                            src_schema.c_str(),
                            src,
                            src_schema.c_str());
    if (backup == nullptr) {
      throw sst::sqlite::error_code_exception("sqlite3_backup_init()",
                                              sqlite3_errcode(dst));
    }
    int const e = sqlite3_backup_step(backup, -1);
    (void)sqlite3_backup_finish(backup);
    if (e != SQLITE_DONE) {
      throw sst::sqlite::error_code_exception("sqlite3_backup_step()",
                                              e);
    }
  }
  for (std::string const & dst_schema : dst_schemas) {
    if (dst_schema == "temp") {
      // Note that indexes and triggers are automatically dropped when
      // their corresponding tables or views are dropped.
      for (table_list_entry const & entry : table_list("temp")) {
        sql = "DROP TABLE temp.";
        quote_identifier(entry.table.c_str(), std::back_inserter(sql));
        sql += ";";
        exec(sql);
      }
      for (view_list_entry const & entry : view_list("temp")) {
        sql = "DROP VIEW temp.";
        quote_identifier(entry.view.c_str(), std::back_inserter(sql));
        sql += ";";
        exec(sql);
      }
    } else {
      sql = "DETACH ";
      quote_identifier(dst_schema.c_str(), std::back_inserter(sql));
      sql += ";";
    }
  }
  return *this;
}

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE
