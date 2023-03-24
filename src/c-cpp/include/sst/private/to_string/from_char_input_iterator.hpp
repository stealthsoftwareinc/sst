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

#ifndef SST_PRIVATE_TO_STRING_FROM_CHAR_INPUT_ITERATOR_HPP
#define SST_PRIVATE_TO_STRING_FROM_CHAR_INPUT_ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_char_input_iterator.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/is_representable_as.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/string_to_string_options.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/guts/to_string/has_member_function.hpp>
#include <sst/private/to_string.hpp>

namespace sst {

//----------------------------------------------------------------------
// src, end, dst, options
//----------------------------------------------------------------------

template<class DstValue, class Src, class End, class Dst, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<DstValue, Src, End, Dst, Options>::value
        && sst::is_char_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<Dst>::value
        && std::is_convertible<Options,
                               sst::string_to_string_options>::value>,
    DstValue,
    Src,
    End,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;
  using dst_value_t =
      typename std::conditional<sst::is_integer<DstValue>::value,
                                sst::remove_cvref_t<DstValue>,
                                sst::value_type_t<dst_t>>::type;

  // clang-format off
  SST_STATIC_ASSERT("When the output value type is unspecified, the value type of the output iterator must be an integer type." && (sst::is_integer<dst_value_t>::value));
  // clang-format on

public:

