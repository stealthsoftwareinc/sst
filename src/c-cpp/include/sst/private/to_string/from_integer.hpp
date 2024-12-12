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

#ifndef SST_PRIVATE_TO_STRING_FROM_INTEGER_HPP
#define SST_PRIVATE_TO_STRING_FROM_INTEGER_HPP

#include <iterator>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/integer_to_string_options.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/promote_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/guts/to_string/has_member_function.hpp>
#include <sst/private/to_string.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, dst, options
//----------------------------------------------------------------------

template<class X, class Src, class Dst, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<X, Src, Dst, Options>::value
        && sst::is_integer_ish<Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && std::is_convertible<Options,
                               sst::integer_to_string_options>::value>,
    X,
    Src,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using int_t = sst::promote_t<src_t>;

  static void
  add_prefix(dst_t & dst,
             sst::integer_to_string_options const & options) {
    if (options.prefix()) {
      *dst = '0';
      ++dst;
      bool const upper = options.uppercase_prefix();
      switch (options.base()) {
        case 2: {
          *dst = upper ? 'B' : 'b';
        } break;
        case 8: {
          *dst = upper ? 'O' : 'o';
        } break;
        case 10: {
          *dst = upper ? 'D' : 'd';
        } break;
        case 16: {
          *dst = upper ? 'X' : 'x';
        } break;
        default: {
          // clang-format off
          SST_ASSERT("This integer base does not have an associated prefix." && (false));
          // clang-format on
        } break;
      }
      ++dst;
    }
  }

  static char
  digit_char(int_t const & digit,
             sst::integer_to_string_options const & options) {
    SST_ASSERT((!sst::is_negative(digit)));
    SST_ASSERT((digit < static_cast<int_t>(options.base())));
    int const d = static_cast<int>(digit);
    if (d < 10) {
      return static_cast<char>('0' + d);
    }
    if (options.uppercase_digits()) {
      return static_cast<char>('A' + (d - 10));
    }
    return static_cast<char>('a' + (d - 10));
  }

public:

  dst_t operator()(
      src_t const & src,
      dst_t dst,
      sst::integer_to_string_options const & options = {}) const {
    int_t const base = static_cast<int_t>(options.base());
    int_t d = 1;
    if (sst::is_negative(src)) {
      while (d <= src / -base) {
        d *= base;
      }
      *dst = '-';
      ++dst;
      add_prefix(dst, options);
      for (; d != 0; d /= base) {
        *dst = digit_char(-((src / d) % base), options);
        ++dst;
      }
    } else {
      while (d <= src / base) {
        d *= base;
      }
      add_prefix(dst, options);
      for (; d != 0; d /= base) {
        *dst = digit_char((src / d) % base, options);
        ++dst;
      }
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, dst
//----------------------------------------------------------------------

template<class X, class Src, class Dst>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<X, Src, Dst>::value
        && sst::is_integer_ish<Src>::value
        && sst::is_output_iterator<Dst, char>::value>,
    X,
    Src,
    Dst> : public to_string_functor<sst::enable_t,
                                    X,
                                    Src,
                                    Dst,
                                    sst::integer_to_string_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<Dst, Src, Options>::
            value
        && sst::is_integer_ish<Src>::value
        && std::is_convertible<Options,
                               sst::integer_to_string_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;

public:

  sst::remove_cvref_t<Dst> operator()(
      src_t const & src,
      sst::integer_to_string_options const & options = {}) const {
    sst::remove_cvref_t<Dst> dst;
    sst::to_string(src, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class X, class Src>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<X, Src>::value
        && sst::is_integer_ish<Src>::value>,
    X,
    Src> : public to_string_functor<sst::enable_t,
                                    X,
                                    Src,
                                    sst::integer_to_string_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_TO_STRING_FROM_INTEGER_HPP
