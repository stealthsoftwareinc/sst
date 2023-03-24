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

#ifndef SST_PRIVATE_TO_HEX_FROM_BYTE_INPUT_ITERATOR_HPP
#define SST_PRIVATE_TO_HEX_FROM_BYTE_INPUT_ITERATOR_HPP

#include <cstdlib>
#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_byte_input_iterator.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_hex.hpp>
#include <sst/catalog/to_hex_functor.hpp>
#include <sst/catalog/to_hex_options.hpp>
#include <sst/catalog/unsigned_min.hpp>

namespace sst {

namespace guts {
namespace to_hex {
namespace from_byte_input_iterator {

template<int BitsPerChar, class Dst>
void write_prefix(Dst & dst, sst::to_hex_options const & options) {
  if (options.prefix()) {
    *dst = '0';
    ++dst;
    if (options.prefix_char() != 0) {
      *dst = options.prefix_char();
    } else {
      switch (BitsPerChar) {
        case 1: {
          *dst = options.uppercase_prefix() ? 'Y' : 'y';
        } break;
        case 3: {
          *dst = options.uppercase_prefix() ? 'O' : 'o';
        } break;
        case 4: {
          *dst = options.uppercase_prefix() ? 'X' : 'x';
        } break;
        case 6: {
          *dst = '=';
        } break;
        default: {
          SST_ASSERT("Missing case." && (false));
          std::abort();
        } break;
      }
    }
    ++dst;
  }
}

template<int BitsPerChar, class Dst>
void write_sep(unsigned int & sep,
               Dst & dst,
               sst::to_hex_options const & options) {
  if (options.sep() > 0) {
    if (sep == options.sep()) {
      *dst = '\'';
      ++dst;
      sep = 1;
    } else {
      ++sep;
    }
  }
}

template<int BitsPerChar, sst::enable_if_t<BitsPerChar == 1> = 0>
char digit_to_char(unsigned char const x,
                   sst::to_hex_options const &) noexcept {
  SST_ASSERT((x < 2));
  return "01"[x];
}

template<int BitsPerChar, sst::enable_if_t<BitsPerChar == 3> = 0>
char digit_to_char(unsigned char const x,
                   sst::to_hex_options const &) noexcept {
  SST_ASSERT((x < 8));
  return "01234567"[x];
}

template<int BitsPerChar, sst::enable_if_t<BitsPerChar == 4> = 0>
char digit_to_char(unsigned char const x,
                   sst::to_hex_options const & options) noexcept {
  SST_ASSERT((x < 16));
  return (options.uppercase_digits() ? "0123456789ABCDEF" :
                                       "0123456789abcdef")[x];
}

template<int BitsPerChar, sst::enable_if_t<BitsPerChar == 6> = 0>
char digit_to_char(unsigned char const x,
                   sst::to_hex_options const & options) noexcept {
  SST_ASSERT((x < 64));
  return x < 62  ? "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "abcdefghijklmnopqrstuvwxyz"
                   "0123456789"[x] :
         x == 62 ? options.c62() :
                   options.c63();
}

template<int BitsPerChar, class Dst>
void process_byte(unsigned int & buf,
                  int & len,
                  unsigned int & sep,
                  Dst & dst,
                  unsigned int x,
                  sst::to_hex_options const & options) {
  int n = sst::char_bit_v;
  while (n > 0) {
    int const k = sst::unsigned_min(n, BitsPerChar);
    buf <<= k;
    buf |= (x >> (n - k)) & sst::ones_mask<unsigned int>(k);
    len += k;
    if (len == BitsPerChar) {
      write_sep<BitsPerChar>(sep, dst, options);
      *dst = digit_to_char<BitsPerChar>(buf, options);
      ++dst;
      buf = 0;
      len = 0;
    }
    n -= k;
  }
}

template<int BitsPerChar, class Dst>
void write_padding(unsigned int & buf,
                   int & len,
                   unsigned int & sep,
                   Dst & dst,
                   sst::to_hex_options const & options) {
  if (len > 0) {
    buf <<= BitsPerChar - len;
    write_sep<BitsPerChar>(sep, dst, options);
    *dst = digit_to_char<BitsPerChar>(buf, options);
    ++dst;
    if (options.pad()) {
      len = sst::char_bit_v - len;
      while (true) {
        len += BitsPerChar;
        len %= sst::char_bit_v;
        if (len == 0) {
          break;
        }
        write_sep<BitsPerChar>(sep, dst, options);
        *dst = '=';
        ++dst;
      }
    }
  }
}

} // namespace from_byte_input_iterator
} // namespace to_hex
} // namespace guts

//----------------------------------------------------------------------
// src, end, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class End, class Dst, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
    X,
    Src,
    End,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<Src>;

