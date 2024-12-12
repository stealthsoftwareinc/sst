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

#ifndef SST_PRIVATE_TO_INTEGER_FROM_CHAR_INPUT_ITERATOR_HPP
#define SST_PRIVATE_TO_INTEGER_FROM_CHAR_INPUT_ITERATOR_HPP

#include <exception>

#include <sst/catalog/checked_overflow.hpp>
#include <sst/catalog/checked_t.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/min.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/string_to_integer_options.hpp>
#include <sst/catalog/to_integer_exception.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/to_integer.hpp>

namespace sst {

//----------------------------------------------------------------------
// Core algorithm
//----------------------------------------------------------------------

namespace guts {
namespace to_integer {
namespace from_char_input_iterator {

template<class Src, class EndOrSen>
int read_sign(Src & src, EndOrSen const & end_or_sen) {
  using char_t = sst::value_type_t<Src>;
  auto const pc = sst::peek(src, end_or_sen);
  if (pc == nullptr) {
    throw sst::to_integer_exception("Unexpected end of string.");
  }
  char_t const & c = *pc;
  if (c == char_t('-')) {
    ++src;
    return -1;
  }
  if (c == char_t('+')) {
    ++src;
    return 1;
  }
  return 0;
}

template<class Src, class EndOrSen>
int read_base(Src & src, EndOrSen const & end_or_sen) {
  using char_t = sst::value_type_t<Src>;
  {
    auto const pc = sst::peek(src, end_or_sen);
    if (pc == nullptr) {
      throw sst::to_integer_exception("Unexpected end of string.");
    }
    char_t const & c = *pc;
    if (c >= char_t('1') && c <= char_t('9')) {
      return 10;
    }
    if (c != char_t('0')) {
      throw sst::to_integer_exception();
    }
    ++src;
  }
  {
    auto const pc = sst::peek(src, end_or_sen);
    if (pc == nullptr) {
      return 0;
    }
    char_t const & c = *pc;
    if (c == char_t('0')) {
      throw sst::to_integer_exception();
    }
    if (c == char_t('b') || c == char_t('B')) {
      ++src;
      return 2;
    }
    if (c == char_t('o') || c == char_t('O')) {
      ++src;
      return 8;
    }
    if (c == char_t('d') || c == char_t('D')) {
      ++src;
      return 10;
    }
    if (c == char_t('x') || c == char_t('X')) {
      ++src;
      return 16;
    }
    return 0;
  }
}

template<class Dst, class Src, class EndOrSen, class Options>
Dst core(Src & src, EndOrSen const & end_or_sen, Options const &) {
  try {
    using char_t = sst::value_type_t<Src>;
    int const sign = read_sign(src, end_or_sen);
    int const base = read_base(src, end_or_sen);
    sst::checked_t<Dst> value = 0;
    auto c = sst::peek(src, end_or_sen);
    if (base != 0) {
      bool first_digit = true;
      while (true) {
        if (c == nullptr) {
          break;
        }
        if (!first_digit && *c == char_t('\'')) {
          ++src;
          c = sst::peek(src, end_or_sen);
          if (c == nullptr) {
            throw sst::to_integer_exception();
          }
          if (*c == '\'') {
            throw sst::to_integer_exception();
          }
        }
        int digit;
        if (*c >= char_t('0')
            && *c <= char_t('0' + sst::min(base, 9))) {
          digit = static_cast<int>(*c - char_t('0'));
          ++src;
          c = sst::peek(src, end_or_sen);
        } else if (base >= 11 && *c >= char_t('A')
                   && *c <= char_t('A' + (base - 11))) {
          digit = static_cast<int>(*c - char_t('A')) + 10;
          ++src;
          c = sst::peek(src, end_or_sen);
        } else if (base >= 11 && *c >= char_t('a')
                   && *c <= char_t('a' + (base - 11))) {
          digit = static_cast<int>(*c - char_t('a')) + 10;
          ++src;
          c = sst::peek(src, end_or_sen);
        } else {
          if (first_digit) {
            throw sst::to_integer_exception();
          }
          break;
        }
        if (value != 0) {
          value *= base;
        }
        if (sign < 0) {
          value -= digit;
        } else {
          value += digit;
        }
        first_digit = false;
      }
    }
    // TODO: Allow K, Ki, etc.
    if (c != nullptr) {
      throw sst::to_integer_exception();
    }
    return value.value();
  } catch (sst::checked_overflow const & e) {
    std::throw_with_nested(sst::to_integer_exception());
  }
}

} // namespace from_char_input_iterator
} // namespace to_integer
} // namespace guts

//----------------------------------------------------------------------
// src, end, options
//----------------------------------------------------------------------

template<class Dst, class Src, class End, class Options>
class to_integer_functor<
    sst::enable_if_t<sst::is_input_iterator<Src, sst::is_char>::value
                     && sst::is_sentinel<End, Src>::value
                     && !sst::is_sentinel<Options, Src>::value
                     && !sst::is_value_sentinel<Options, Src>::value>,
    Dst,
    Src,
    End,
    Options> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t src,
                   end_t const & end,
                   options_t const & options) const {
    return guts::to_integer::from_char_input_iterator::core<dst_t>(
        src,
        end,
        options);
  }

}; //

//----------------------------------------------------------------------
// src, sen, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen, class Options>
class to_integer_functor<
    sst::enable_if_t<sst::is_input_iterator<Src, sst::is_char>::value
                     && sst::is_value_sentinel<Sen, Src>::value
                     && !sst::is_sentinel<Options, Src>::value
                     && !sst::is_value_sentinel<Options, Src>::value>,
    Dst,
    Src,
    Sen,
    Options> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t src,
                   sen_t const & sen,
                   options_t const & options) const {
    return guts::to_integer::from_char_input_iterator::core<dst_t>(
        src,
        sen,
        options);
  }

}; //

//----------------------------------------------------------------------
// src, end
//----------------------------------------------------------------------

template<class Dst, class Src, class End>
class to_integer_functor<
    sst::enable_if_t<sst::is_input_iterator<Src, sst::is_char>::value
                     && sst::is_sentinel<End, Src>::value>,
    Dst,
    Src,
    End> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;

public:

  dst_t operator()(src_t src, end_t const & end) const {
    return guts::to_integer::from_char_input_iterator::core<dst_t>(
        src,
        end,
        sst::string_to_integer_options());
  }

}; //

//----------------------------------------------------------------------
// src, sen
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen>
class to_integer_functor<
    sst::enable_if_t<sst::is_input_iterator<Src, sst::is_char>::value
                     && sst::is_value_sentinel<Sen, Src>::value>,
    Dst,
    Src,
    Sen> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;

public:

  dst_t operator()(src_t src, sen_t const & sen) const {
    return guts::to_integer::from_char_input_iterator::core<dst_t>(
        src,
        sen,
        sst::string_to_integer_options());
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class to_integer_functor<
    sst::enable_if_t<sst::is_input_iterator<Src, sst::is_char>::value>,
    Dst,
    Src> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using src_value_t = sst::value_type_t<Src>;

public:

  dst_t operator()(src_t src) const {
    return guts::to_integer::from_char_input_iterator::core<dst_t>(
        src,
        src_value_t(),
        sst::string_to_integer_options());
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_TO_INTEGER_FROM_CHAR_INPUT_ITERATOR_HPP
