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

#ifndef SST_PRIVATE_C_QUOTE_ITERATOR_HPP
#define SST_PRIVATE_C_QUOTE_ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/c_quote_options.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/integer_to_string_options.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/value_sentinel.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/c_quote.hpp>

namespace sst {

namespace guts {
namespace c_quote {
namespace from_byte_or_char_input_iterator {

template<class src_t, class end_t, class dst_t, class options_t>
void core(src_t & src,
          end_t const & end,
          dst_t & dst,
          options_t const & options) {
  using src_value_t = sst::value_type_t<src_t>;
  bool const allow_zero = options.has_allow_zero() ?
                              options.allow_zero() :
                              !sst::is_char<src_value_t>::value;
  if (options.quote()) {
    if (std::is_same<src_value_t, wchar_t>::value) {
      *dst = 'L';
      ++dst;
    } else if (std::is_same<src_value_t, char16_t>::value) {
      *dst = 'u';
      ++dst;
    } else if (std::is_same<src_value_t, char32_t>::value) {
      *dst = 'U';
      ++dst;
#if SST_CPP20_OR_LATER
    } else if (std::is_same<src_value_t, char8_t>::value) {
      *dst = 'u';
      ++dst;
      *dst = '8';
      ++dst;
#endif
    }
    *dst = '"';
    ++dst;
  }
  bool protect_hex = false;
  bool protect_tri = false;
  while (true) {
    auto const pc = sst::peek(src, end);
    if (pc == nullptr) {
      break;
    }
    src_value_t const & c = *pc;
    if (!allow_zero && c == 0) {
      break;
    }
    ++src;
    if (c >= src_value_t(' ') && c <= src_value_t('~')) {
      if (protect_hex
          && ((c >= src_value_t('0') && c <= src_value_t('9'))
              || (c >= src_value_t('A') && c <= src_value_t('F'))
              || (c >= src_value_t('a') && c <= src_value_t('f')))) {
        *dst = '"';
        ++dst;
        *dst = '"';
        ++dst;
      } else if (protect_tri && c == src_value_t('?')) {
        *dst = '\\';
        ++dst;
      }
      *dst = static_cast<char>(c);
      ++dst;
      protect_hex = false;
      protect_tri = c == src_value_t('?');
    } else if (c == src_value_t('\a')) {
      *dst = '\\';
      ++dst;
      *dst = 'a';
      ++dst;
    } else if (c == src_value_t('\b')) {
      *dst = '\\';
      ++dst;
      *dst = 'b';
      ++dst;
    } else if (c == src_value_t('\f')) {
      *dst = '\\';
      ++dst;
      *dst = 'f';
      ++dst;
    } else if (c == src_value_t('\n')) {
      *dst = '\\';
      ++dst;
      *dst = 'n';
      ++dst;
    } else if (c == src_value_t('\r')) {
      *dst = '\\';
      ++dst;
      *dst = 'r';
      ++dst;
    } else if (c == src_value_t('\t')) {
      *dst = '\\';
      ++dst;
      *dst = 't';
      ++dst;
    } else if (c == src_value_t('\v')) {
      *dst = '\\';
      ++dst;
      *dst = 'v';
      ++dst;
    } else {
      *dst = '\\';
      ++dst;
      *dst = 'x';
      ++dst;
      dst = sst::to_string(c,
                           dst,
                           sst::integer_to_string_options().base(16));
      protect_hex = true;
      protect_tri = false;
    }
  }
  if (options.quote()) {
    *dst = '"';
    ++dst;
  }
}

} // namespace from_byte_or_char_input_iterator
} // namespace c_quote
} // namespace guts

//----------------------------------------------------------------------
// src, end, dst, options
//----------------------------------------------------------------------

template<class Unused, class Src, class End, class Dst, class Options>
class c_quote_functor<
    sst::enable_if_t<
        (sst::is_input_iterator<Src, sst::is_byte>::value
         || sst::is_input_iterator<Src, sst::is_char>::value)
        && (sst::is_sentinel<End, Src>::value
            || sst::is_value_sentinel<End, Src>::value)
        && sst::is_output_iterator<Dst, char>::value
        && !sst::is_sentinel<Options, Src>::value
        && !sst::is_value_sentinel<Options, Src>::value
        && !sst::is_output_iterator<Options, char>::value>,
    Unused,
    Src,
    End,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t src,
                   end_t const & end,
                   dst_t dst,
                   options_t const & options) const {
    guts::c_quote::from_byte_or_char_input_iterator::core(src,
                                                          end,
                                                          dst,
                                                          options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end, dst
//----------------------------------------------------------------------

template<class Unused, class Src, class End, class Dst>
class c_quote_functor<
    sst::enable_if_t<
        (sst::is_input_iterator<Src, sst::is_byte>::value
         || sst::is_input_iterator<Src, sst::is_char>::value)
        && (sst::is_sentinel<End, Src>::value
            || sst::is_value_sentinel<End, Src>::value)
        && sst::is_output_iterator<Dst, char>::value>,
    Unused,
    Src,
    End,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t src, end_t const & end, dst_t dst) const {
    return sst::c_quote(std::move(src),
                        end,
                        std::move(dst),
                        sst::c_quote_options());
  }

}; //

//----------------------------------------------------------------------
// src, end, options
//----------------------------------------------------------------------

template<class Dst, class Src, class End, class Options>
class c_quote_functor<
    sst::enable_if_t<
        (sst::is_input_iterator<Src, sst::is_byte>::value
         || sst::is_input_iterator<Src, sst::is_char>::value)
        && (sst::is_sentinel<End, Src>::value
            || sst::is_value_sentinel<End, Src>::value)
        && !sst::is_sentinel<Options, Src>::value
        && !sst::is_value_sentinel<Options, Src>::value
        && !sst::is_output_iterator<Options, char>::value>,
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
    dst_t dst;
    sst::c_quote(std::move(src), end, std::back_inserter(dst), options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end
//----------------------------------------------------------------------

template<class Dst, class Src, class End>
class c_quote_functor<
    sst::enable_if_t<
        (sst::is_input_iterator<Src, sst::is_byte>::value
         || sst::is_input_iterator<Src, sst::is_char>::value)
        && (sst::is_sentinel<End, Src>::value
            || sst::is_value_sentinel<End, Src>::value)>,
    Dst,
    Src,
    End> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;

public:

  dst_t operator()(src_t src, end_t const & end) const {
    return sst::c_quote(std::move(src), end, sst::c_quote_options());
  }

}; //

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class c_quote_functor<
    sst::enable_if_t<
        (sst::is_input_iterator<Src, sst::is_byte>::value
         || sst::is_input_iterator<Src, sst::is_char>::value)
        && !sst::is_sentinel<Options, Src>::value
        && !sst::is_value_sentinel<Options, Src>::value
        && !sst::is_output_iterator<Options, char>::value>,
    Dst,
    Src,
    Options> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using options_t = sst::remove_cvref_t<Options>;
  using src_value_t = sst::value_type_t<Src>;

public:

  dst_t operator()(src_t src, options_t const & options) const {
    return sst::c_quote(std::move(src),
                        sst::value_sentinel(src_value_t()),
                        options);
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class c_quote_functor<
    sst::enable_if_t<(
        sst::is_input_iterator<Src, sst::is_byte>::value
        || sst::is_input_iterator<Src, sst::is_char>::value)>,
    Dst,
    Src> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;

public:

  dst_t operator()(src_t src) const {
    return sst::c_quote(std::move(src), sst::c_quote_options());
  }

}; //

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_PRIVATE_C_QUOTE_ITERATOR_HPP
