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

#ifndef SST_PRIVATE_FROM_HEX_FROM_CHAR_INPUT_ITERATOR_HPP
#define SST_PRIVATE_FROM_HEX_FROM_CHAR_INPUT_ITERATOR_HPP

#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/from_hex.hpp>
#include <sst/catalog/from_hex_exception.hpp>
#include <sst/catalog/from_hex_functor.hpp>
#include <sst/catalog/from_hex_options.hpp>
#include <sst/catalog/is_char_input_iterator.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_sentinel.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

namespace guts {
namespace from_hex {
namespace from_char_input_iterator {

template<int BitsPerChar, class SrcValue>
static int parse_prefix(SrcValue const c1, SrcValue const c2) noexcept {
  if (c1 == SrcValue('0')) {
    switch (BitsPerChar) {
      case 0: {
        switch (c2) {
          case SrcValue('y'):
          case SrcValue('Y'):
            return 1;
          case SrcValue('o'):
          case SrcValue('O'):
            return 3;
          case SrcValue('x'):
          case SrcValue('X'):
            return 4;
          case SrcValue('s'):
          case SrcValue('S'):
          case SrcValue('='):
            return 6;
        }
      } break;
      case 1: {
        switch (c2) {
          case SrcValue('b'):
          case SrcValue('B'):
          case SrcValue('y'):
          case SrcValue('Y'):
            return 1;
        }
      } break;
      case 3: {
        switch (c2) {
          case SrcValue('o'):
          case SrcValue('O'):
            return 3;
        }
      } break;
      case 4: {
        switch (c2) {
          case SrcValue('x'):
          case SrcValue('X'):
            return 4;
        }
      } break;
      case 6: {
        switch (c2) {
          case SrcValue('='):
            return 6;
        }
      } break;
      default: {
        SST_ASSERT("Missing case." && (false));
        std::abort();
      } break;
    }
  }
  return 0;
}

template<int BitsPerChar,
         class SrcValue,
         sst::enable_if_t<BitsPerChar == 1> = 0>
static unsigned int char_to_digit(SrcValue const c,
                                  sst::from_hex_options const &) {
  if (c == SrcValue('0')) {
    return 0U;
  }
  if (c == SrcValue('1')) {
    return 1U;
  }
  if (c == SrcValue('=')) {
    throw sst::from_hex_exception("sst::from_hex: Invalid padding.");
  }
  throw sst::from_hex_exception(
      "sst::from_hex: Invalid binary digit character.");
}

template<int BitsPerChar,
         class SrcValue,
         sst::enable_if_t<BitsPerChar == 3> = 0>
static unsigned int char_to_digit(SrcValue const c,
                                  sst::from_hex_options const &) {
  if (c >= SrcValue('0') && c <= SrcValue('7')) {
    return static_cast<unsigned int>(c - SrcValue('0'));
  }
  if (c == SrcValue('=')) {
    throw sst::from_hex_exception("sst::from_hex: Invalid padding.");
  }
  throw sst::from_hex_exception(
      "sst::from_hex: Invalid octal digit character.");
}

template<int BitsPerChar,
         class SrcValue,
         sst::enable_if_t<BitsPerChar == 4> = 0>
static unsigned int char_to_digit(SrcValue const c,
                                  sst::from_hex_options const &) {
  if (c >= SrcValue('0') && c <= SrcValue('9')) {
    return static_cast<unsigned int>(c - SrcValue('0'));
  }
  if (c >= SrcValue('A') && c <= SrcValue('F')) {
    return 10U + static_cast<unsigned int>(c - SrcValue('A'));
  }
  if (c >= SrcValue('a') && c <= SrcValue('f')) {
    return 10U + static_cast<unsigned int>(c - SrcValue('a'));
  }
  if (c == SrcValue('=')) {
    throw sst::from_hex_exception("sst::from_hex: Invalid padding.");
  }
  throw sst::from_hex_exception(
      "sst::from_hex: Invalid hexadecimal digit character.");
}

template<int BitsPerChar,
         class SrcValue,
         sst::enable_if_t<BitsPerChar == 6> = 0>
static unsigned int
char_to_digit(SrcValue const c, sst::from_hex_options const & options) {
  if (c >= SrcValue('A') && c <= SrcValue('Z')) {
    return static_cast<unsigned int>(c - SrcValue('A'));
  }
  if (c >= SrcValue('a') && c <= SrcValue('z')) {
    return 26U + static_cast<unsigned int>(c - SrcValue('a'));
  }
  if (c >= SrcValue('0') && c <= SrcValue('9')) {
    return 52U + static_cast<unsigned int>(c - SrcValue('0'));
  }
  if (c == options.c62()) {
    return 62U;
  }
  if (c == options.c63()) {
    return 63U;
  }
  if (c == SrcValue('=')) {
    throw sst::from_hex_exception("sst::from_hex: Invalid padding.");
  }
  throw sst::from_hex_exception(
      "sst::from_hex: Invalid Base64 digit character.");
}

template<int BitsPerChar, class Dst, class SrcValue>
static void process_char(unsigned int & buf,
                         int & len,
                         Dst & dst,
                         SrcValue c,
                         sst::from_hex_options const & options) {
  unsigned int const digit = char_to_digit<BitsPerChar>(c, options);
  int const r = sst::char_bit_v - len;
  if (r > BitsPerChar) {
    buf <<= BitsPerChar;
    buf |= digit;
    len += BitsPerChar;
  } else {
    len = BitsPerChar - r;
    buf <<= r;
    buf |= digit >> len;
    *dst = static_cast<unsigned char>(buf);
    ++dst;
    buf <<= len;
    buf |= digit & ((1U << len) - 1U);
  }
}

} // namespace from_char_input_iterator
} // namespace from_hex
} // namespace guts

