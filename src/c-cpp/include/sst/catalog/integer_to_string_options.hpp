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

#ifndef SST_CATALOG_INTEGER_TO_STRING_OPTIONS_HPP
#define SST_CATALOG_INTEGER_TO_STRING_OPTIONS_HPP

#include <sst/catalog/SST_ASSERT.h>

namespace sst {

class integer_to_string_options final {

  int base_ = 10;
  bool prefix_ = false;
  bool uppercase_digits_ = true;
  bool uppercase_prefix_ = false;

public:

  //--------------------------------------------------------------------
  // base
  //--------------------------------------------------------------------

  int base() const {
    return base_;
  }

  integer_to_string_options & base(int const x) {
    SST_ASSERT((x >= 0));
    SST_ASSERT((x <= 36));
    base_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // prefix
  //--------------------------------------------------------------------

  bool prefix() const {
    return prefix_;
  }

  integer_to_string_options & prefix(bool const x) {
    prefix_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // uppercase_digits
  //--------------------------------------------------------------------

  bool uppercase_digits() const {
    return uppercase_digits_;
  }

  integer_to_string_options & uppercase_digits(bool const x) {
    uppercase_digits_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // uppercase_prefix
  //--------------------------------------------------------------------

  bool uppercase_prefix() const {
    return uppercase_prefix_;
  }

  integer_to_string_options & uppercase_prefix(bool const x) {
    uppercase_prefix_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #ifndef SST_CATALOG_INTEGER_TO_STRING_OPTIONS_HPP
