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

#ifndef SST_CATALOG_WRITE_WHOLE_FILE_OPTIONS_HPP
#define SST_CATALOG_WRITE_WHOLE_FILE_OPTIONS_HPP

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/is_char.hpp>

namespace sst {

class write_whole_file_options {

  //--------------------------------------------------------------------
  // allow_zero_based_on_type
  //--------------------------------------------------------------------

private:

  bool allow_zero_based_on_type_ = true;

public:

  bool allow_zero_based_on_type() const noexcept {
    return allow_zero_based_on_type_;
  }

  write_whole_file_options &
  allow_zero_based_on_type(bool const x) noexcept {
    allow_zero_based_on_type_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // allow_zero
  //--------------------------------------------------------------------

private:

  bool allow_zero_ = true;

public:

  bool allow_zero() const noexcept {
    SST_ASSERT((!allow_zero_based_on_type_));
    return allow_zero_;
  }

  template<class T>
  bool allow_zero(T &&) const noexcept {
    if (allow_zero_based_on_type_) {
      return !sst::is_char<T>::value;
    }
    return allow_zero_;
  }

  write_whole_file_options & allow_zero(bool const x) noexcept {
    allow_zero_based_on_type_ = false;
    allow_zero_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // quote
  //--------------------------------------------------------------------

private:

  bool quote_ = true;

public:

  bool quote() const noexcept {
    return quote_;
  }

  write_whole_file_options & quote(bool const x) noexcept {
    quote_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #ifndef SST_CATALOG_WRITE_WHOLE_FILE_OPTIONS_HPP