//----------------------------------------------------------------------
// src, end, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class End, class Dst, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<Dst, unsigned char>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    X,
    Src,
    End,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;

  template<int BitsPerChar>
  static void process_chars(src_t & src,
                            end_t const & end,
                            bool & allow_sep,
                            unsigned int & buf,
                            int & len,
                            dst_t & dst,
                            sst::from_hex_options const & options) {
    using namespace guts::from_hex::from_char_input_iterator;
    for (; !(src == end); ++src) {
      src_value_t const c = *src;
      if (c == 0) {
        break;
      }
      if (allow_sep && c == src_value_t('\'')) {
        allow_sep = false;
      } else if (c == src_value_t('=')) {
        if (len % BitsPerChar == 0) {
          throw sst::from_hex_exception(
              "sst::from_hex: Invalid padding.");
        }
        while (true) {
          len += BitsPerChar;
          len %= sst::char_bit_v;
          if (len == 0) {
            break;
          }
          ++src;
          if (src == end) {
            throw sst::from_hex_exception(
                "sst::from_hex: Invalid padding.");
          }
          src_value_t c2 = *src;
          if (c2 == 0) {
            throw sst::from_hex_exception(
                "sst::from_hex: Invalid padding.");
          }
          if (c2 == src_value_t('\'')) {
            ++src;
            if (src == end) {
              throw sst::from_hex_exception(
                  "sst::from_hex: Invalid padding.");
            }
            c2 = *src;
            if (c2 == 0) {
              throw sst::from_hex_exception(
                  "sst::from_hex: Invalid padding.");
            }
          }
          if (c2 != src_value_t('=')) {
            throw sst::from_hex_exception(
                "sst::from_hex: Invalid padding.");
          }
        }
        allow_sep = true;
      } else {
        process_char<BitsPerChar>(buf, len, dst, c, options);
        allow_sep = true;
      }
    }
  }

  template<int BitsPerChar>
  static void parse(src_t & src,
                    end_t const & end,
                    dst_t & dst,
                    sst::from_hex_options const & options) {
    using namespace guts::from_hex::from_char_input_iterator;
    constexpr int default_bits_per_char =
        BitsPerChar > 0 ? BitsPerChar : 4;
    if (src == end) {
      return;
    }
    src_value_t const c1 = *src;
    if (c1 == 0) {
      return;
    }
    ++src;
    if (src == end) {
      static_cast<void>(
          char_to_digit<default_bits_per_char>(c1, options));
      return;
    }
    src_value_t const c2 = *src;
    if (c2 == 0) {
      static_cast<void>(
          char_to_digit<default_bits_per_char>(c1, options));
      return;
    }
    ++src;
    int const prefix_bits_per_char = parse_prefix<BitsPerChar>(c1, c2);
    int const bits_per_char = BitsPerChar > 0 ? BitsPerChar :
                              prefix_bits_per_char > 0 ?
                                                prefix_bits_per_char :
                                                default_bits_per_char;
    unsigned int buf = 0;
    int len = 0;
    bool allow_sep = true;
    if (prefix_bits_per_char == 0) {
      process_char<default_bits_per_char>(buf, len, dst, c1, options);
      if (c2 == src_value_t('\'')) {
        allow_sep = false;
      } else {
        process_char<default_bits_per_char>(buf, len, dst, c2, options);
      }
    }
    switch (bits_per_char) {
      case 1: {
        process_chars<1>(src, end, allow_sep, buf, len, dst, options);
      } break;
      case 3: {
        process_chars<3>(src, end, allow_sep, buf, len, dst, options);
      } break;
      case 4: {
        process_chars<4>(src, end, allow_sep, buf, len, dst, options);
      } break;
      case 6: {
        process_chars<6>(src, end, allow_sep, buf, len, dst, options);
      } break;
      default: {
        SST_ASSERT("Missing case." && (false));
        std::abort();
      } break;
    }
    if (!allow_sep) {
      throw sst::from_hex_exception(
          "A text representation of a binary blob must not end with "
          "the digit separator character.");
    }
  }

