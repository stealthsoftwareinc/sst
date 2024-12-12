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

#ifndef SST_PRIVATE_JSON_QUOTE_ITERATOR_QA94410W_HPP
#define SST_PRIVATE_JSON_QUOTE_ITERATOR_QA94410W_HPP

#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/code_point_decoder.hpp>
#include <sst/catalog/code_point_encoder.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/json/quote_options.hpp>
#include <sst/catalog/malformed_code_point_action.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/pick_utf_encoding.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/text_encoding.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/unsigned_eq.hpp>
#include <sst/catalog/unsigned_ge.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/unsigned_le.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/json/quote.hpp>

// TODO: Is there any way we can support non-ASCII output? Seems
//       difficult to put into the options class since we're using
//       sst::is_output_iterator<Dst, char>::value all over. We'd need
//       to write out bigger code units for >=UTF-16. Maybe we can put
//       it into the options class, but it'd need to be constexpr so we
//       can evaluate it at template time to pick the right value type
//       for the output iterator.

namespace sst {
namespace json {

//----------------------------------------------------------------------
// Core algorithm
//----------------------------------------------------------------------

namespace guts {
namespace quote {
namespace iterator {

#define SST_r                                                          \
  (dst.template malformed_code_point_action<                           \
      Options::malformed_code_point_action()>())

template<
    class Options,
    class DecoderOptions,
    sst::enable_if_t<
        Options::has_compile_time_malformed_code_point_action()> = 0>
auto inherit_malformed_code_point_action(
    Options const &,
    DecoderOptions const & dst) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

#define SST_r                                                          \
  (dst.malformed_code_point_action(src.malformed_code_point_action()))

template<
    class Options,
    class DecoderOptions,
    sst::enable_if_t<
        !Options::has_compile_time_malformed_code_point_action()> = 0>
auto inherit_malformed_code_point_action(
    Options const & src,
    DecoderOptions const & dst) noexcept(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

template<class CodeUnit, class Size, class Dst>
void write_code_units(CodeUnit const * const src,
                      Size const size,
                      Dst & dst) {
  SST_ASSERT(src != nullptr);
  for (Size i = 0; i < size; ++i) {
    CodeUnit const c = src[i];
    SST_ASSERT(!sst::is_negative(c));
    if (sst::unsigned_eq(c, '"') || sst::unsigned_eq(c, '\\')
        || sst::unsigned_eq(c, '/')) {
      *dst = '\\';
      ++dst;
      *dst = static_cast<char>(c);
      ++dst;
    } else if (sst::unsigned_eq(c, '\b')) {
      *dst = '\\';
      ++dst;
      *dst = 'b';
      ++dst;
    } else if (sst::unsigned_eq(c, '\f')) {
      *dst = '\\';
      ++dst;
      *dst = 'f';
      ++dst;
    } else if (sst::unsigned_eq(c, '\n')) {
      *dst = '\\';
      ++dst;
      *dst = 'n';
      ++dst;
    } else if (sst::unsigned_eq(c, '\r')) {
      *dst = '\\';
      ++dst;
      *dst = 'r';
      ++dst;
    } else if (sst::unsigned_eq(c, '\t')) {
      *dst = '\\';
      ++dst;
      *dst = 't';
      ++dst;
    } else if (sst::unsigned_ge(c, 0x20) && sst::unsigned_le(c, 0x7E)) {
      *dst = static_cast<char>(c);
      ++dst;
    } else {
      *dst = '\\';
      ++dst;
      *dst = 'u';
      ++dst;
      unsigned long const x = static_cast<unsigned long>(c);
      for (int i = 12; i >= 0; i -= 4) {
        int const y = static_cast<int>((x >> i) & 0xFU);
        if (y < 10) {
          *dst = static_cast<char>('0' + static_cast<char>(y));
        } else {
          *dst = static_cast<char>('A' + static_cast<char>(y - 10));
        }
        ++dst;
      }
    }
  }
}

template<class Src,
         class EndOrSen,
         class Dst,
         class Options,
         sst::enable_if_t<Options::has_compile_time_src_encoding()> = 0>
void core(Src & src,
          EndOrSen const & end_or_sen,
          Dst & dst,
          Options const & options) {
  using src_value_t = sst::value_type_t<Src>;
  bool const allow_zero = options.has_allow_zero() ?
                              options.allow_zero() :
                              !sst::is_char<src_value_t>::value;
  constexpr sst::text_encoding src_encoding =
      Options::has_src_encoding() ?
          Options::src_encoding() :
          sst::pick_utf_encoding<src_value_t>();
  auto decoder = sst::code_point_decoder<src_encoding>(
      inherit_malformed_code_point_action(
          options,
          sst::code_point_decoder_options()));
  auto encoder = sst::code_point_encoder<sst::text_encoding::utf_16>();
  if (options.quote()) {
    *dst = '"';
    ++dst;
  }
  while (true) {
    auto const pc = sst::peek(src, end_or_sen);
    if (pc == nullptr) {
      decoder.flush();
      if (decoder.ready()) {
        encoder.put(decoder.get());
        write_code_units(encoder.get(), encoder.size(), dst);
      }
      break;
    }
    src_value_t const & c = *pc;
    if (!allow_zero && c == 0) {
      decoder.flush();
      if (decoder.ready()) {
        encoder.put(decoder.get());
        write_code_units(encoder.get(), encoder.size(), dst);
      }
      break;
    }
    // TODO: Support an option to check for out of range code units?
    decoder.put(c);
    if (decoder.ready()) {
      encoder.put(decoder.get());
      write_code_units(encoder.get(), encoder.size(), dst);
    }
    ++src;
  }
  if (options.quote()) {
    *dst = '"';
    ++dst;
  }
}

template<
    class Src,
    class EndOrSen,
    class Dst,
    class Options,
    sst::enable_if_t<!Options::has_compile_time_src_encoding()> = 0>
void core(Src & src,
          EndOrSen const & end_or_sen,
          Dst & dst,
          Options const & options) {

#define SST_F(x)                                                       \
  case x:                                                              \
    core(src, end_or_sen, dst, options.template src_encoding<x>());    \
    return

  switch (options.src_encoding()) {
    SST_F(sst::text_encoding::utf_8);
    SST_F(sst::text_encoding::utf_16);
    SST_F(sst::text_encoding::utf_32);
  }

#undef SST_F

  SST_ASSERT((false));
  std::abort();
}

} // namespace iterator
} // namespace quote
} // namespace guts

//----------------------------------------------------------------------
// src, end, dst, options
//----------------------------------------------------------------------

template<class Unused, class Src, class End, class Dst, class Options>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_sentinel<End, Src>::value
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
                   end_t const end,
                   dst_t dst,
                   options_t const & options) const {
    guts::quote::iterator::core(src, end, dst, options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end, dst
//----------------------------------------------------------------------

template<class Unused, class Src, class End, class Dst>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<Dst, char>::value>,
    Unused,
    Src,
    End,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t src, end_t const end, dst_t dst) const {
    guts::quote::iterator::core(src,
                                end,
                                dst,
                                sst::json::quote_options());
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end, options
//----------------------------------------------------------------------

template<class Dst, class Src, class End, class Options>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_sentinel<End, Src>::value
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

  dst_t
  operator()(src_t src, end_t end, options_t const & options) const {
    dst_t dst;
    sst::json::quote(std::move(src),
                     std::move(end),
                     std::back_inserter(dst),
                     options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end
//----------------------------------------------------------------------

template<class Dst, class Src, class End>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_sentinel<End, Src>::value>,
    Dst,
    Src,
    End> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;

public:

  dst_t operator()(src_t src, end_t end) const {
    dst_t dst;
    sst::json::quote(std::move(src),
                     std::move(end),
                     std::back_inserter(dst),
                     sst::json::quote_options());
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen, dst, options
//----------------------------------------------------------------------

template<class Unused, class Src, class Sen, class Dst, class Options>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst, char>::value
        && !sst::is_sentinel<Options, Src>::value
        && !sst::is_value_sentinel<Options, Src>::value
        && !sst::is_output_iterator<Options, char>::value>,
    Unused,
    Src,
    Sen,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t src,
                   sen_t const & sen,
                   dst_t dst,
                   options_t const & options) const {
    guts::quote::iterator::core(src, sen, dst, options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen, dst
//----------------------------------------------------------------------

template<class Unused, class Src, class Sen, class Dst>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst, char>::value>,
    Unused,
    Src,
    Sen,
    Dst> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t src, sen_t const & sen, dst_t dst) const {
    guts::quote::iterator::core(src,
                                sen,
                                dst,
                                sst::json::quote_options());
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen, class Options>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && !sst::is_sentinel<Options, Src>::value
        && !sst::is_value_sentinel<Options, Src>::value
        && !sst::is_output_iterator<Options, char>::value>,
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
    dst_t dst;
    sst::json::quote(std::move(src),
                     sen,
                     std::back_inserter(dst),
                     options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && sst::is_value_sentinel<Sen, Src>::value>,
    Dst,
    Src,
    Sen> {

  using dst_t = sst::remove_cvref_t<Dst>;
  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;

public:

  dst_t operator()(src_t src, sen_t const & sen) const {
    dst_t dst;
    sst::json::quote(std::move(src),
                     sen,
                     std::back_inserter(dst),
                     sst::json::quote_options());
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value
        && !sst::is_sentinel<Options, Src>::value
        && !sst::is_value_sentinel<Options, Src>::value
        && !sst::is_output_iterator<Options, char>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using src_value_t = sst::value_type_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using options_t = sst::remove_cvref_t<Options>;

public:

  dst_t operator()(src_t src, options_t const & options) const {
    dst_t dst;
    sst::json::quote(std::move(src),
                     src_value_t(),
                     std::back_inserter(dst),
                     options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src
//----------------------------------------------------------------------

template<class Dst, class Src>
class quote_functor<
    sst::enable_if_t<
        sst::is_input_iterator<Src, sst::is_integer_ish>::value>,
    Dst,
    Src> {

  using src_t = sst::remove_cvref_t<Src>;
  using src_value_t = sst::value_type_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;

public:

  dst_t operator()(src_t src) const {
    dst_t dst;
    sst::json::quote(std::move(src),
                     src_value_t(),
                     std::back_inserter(dst),
                     sst::json::quote_options());
    return dst;
  }

}; //

//----------------------------------------------------------------------

} // namespace json
} // namespace sst

#endif // SST_PRIVATE_JSON_QUOTE_ITERATOR_QA94410W_HPP
