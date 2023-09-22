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

#ifndef SST_REP_FROM_HEX_H
#define SST_REP_FROM_HEX_H

#ifdef __cplusplus

#include <iterator>
#include <sst/rep/error.h>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace sst {
namespace rep {

template<
    class Src,
    typename std::enable_if<std::is_integral<Src>::value, int>::type =
        0>
unsigned char from_hex(Src const src) {
  if (src >= '0' && src <= '9') {
    return static_cast<unsigned char>(src - '0');
  }
  if (src >= 'A' && src <= 'F') {
    return static_cast<unsigned char>(src - 'A' + 10);
  }
  if (src >= 'a' && src <= 'f') {
    return static_cast<unsigned char>(src - 'a' + 10);
  }
  throw error("invalid hex digit");
}

template<class Dst, class Src>
Dst from_hex(Src src, Src const src_end, Dst dst) {
  while (src != src_end) {
    unsigned char const x = from_hex(*src++);
    if (src == src_end) {
      throw error("odd hex length");
    }
    unsigned char const y = from_hex(*src++);
    *dst++ = static_cast<unsigned char>((x << 4) | y);
  }
  return dst;
}

template<class Dst = std::vector<unsigned char>, class Src>
Dst from_hex(Src src, Src const src_end) {
  Dst dst;
  from_hex(src, src_end, std::back_inserter(dst));
  return dst;
}

template<
    class Dst = std::vector<unsigned char>,
    class Src,
    typename std::enable_if<!std::is_integral<Src>::value, int>::type =
        0>
Dst from_hex(Src const & src) {
  return from_hex<Dst>(src.begin(), src.end());
}

template<class Dst, class Src>
Dst from_hex_exact(
    Src src, Src const src_end, Dst dst, Dst const dst_end) {
  while (src != src_end) {
    if (dst == dst_end) {
      throw error("inexact length");
    }
    unsigned char const x = from_hex(*src++);
    if (src == src_end) {
      throw error("odd hex length");
    }
    unsigned char const y = from_hex(*src++);
    *dst++ = static_cast<unsigned char>((x << 4) | y);
  }
  if (dst != dst_end) {
    throw error("inexact length");
  }
  return dst;
}

} // namespace rep
} // namespace sst

#endif // __cplusplus

#endif // SST_REP_FROM_HEX_H