  template<int BitsPerChar>
  static void process_bytes(src_t & src,
                            end_t const & end,
                            dst_t & dst,
                            sst::to_hex_options const & options) {
    using namespace guts::to_hex::from_byte_input_iterator;
    write_prefix<BitsPerChar>(dst, options);
    unsigned int buf = 0;
    int len = 0;
    unsigned int sep = 0;
    while (true) {
      auto const pc = sst::peek(src, end);
      if (pc == nullptr) {
        break;
      }
      src_value_t const & c = *pc;
      if (!options.allow_zero(c) && c == 0) {
        break;
      }
      ++src;
      unsigned int const x = static_cast<unsigned char>(c);
      process_byte<BitsPerChar>(buf, len, sep, dst, x, options);
    }
    write_padding<BitsPerChar>(buf, len, sep, dst, options);
  }

public:

  dst_t operator()(src_t src,
                   end_t const & end,
                   dst_t dst,
                   sst::to_hex_options const & options = {}) const {
    switch (options.base()) {
      case 2: {
        process_bytes<1>(src, end, dst, options);
      } break;
      case 8: {
        process_bytes<3>(src, end, dst, options);
      } break;
      case 16: {
        process_bytes<4>(src, end, dst, options);
      } break;
      case 64: {
        process_bytes<6>(src, end, dst, options);
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
class to_hex_functor<
    sst::enable_if_t<sst::is_byte_input_iterator<Src>::value
                     && sst::is_sentinel<End, Src>::value
                     && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    End,
    Dst> : public to_hex_functor<sst::enable_t,
                                 X,
                                 Src,
                                 End,
                                 Dst,
                                 sst::to_hex_options> {};

//----------------------------------------------------------------------
// src, end, options
//----------------------------------------------------------------------

template<class Dst, class Src, class End, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
    Dst,
    Src,
    End,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t src,
             end_t const & end,
             sst::to_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_hex(std::move(src),
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
class to_hex_functor<
    sst::enable_if_t<sst::is_byte_input_iterator<Src>::value
                     && sst::is_sentinel<End, Src>::value>,
    X,
    Src,
    End> : public to_hex_functor<sst::enable_t,
                                 X,
                                 Src,
                                 End,
                                 sst::to_hex_options> {};

//----------------------------------------------------------------------
// src, sen, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class Sen, class Dst, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
    X,
    Src,
    Sen,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<Src>;

  template<int BitsPerChar>
  static void process_bytes(src_t & src,
                            sen_t const & sen,
                            dst_t & dst,
                            sst::to_hex_options const & options) {
    using namespace guts::to_hex::from_byte_input_iterator;
    write_prefix<BitsPerChar>(dst, options);
    unsigned int buf = 0;
    int len = 0;
    unsigned int sep = 0;
    while (true) {
      auto const pc = sst::peek(src, sen);
      if (pc == nullptr) {
        break;
      }
      src_value_t const & c = *pc;
      if (!options.allow_zero(c) && c == 0) {
        break;
      }
      ++src;
      unsigned int const x = static_cast<unsigned char>(c);
      process_byte<BitsPerChar>(buf, len, sep, dst, x, options);
    }
    write_padding<BitsPerChar>(buf, len, sep, dst, options);
  }

public:

  dst_t operator()(src_t src,
                   sen_t const & sen,
                   dst_t dst,
                   sst::to_hex_options const & options = {}) const {
    switch (options.base()) {
      case 2: {
        process_bytes<1>(src, sen, dst, options);
      } break;
      case 8: {
        process_bytes<3>(src, sen, dst, options);
      } break;
      case 16: {
        process_bytes<4>(src, sen, dst, options);
      } break;
      case 64: {
        process_bytes<6>(src, sen, dst, options);
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
class to_hex_functor<
    sst::enable_if_t<sst::is_byte_input_iterator<Src>::value
                     && sst::is_value_sentinel<Sen, Src>::value
                     && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    Sen,
    Dst> : public to_hex_functor<sst::enable_t,
                                 X,
                                 Src,
                                 Sen,
                                 Dst,
                                 sst::to_hex_options> {};

//----------------------------------------------------------------------
// src, sen, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
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
             sst::to_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_hex(std::move(src), sen, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen
//----------------------------------------------------------------------

template<class X, class Src, class Sen>
class to_hex_functor<
    sst::enable_if_t<sst::is_byte_input_iterator<Src>::value
                     && sst::is_value_sentinel<Sen, Src>::value>,
    X,
    Src,
    Sen> : public to_hex_functor<sst::enable_t,
                                 X,
                                 Src,
                                 Sen,
                                 sst::to_hex_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class to_hex_functor<
    sst::enable_if_t<
        sst::is_byte_input_iterator<Src>::value
        && std::is_convertible<Options, sst::to_hex_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using src_value_t = sst::value_type_t<Src>;

public:

  sst::remove_cvref_t<Dst>
  operator()(src_t src,
             sst::to_hex_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_hex(std::move(src),
                src_value_t{},
                std::back_inserter(dst),
                options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class to_hex_functor<
    sst::enable_if_t<sst::is_byte_input_iterator<Src>::value>,
    Dst,
    Src> : public to_hex_functor<sst::enable_t,
                                 Dst,
                                 Src,
                                 sst::to_hex_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_PRIVATE_TO_HEX_FROM_BYTE_INPUT_ITERATOR_HPP
