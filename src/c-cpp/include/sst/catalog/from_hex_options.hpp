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

#ifndef SST_CATALOG_FROM_HEX_OPTIONS_HPP
#define SST_CATALOG_FROM_HEX_OPTIONS_HPP

#include <sst/catalog/SST_ASSERT.hpp>

namespace sst {

class from_hex_options {

  int base_ = 0;
  char c62_ = '+';
  char c63_ = '/';

public:

  //--------------------------------------------------------------------
  // base (bijc6wca)
  //--------------------------------------------------------------------

  int base() const noexcept {
    return base_;
  }

  //--------------------------------------------------------------------
  // base (u5s7nxg3)
  //--------------------------------------------------------------------

  from_hex_options & base(int const b) noexcept {
    SST_ASSERT((b == 0 || b == 2 || b == 8 || b == 16 || b == 64));
    base_ = b;
    return *this;
  }

  //--------------------------------------------------------------------
  // c62 (cxn0jpnb)
  //--------------------------------------------------------------------

  char c62() const noexcept {
    return c62_;
  }

  //--------------------------------------------------------------------
  // c62 (zb3azdgc)
  //--------------------------------------------------------------------

  from_hex_options & c62(char const x62) noexcept {
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
  // c6263 (wznxyxbn)
  //--------------------------------------------------------------------

  from_hex_options & c6263(char const x62, char const x63) noexcept {
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
  // c63 (ta6dhf70)
  //--------------------------------------------------------------------

  char c63() const noexcept {
    return c63_;
  }

  //--------------------------------------------------------------------
  // c63 (jyaxaaha)
  //--------------------------------------------------------------------

  from_hex_options & c63(char const x63) noexcept {
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
};

} // namespace sst

#endif // SST_CATALOG_FROM_HEX_OPTIONS_HPP
