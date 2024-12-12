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

#ifndef SST_CATALOG_POSIX_READDIR_HPP
#define SST_CATALOG_POSIX_READDIR_HPP

#include <sst/config.h>

#if SST_WITH_POSIX

namespace sst {

class posix_readdir {

  void * dir_;
  void * ent_ = nullptr;
  bool done_ = false;

  //--------------------------------------------------------------------
  // construct
  //--------------------------------------------------------------------

public:

  explicit posix_readdir(char const * dir);

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  posix_readdir & operator=(posix_readdir const & other) = delete;

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  posix_readdir(posix_readdir const & other) = delete;

  //--------------------------------------------------------------------
  // done
  //--------------------------------------------------------------------

public:

  bool done() const;

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~posix_readdir() noexcept;

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

  posix_readdir & operator=(posix_readdir && other) noexcept;

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

public:

  posix_readdir(posix_readdir && other) noexcept;

  //--------------------------------------------------------------------
  // name
  //--------------------------------------------------------------------

public:

  char const * name() const noexcept;

  //--------------------------------------------------------------------
  // name_is_dot
  //--------------------------------------------------------------------

public:

  bool name_is_dot() const noexcept;

  //--------------------------------------------------------------------
  // name_is_dotdot
  //--------------------------------------------------------------------

public:

  bool name_is_dotdot() const noexcept;

  //--------------------------------------------------------------------
  // name_is_dot_or_dotdot
  //--------------------------------------------------------------------

public:

  bool name_is_dot_or_dotdot() const noexcept;

  //--------------------------------------------------------------------
  // next
  //--------------------------------------------------------------------

public:

  bool next();

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_CATALOG_POSIX_READDIR_HPP
