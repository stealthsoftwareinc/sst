/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 */

#ifndef SST_REP_TO_HEX_H
#define SST_REP_TO_HEX_H

#ifdef __cplusplus

#include <iterator>
#include <type_traits>

namespace sst {
namespace rep {

template<
    class Dst,
    class Src,
    typename std::enable_if<
        std::is_same<
            typename std::remove_cv<typename std::remove_reference<
                decltype(*std::declval<Src &>())>::type>::type,
            unsigned char>::value,
        int>::type = 0>
Dst to_hex(Src src, Src const src_end, Dst dst) {
  constexpr char const * const h = "0123456789ABCDEF";
  for (; src != src_end; ++src) {
    unsigned char const x = *src;
    *dst++ = h[(x >> 4) & 0xF];
    *dst++ = h[(x >> 0) & 0xF];
  }
  return dst;
}

template<
    class Dst = std::string,
    class Src,
    decltype(std::back_inserter(std::declval<Dst &>()), int()) = 0>
Dst to_hex(Src src, Src const src_end) {
  Dst dst;
  to_hex(src, src_end, std::back_inserter(dst));
  return dst;
}

template<
    class Dst = std::string,
    class Src,
    decltype(
        std::declval<Src &>().begin(),
        std::declval<Src &>().end(),
        int()) = 0>
Dst to_hex(Src const & src) {
  return to_hex<Dst>(src.begin(), src.end());
}

} // namespace rep
} // namespace sst

#endif // __cplusplus

#endif // SST_REP_TO_HEX_H
