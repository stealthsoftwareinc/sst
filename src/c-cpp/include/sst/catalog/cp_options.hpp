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

#ifndef SST_CATALOG_CP_OPTIONS_HPP
#define SST_CATALOG_CP_OPTIONS_HPP

namespace sst {

class cp_options {

  //--------------------------------------------------------------------
  // contents
  //--------------------------------------------------------------------

private:

  bool contents_ = false;

public:

  bool contents() const noexcept {
    return contents_;
  }

  cp_options & contents(bool const x) noexcept {
    contents_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // follow_links
  //--------------------------------------------------------------------

private:

  bool follow_links_ = true;

public:

  bool follow_links() const noexcept {
    return follow_links_;
  }

  cp_options & follow_links(bool const x) noexcept {
    follow_links_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // recursive
  //--------------------------------------------------------------------

private:

  bool recursive_ = false;

public:

  bool recursive() const noexcept {
    return recursive_;
  }

  cp_options & recursive(bool const x) noexcept {
    recursive_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_CATALOG_CP_OPTIONS_HPP
