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

#ifndef SST_CATALOG_SQLITE_STATEMENT_HPP
#define SST_CATALOG_SQLITE_STATEMENT_HPP

#include <sst/catalog/SST_WITH_SQLITE.h>

#if SST_WITH_SQLITE

#include <string>

#include <sst/catalog/SST_NODISCARD.hpp>

#include <sqlite3.h>

namespace sst {
namespace sqlite {

class statement {

  //--------------------------------------------------------------------
  // handle
  //--------------------------------------------------------------------

private:

  sqlite3_stmt * handle_ = nullptr;

public:

  SST_NODISCARD() sqlite3_stmt * handle() const noexcept {
    return handle_;
  }

  SST_NODISCARD() operator sqlite3_stmt *() const noexcept {
    return handle_;
  }

  //--------------------------------------------------------------------
  // Constructors
  //--------------------------------------------------------------------

public:

  explicit statement(sqlite3 * db, char const * sql);

  explicit statement(sqlite3 * const db, std::string const & sql)
      : statement(db, sql.c_str()) {
  }

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------

public:

  statement(statement const &) = delete;

  statement & operator=(statement const &) = delete;

  statement(statement &&) = delete;

  statement & operator=(statement &&) = delete;

  ~statement() noexcept;

  //--------------------------------------------------------------------
  // bind_text
  //--------------------------------------------------------------------

public:

  // ID: btyuewha
  statement & bind_text(int index, char const * text);

  // ID: pavnthpc
  statement & bind_text(int index, std::string const & text);

  //--------------------------------------------------------------------
  // step
  //--------------------------------------------------------------------

public:

  statement & step();

  //--------------------------------------------------------------------
};

} // namespace sqlite
} // namespace sst

#endif // #if SST_WITH_SQLITE

#endif // SST_CATALOG_SQLITE_STATEMENT_HPP