  dst_t
  operator()(src_t src,
             end_t const end,
             dst_t dst,
             sst::string_to_string_options const & options = {}) const {
    if (options.replace_unrepresentable()) {
      for (; !(src == end); ++src) {
        src_value_t const c = *src;
        if (c == 0) {
          break;
        }
        if (sst::is_representable_as<dst_value_t>(c)) {
          *dst = static_cast<dst_value_t>(c);
        } else {
          *dst = static_cast<dst_value_t>('?');
        }
        ++dst;
      }
    } else {
      for (; !(src == end); ++src) {
        src_value_t const c = *src;
        if (c == 0) {
          break;
        }
        *dst = sst::checked_cast<dst_value_t>(c);
        ++dst;
      }
    }
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end, dst
//----------------------------------------------------------------------

template<class DstValue, class Src, class End, class Dst>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<DstValue, Src, End, Dst>::value
        && sst::is_char_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && sst::is_output_iterator<Dst>::value>,
    DstValue,
    Src,
    End,
    Dst> : public to_string_functor<sst::enable_t,
                                    DstValue,
                                    Src,
                                    End,
                                    Dst,
                                    sst::string_to_string_options> {};

//----------------------------------------------------------------------
// src, end, options
//----------------------------------------------------------------------

template<class Dst, class Src, class End, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<Dst, Src, End, Options>::value
        && sst::is_char_input_iterator<Src>::value
        && sst::is_sentinel<End, Src>::value
        && std::is_convertible<Options,
                               sst::string_to_string_options>::value>,
    Dst,
    Src,
    End,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using end_t = sst::remove_cvref_t<End>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;

public:

  dst_t
  operator()(src_t src,
             end_t end,
             sst::string_to_string_options const & options = {}) const {
    dst_t dst;
    using dst_value_t = sst::value_type_t<decltype(dst)>;
    sst::to_string<dst_value_t>(std::move(src),
                                std::move(end),
                                std::back_inserter(dst),
                                options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, end
//----------------------------------------------------------------------

template<class DstValue, class Src, class End>
class to_string_functor<
    sst::enable_if_t<!sst::guts::to_string::
                         has_member_function<DstValue, Src, End>::value
                     && sst::is_char_input_iterator<Src>::value
                     && sst::is_sentinel<End, Src>::value>,
    DstValue,
    Src,
    End> : public to_string_functor<sst::enable_t,
                                    DstValue,
                                    Src,
                                    End,
                                    sst::string_to_string_options> {};

//----------------------------------------------------------------------
// src, sen, dst, options
//----------------------------------------------------------------------

template<class DstValue, class Src, class Sen, class Dst, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<DstValue, Src, Sen, Dst, Options>::value
        && sst::is_char_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst>::value
        && std::is_convertible<Options,
                               sst::string_to_string_options>::value>,
    DstValue,
    Src,
    Sen,
    Dst,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using sen_t = sst::remove_cvref_t<Sen>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<src_t>;
  using dst_value_t =
      typename std::conditional<sst::is_integer<DstValue>::value,
                                sst::remove_cvref_t<DstValue>,
                                sst::value_type_t<dst_t>>::type;

  // clang-format off
  SST_STATIC_ASSERT("When the output value type is unspecified, the value type of the output iterator must be an integer type." && (sst::is_integer<dst_value_t>::value));
  // clang-format on

public:

  dst_t
  operator()(src_t src,
             sen_t const & sen,
             dst_t dst,
             sst::string_to_string_options const & options = {}) const {
    if (options.replace_unrepresentable()) {
      for (;; ++src) {
        src_value_t const c = *src;
        if (c == sen) {
          return dst;
        }
        if (sst::is_representable_as<dst_value_t>(c)) {
          *dst = static_cast<dst_value_t>(c);
        } else {
          *dst = static_cast<dst_value_t>('?');
        }
        ++dst;
      }
    } else {
      for (;; ++src) {
        src_value_t const c = *src;
        if (c == sen) {
          return dst;
        }
        *dst = sst::checked_cast<dst_value_t>(c);
        ++dst;
      }
    }
  }

}; //

//----------------------------------------------------------------------
// src, sen, dst
//----------------------------------------------------------------------

template<class DstValue, class Src, class Sen, class Dst>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<DstValue, Src, Sen, Dst>::value
        && sst::is_char_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && sst::is_output_iterator<Dst>::value>,
    DstValue,
    Src,
    Sen,
    Dst> : public to_string_functor<sst::enable_t,
                                    DstValue,
                                    Src,
                                    Sen,
                                    Dst,
                                    sst::string_to_string_options> {};

//----------------------------------------------------------------------
// src, sen, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Sen, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::
            has_member_function<Dst, Src, Sen, Options>::value
        && sst::is_char_input_iterator<Src>::value
        && sst::is_value_sentinel<Sen, Src>::value
        && std::is_convertible<Options,
                               sst::string_to_string_options>::value>,
    Dst,
    Src,
    Sen,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using sen_t = sst::remove_cvref_t<Sen>;

public:

  dst_t
  operator()(src_t src,
             sen_t const & sen,
             sst::string_to_string_options const & options = {}) const {
    dst_t dst;
    sst::to_string(std::move(src),
                   sen,
                   std::back_inserter(dst),
                   options);
    return dst;
  }

}; //

//----------------------------------------------------------------------
// src, sen
//----------------------------------------------------------------------

template<class DstValue, class Src, class Sen>
class to_string_functor<
    sst::enable_if_t<!sst::guts::to_string::
                         has_member_function<DstValue, Src, Sen>::value
                     && sst::is_char_input_iterator<Src>::value
                     && sst::is_value_sentinel<Sen, Src>::value>,
    DstValue,
    Src,
    Sen> : public to_string_functor<sst::enable_t,
                                    DstValue,
                                    Src,
                                    Sen,
                                    sst::string_to_string_options> {};

//----------------------------------------------------------------------
// src, options
//----------------------------------------------------------------------

template<class Dst, class Src, class Options>
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<Dst, Src, Options>::
            value
        && sst::is_char_input_iterator<Src>::value
        && std::is_convertible<Options,
                               sst::string_to_string_options>::value>,
    Dst,
    Src,
    Options> {

  using src_t = sst::remove_cvref_t<Src>;
  using dst_t = sst::remove_cvref_t<Dst>;
  using src_value_t = sst::value_type_t<Src>;

public:

  dst_t
  operator()(src_t src,
             sst::string_to_string_options const & options = {}) const {
    dst_t dst;
    sst::to_string(std::move(src),
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
class to_string_functor<
    sst::enable_if_t<
        !sst::guts::to_string::has_member_function<Dst, Src>::value
        && sst::is_char_input_iterator<Src>::value>,
    Dst,
    Src> : public to_string_functor<sst::enable_t,
                                    Dst,
                                    Src,
                                    sst::string_to_string_options> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // #ifndef SST_PRIVATE_TO_STRING_FROM_CHAR_INPUT_ITERATOR_HPP