public:

  dst_t operator()(src_t src,
                   end_t const end,
                   dst_t dst,
                   sst::from_hex_options const & options = {}) const {
    switch (options.base()) {
      case 0: {
        parse<0>(src, end, dst, options);
      } break;
      case 2: {
        parse<1>(src, end, dst, options);
      } break;
      case 8: {
        parse<3>(src, end, dst, options);
      } break;
      case 16: {
        parse<4>(src, end, dst, options);
      } break;
      case 64: {
        parse<6>(src, end, dst, options);
      } break;
      default: {
        SST_ASSERT("Missing case." && (false));
        std::abort();
      } break;
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end, dst
//----------------------------------------------------------------------

template<class X, class Src, class End, class Dst>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<Dst, unsigned char>::value>,
    X,
    Src,
    End,
    Dst> : public from_hex_functor<sst::enable_t,
                                   X,
                                   Src,
                                   End,
                                   Dst,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------
// src, end, options
//----------------------------------------------------------------------

template<class Dst, class Src, class End, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    Dst,
    Src,
    End,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t src,
             end_t end,
             sst::from_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::from_hex(std::move(src),
                  std::move(end),
                  std::back_inserter(dst),
                  options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end
//----------------------------------------------------------------------

template<class X, class Src, class End>
class from_hex_functor<
    sst::enable_if_t<sst::is_char_input_iterator<Src>::value
                     && sst::is_sentinel<End, Src>::value>,
    X,
    Src,
    End> : public from_hex_functor<sst::enable_t,
                                   X,
                                   Src,
                                   End,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------
// src, sen, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class Sen, class Dst, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst, unsigned char>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    X,
    Src,
    Sen,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;

  template<int BitsPerChar>
  static void process_chars(src_t & src,
                            sen_t const & sen,
                            bool & allow_sep,
                            unsigned int & buf,
                            int & len,
                            dst_t & dst,
                            sst::from_hex_options const & options) {
    using namespace guts::from_hex::from_char_input_iterator;
    for (;; ++src) {
      src_value_t const c = *src;
      if (c == sen) {
        break;
      }
      if (allow_sep && c == src_value_t('\'')) {
        allow_sep = false;
      } else if (c == src_value_t('=')) {
        if (len % BitsPerChar == 0) {
          throw sst::from_hex_exception(
              "sst::from_hex: Invalid padding.");
        }
        while (true) {
          len += BitsPerChar;
          len %= sst::char_bit_v;
          if (len == 0) {
            break;
          }
          ++src;
          src_value_t c2 = *src;
          if (c2 == sen) {
            throw sst::from_hex_exception(
                "sst::from_hex: Invalid padding.");
          }
          if (c2 == src_value_t('\'')) {
            ++src;
            c2 = *src;
            if (c2 == sen) {
              throw sst::from_hex_exception(
                  "sst::from_hex: Invalid padding.");
            }
          }
          if (c2 != src_value_t('=')) {
            throw sst::from_hex_exception(
                "sst::from_hex: Invalid padding.");
          }
        }
        allow_sep = true;
      } else {
        process_char<BitsPerChar>(buf, len, dst, c, options);
        allow_sep = true;
      }
    }
  }

  template<int BitsPerChar>
  static void parse(src_t & src,
                    sen_t const & sen,
                    dst_t & dst,
                    sst::from_hex_options const & options) {
    using namespace guts::from_hex::from_char_input_iterator;
    constexpr int default_bits_per_char =
        BitsPerChar > 0 ? BitsPerChar : 4;
    src_value_t const c1 = *src;
    if (c1 == sen) {
      return;
    }
    ++src;
    src_value_t const c2 = *src;
    if (c2 == sen) {
      static_cast<void>(
          char_to_digit<default_bits_per_char>(c1, options));
      return;
    }
    ++src;
    int const prefix_bits_per_char = parse_prefix<BitsPerChar>(c1, c2);
    int const bits_per_char = BitsPerChar > 0 ? BitsPerChar :
                              prefix_bits_per_char > 0 ?
                                                prefix_bits_per_char :
                                                default_bits_per_char;
    unsigned int buf = 0;
    int len = 0;
    bool allow_sep = true;
    if (prefix_bits_per_char == 0) {
      process_char<default_bits_per_char>(buf, len, dst, c1, options);
      if (c2 == src_value_t('\'')) {
        allow_sep = false;
      } else {
        process_char<default_bits_per_char>(buf, len, dst, c2, options);
      }
    }
    switch (bits_per_char) {
      case 1: {
        process_chars<1>(src, sen, allow_sep, buf, len, dst, options);
      } break;
      case 3: {
        process_chars<3>(src, sen, allow_sep, buf, len, dst, options);
      } break;
      case 4: {
        process_chars<4>(src, sen, allow_sep, buf, len, dst, options);
      } break;
      case 6: {
        process_chars<6>(src, sen, allow_sep, buf, len, dst, options);
      } break;
      default: {
        SST_ASSERT("Missing case." && (false));
        std::abort();
      } break;
    }
    if (!allow_sep) {
      throw sst::from_hex_exception(
          "A text representation of a binary blob must not end with "
          "the digit separator character.");
    }
  }

public:

  dst_t operator()(src_t src,
                   sen_t const & sen,
                   dst_t dst,
                   sst::from_hex_options const & options = {}) const {
    switch (options.base()) {
      case 0: {
        parse<0>(src, sen, dst, options);
      } break;
      case 2: {
        parse<1>(src, sen, dst, options);
      } break;
      case 8: {
        parse<3>(src, sen, dst, options);
      } break;
      case 16: {
        parse<4>(src, sen, dst, options);
      } break;
      case 64: {
        parse<6>(src, sen, dst, options);
      } break;
      default: {
        SST_ASSERT("Missing case." && (false));
        std::abort();
      } break;
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen, dst
//----------------------------------------------------------------------

template<class X, class Src, class Sen, class Dst>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst, unsigned char>::value>,
    X,
    Src,
    Sen,
    Dst> : public from_hex_functor<sst::enable_t,
                                   X,
                                   Src,
                                   Sen,
                                   Dst,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------
// src, sen, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    Dst,
    Src,
    Sen,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t src,
             sen_t const & sen,
             sst::from_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::from_hex(std::move(src),
                  sen,
                  std::back_inserter(dst),
                  options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen
//----------------------------------------------------------------------

template<class X, class Src, class Sen>
class from_hex_functor<
    sst::enable_if_t<sst::is_char_input_iterator<Src>::value
                     && sst::is_value_sentinel<Sen, Src>::value>,
    X,
    Src,
    Sen> : public from_hex_functor<sst::enable_t,
                                   X,
                                   Src,
                                   Sen,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class from_hex_functor<
    sst::enable_if_t<
        sst::is_char_input_iterator<Src>::value
        && std::is_convertible<Options, sst::from_hex_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using src_value_t = sst::value_type_t<Src>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t src,
             sst::from_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::from_hex(std::move(src),
                  sst::value_sentinel(src_value_t()),
                  std::back_inserter(dst),
                  options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class from_hex_functor<
    sst::enable_if_t<sst::is_char_input_iterator<Src>::value>,
    Dst,
    Src> : public from_hex_functor<sst::enable_t,
                                   Dst,
                                   Src,
                                   sst::from_hex_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_FROM_HEX_FROM_CHAR_INPUT_ITERATOR_HPP
