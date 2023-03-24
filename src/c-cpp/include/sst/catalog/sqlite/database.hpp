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

#ifndef SST_CATALOG_SQLITE_DATABASE_HPP
#define SST_CATALOG_SQLITE_DATABASE_HPP

#include <sst/catalog/SST_WITH_SQLITE.h>

#if SST_WITH_SQLITE

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_DEFAULT_NOEXCEPT.hpp>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_WITH_SQLITE_SERIALIZATION.h>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/data.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_contiguous.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_iterable.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/sqlite/error_code_exception.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

class database {

  template<class Dst>
  void quote_identifier(char const * src, Dst dst) {
    *dst = '"';
    ++dst;
    for (; *src != '\0'; ++src) {
      *dst = *src;
      ++dst;
      if (*src == '"') {
        *dst = *src;
        ++dst;
      }
    }
    *dst = '"';
    ++dst;
  }

  //--------------------------------------------------------------------
  // handle
  //--------------------------------------------------------------------

private:

  sst::basic_ptr<sqlite3> handle_{nullptr, [](sqlite3 * const p) {
                                    (void)sqlite3_close_v2(p);
                                  }};

public:

  SST_NODISCARD() sqlite3 * handle() const noexcept {
    return handle_.get();
  }

  SST_NODISCARD() operator sqlite3 *() const noexcept {
    return handle_.get();
  }

  //--------------------------------------------------------------------
  // open
  //--------------------------------------------------------------------

private:

  static sqlite3 * open(char const * file);

  //--------------------------------------------------------------------
  // Non-default constructors
  //--------------------------------------------------------------------

public:

  explicit database(char const * const file) {
    SST_ASSERT((file != nullptr));
    handle_ = open(file);
  }

  explicit database(std::string const & file) : database(file.c_str()) {
  }

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

public:

  database() : database(":memory:") {
  }

  database(database const & other) {
    *this = other;
  }

  database & operator=(database const & other);

  database(database &&) SST_DEFAULT_NOEXCEPT(true) = default;

  database & operator=(database &&)
      SST_DEFAULT_NOEXCEPT(true) = default;

  ~database() SST_DEFAULT_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // database_list
  //--------------------------------------------------------------------

public:

  struct database_list_entry {
    std::string schema;
    std::string file;
  };

  // ID: axmotrij
  std::vector<database_list_entry> database_list();

  //--------------------------------------------------------------------
  // deserialize
  //--------------------------------------------------------------------

#if SST_WITH_SQLITE_SERIALIZATION

public:

  // ID: fttcexwfwu
  database & deserialize(char const * const schema,
                         unsigned char const * const buffer,
                         sqlite3_int64 const size);

  // ID: vxpizfwfzi
  template<class Size,
           sst::enable_if_t<sst::is_integer_ish<Size>::value
                            && !std::is_same<sst::remove_cvref_t<Size>,
                                             sqlite3_int64>::value> = 0>
  database & deserialize(char const * schema,
                         unsigned char const * buffer,
                         Size const & size) {
    return deserialize(schema,
                       buffer,
                       sst::checked_cast<sqlite3_int64>(size));
  }

  // ID: enxnulmzqp
  template<
      class Buffer,
      sst::enable_if_t<sst::is_iterable<Buffer, sst::is_byte>::value
                       && sst::is_contiguous<Buffer>::value> = 0>
  database & deserialize(char const * schema, Buffer const & buffer) {
    auto const n = sst::size(buffer);
    auto const p = sst::data(sst::cbegin(buffer), n);
    auto const q = reinterpret_cast<unsigned char const *>(p);
    return deserialize(schema, q, n);
  }

#endif // #if SST_WITH_SQLITE_SERIALIZATION

  //--------------------------------------------------------------------
  // exec
  //--------------------------------------------------------------------

public:

  // ID: buvxxabr
  database & exec(char const * sql);

  // ID: jdnqanjv
  database & exec(std::string const & sql) {
    return exec(sql.c_str());
  }

  // ID: yxrpjrjy
  database &
  exec(char const * sql,
       std::function<void(int column_count,
                          char ** column_texts,
                          char ** column_names)> const & callback);

  // ID: wrddnsio
  database &
  exec(std::string const & sql,
       std::function<void(int column_count,
                          char ** column_texts,
                          char ** column_names)> const & callback) {
    return exec(sql.c_str(), callback);
  }

  //--------------------------------------------------------------------
  // serialize
  //--------------------------------------------------------------------

#if SST_WITH_SQLITE_SERIALIZATION

public:

  // ID: dwochwfnea
  std::vector<unsigned char> serialize(char const * schema);

#endif // #if SST_WITH_SQLITE_SERIALIZATION

  //--------------------------------------------------------------------
  // table_list
  //--------------------------------------------------------------------

public:

  struct table_list_entry {
    std::string schema;
    std::string table;
  };

  // ID: wzjrnzms
  std::vector<table_list_entry>
  table_list(char const * schema = nullptr);

  // ID: lfgtpdbd
  std::vector<table_list_entry> table_list(std::string const & schema) {
    return table_list(schema.c_str());
  }

  //--------------------------------------------------------------------
  // view_list
  //--------------------------------------------------------------------

public:

  struct view_list_entry {
    std::string schema;
    std::string view;
  };

  // ID: fvccjmib
  std::vector<view_list_entry> view_list(char const * schema = nullptr);

  // ID: zvjzvwdv
  std::vector<view_list_entry> view_list(std::string const & schema) {
    return view_list(schema.c_str());
  }

  //--------------------------------------------------------------------
};

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE

#endif // #ifndef SST_CATALOG_SQLITE_DATABASE_HPP
