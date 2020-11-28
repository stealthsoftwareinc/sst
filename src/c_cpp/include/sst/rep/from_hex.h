/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 */

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
