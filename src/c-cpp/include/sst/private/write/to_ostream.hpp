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

#ifndef SST_PRIVATE_WRITE_TO_OSTREAM_HPP
#define SST_PRIVATE_WRITE_TO_OSTREAM_HPP

#include <ios>
#include <ostream>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_zero.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/unsigned_min.hpp>

namespace sst {

template<class CharT,
         class Traits,
         class Integer,
         sst::enable_if_t<sst::is_integer_ish<Integer>::value> = 0>
std::basic_ostream<CharT, Traits> &
write(CharT const * src,
      Integer len,
      std::basic_ostream<CharT, Traits> & dst) {
  SST_ASSERT(!sst::is_negative(len));
  SST_ASSERT(src != nullptr || sst::is_zero(len));
  while (!sst::is_zero(len)) {
    std::streamsize const k = static_cast<std::streamsize>(
        sst::unsigned_min(len, sst::type_max<std::streamsize>::value));
    dst.write(src, k);
    src += k;
    len -= k;
  }
  return dst;
}

} // namespace sst

#endif // SST_PRIVATE_WRITE_TO_OSTREAM_HPP
