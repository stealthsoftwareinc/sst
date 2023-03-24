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

#ifndef SST_CATALOG_TO_HEX_OPTIONS_HPP
#define SST_CATALOG_TO_HEX_OPTIONS_HPP

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/is_char.hpp>

namespace sst {

class to_hex_options final {

  int base_ = 16;
  char c62_ = '+';
  char c63_ = '/';
  bool pad_ = false;
  bool prefix_ = false;
  char prefix_char_ = 0;
  unsigned int sep_ = 0;
  bool uppercase_digits_ = true;
  bool uppercase_prefix_ = false;

public:

  //--------------------------------------------------------------------
  // base (whfww66z)
  //--------------------------------------------------------------------

  int base() const noexcept {
    return base_;
  }

  //--------------------------------------------------------------------
  // base (ud5hmxak)
  //--------------------------------------------------------------------

  to_hex_options & base(int const x) noexcept {
    SST_ASSERT((x == 2 || x == 8 || x == 16 || x == 64));
    char const y = prefix_char_;
    if (y != 0) {
      switch (x) {
        case 2: {
          SST_ASSERT((y == 'b' || y == 'B' || y == 'y' || y == 'Y'));
        } break;
        case 8: {
          SST_ASSERT((y == 'o' || y == 'O'));
        } break;
        case 16: {
          SST_ASSERT((y == 'x' || y == 'X'));
        } break;
        case 64: {
          SST_ASSERT((y == 's' || y == 'S' || y == '='));
        } break;
      }
    }
    base_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // c62 (ycmxm784)
  //--------------------------------------------------------------------

  char c62() const noexcept {
    return c62_;
  }

  //--------------------------------------------------------------------
  // c62 (wbz0904h)
  //--------------------------------------------------------------------

  to_hex_options & c62(char const x62) noexcept {
    SST_ASSERT((x62 >= '!' && x62 <= '~'));
    SST_ASSERT((x62 < 'A' || x62 > 'Z'));
    SST_ASSERT((x62 < 'a' || x62 > 'z'));
    SST_ASSERT((x62 < '0' || x62 > '9'));
    SST_ASSERT((x62 != '='));
    SST_ASSERT((x62 != c63_));
    c62_ = x62;
    return *this;
  }

  //--------------------------------------------------------------------
  // c6263 (rvhr4fyy)
  //--------------------------------------------------------------------

  to_hex_options & c6263(char const x62, char const x63) noexcept {
    SST_ASSERT((x62 >= '!' && x62 <= '~'));
    SST_ASSERT((x62 < 'A' || x62 > 'Z'));
    SST_ASSERT((x62 < 'a' || x62 > 'z'));
    SST_ASSERT((x62 < '0' || x62 > '9'));
    SST_ASSERT((x62 != '='));
    SST_ASSERT((x63 >= '!' && x63 <= '~'));
    SST_ASSERT((x63 < 'A' || x63 > 'Z'));
    SST_ASSERT((x63 < 'a' || x63 > 'z'));
    SST_ASSERT((x63 < '0' || x63 > '9'));
    SST_ASSERT((x63 != '='));
    SST_ASSERT((x62 != x63));
    c62_ = x62;
    c63_ = x63;
    return *this;
  }

  //--------------------------------------------------------------------
  // c63 (owt24p6q)
  //--------------------------------------------------------------------

  char c63() const noexcept {
    return c63_;
  }

  //--------------------------------------------------------------------
  // c63 (tf7wry3f)
  //--------------------------------------------------------------------

  to_hex_options & c63(char const x63) noexcept {
    SST_ASSERT((x63 >= '!' && x63 <= '~'));
    SST_ASSERT((x63 < 'A' || x63 > 'Z'));
    SST_ASSERT((x63 < 'a' || x63 > 'z'));
    SST_ASSERT((x63 < '0' || x63 > '9'));
    SST_ASSERT((x63 != '='));
    SST_ASSERT((x63 != c62_));
    c63_ = x63;
    return *this;
  }

  //--------------------------------------------------------------------
  // pad (pv3qy6jj)
  //--------------------------------------------------------------------

  bool pad() const noexcept {
    return pad_;
  }

  //--------------------------------------------------------------------
  // pad (gbgov3f2)
  //--------------------------------------------------------------------

  to_hex_options & pad(bool const x) noexcept {
    pad_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // prefix (qfwnfe0v)
  //--------------------------------------------------------------------

  bool prefix() const noexcept {
    return prefix_;
  }

  //--------------------------------------------------------------------
  // prefix (uth3qqui)
  //--------------------------------------------------------------------

  to_hex_options & prefix(bool const x) noexcept {
    prefix_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // prefix_char (khgh7kcw)
  //--------------------------------------------------------------------

  char prefix_char() const noexcept {
    return prefix_char_;
  }

  //--------------------------------------------------------------------
  // prefix_char (iq3d6mz2)
  //--------------------------------------------------------------------

  to_hex_options & prefix_char(char const x) {
    if (x != 0) {
      switch (base_) {
        case 2: {
          SST_ASSERT((x == 'b' || x == 'B' || x == 'y' || x == 'Y'));
        } break;
        case 8: {
          SST_ASSERT((x == 'o' || x == 'O'));
        } break;
        case 16: {
          SST_ASSERT((x == 'x' || x == 'X'));
        } break;
        case 64: {
          SST_ASSERT((x == 's' || x == 'S' || x == '='));
        } break;
      }
    }
    prefix_char_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // sep (cse58dev)
  //--------------------------------------------------------------------

  unsigned int sep() const noexcept {
    return sep_;
  }

  //--------------------------------------------------------------------
  // sep (v9a0d37k)
  //--------------------------------------------------------------------

  to_hex_options & sep(unsigned int const x) noexcept {
    sep_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // uppercase_digits (meegkv3u)
  //--------------------------------------------------------------------

  bool uppercase_digits() const noexcept {
    return uppercase_digits_;
  }

  //--------------------------------------------------------------------
  // uppercase_digits (s8a6rcns)
  //--------------------------------------------------------------------

  to_hex_options & uppercase_digits(bool const x) noexcept {
    uppercase_digits_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // uppercase_prefix (vs2ynve8)
  //--------------------------------------------------------------------

  bool uppercase_prefix() const noexcept {
    return uppercase_prefix_;
  }

  //--------------------------------------------------------------------
  // uppercase_prefix (h32w2afc)
  //--------------------------------------------------------------------

  to_hex_options & uppercase_prefix(bool const x) noexcept {
    uppercase_prefix_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
  // allow_zero_based_on_type
  //--------------------------------------------------------------------

private:

  bool allow_zero_based_on_type_ = true;

public:

  bool allow_zero_based_on_type() const noexcept {
    return allow_zero_based_on_type_;
  }

  to_hex_options & allow_zero_based_on_type(bool const x) noexcept {
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

  to_hex_options & allow_zero(bool const x) noexcept {
    allow_zero_based_on_type_ = false;
    allow_zero_ = x;
    return *this;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #ifndef SST_CATALOG_TO_HEX_OPTIONS_HPP
