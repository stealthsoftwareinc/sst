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

#ifndef SST_CATALOG_PICK_UTF_ENCODING_HPP
#define SST_CATALOG_PICK_UTF_ENCODING_HPP

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/numeric_limits.hpp>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/text_encoding.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>

namespace sst {

template<
    class T,
    sst::enable_if_t<sst::is_integer_ish<T>::value
                     && sst::numeric_limits<T>::is_specialized
                     && sst::is_negative(sst::type_min<T>::value)> = 0>
constexpr sst::text_encoding pick_utf_encoding() noexcept {
  return sst::type_min<T>::value < -sst::ones_mask<long>(31)
                 && sst::type_max<T>::value
                        >= sst::ones_mask<long>(31) ?
             sst::text_encoding::utf_32 :
         sst::type_min<T>::value < -sst::ones_mask<long>(15)
                 && sst::type_max<T>::value
                        >= sst::ones_mask<long>(15) ?
             sst::text_encoding::utf_16 :
             sst::text_encoding::utf_8;
}

template<
    class T,
    sst::enable_if_t<sst::is_integer_ish<T>::value
                     && sst::numeric_limits<T>::is_specialized
                     && !sst::is_negative(sst::type_min<T>::value)> = 0>
constexpr sst::text_encoding pick_utf_encoding() noexcept {
  return sst::type_max<T>::value >= sst::ones_mask<unsigned long>(32) ?
             sst::text_encoding::utf_32 :
         sst::type_max<T>::value >= sst::ones_mask<unsigned long>(16) ?
             sst::text_encoding::utf_16 :
             sst::text_encoding::utf_8;
}

template<
    class T,
    sst::enable_if_t<sst::is_integer_ish<T>::value
                     && !sst::numeric_limits<T>::is_specialized> = 0>
constexpr sst::text_encoding pick_utf_encoding() noexcept {
  return sst::text_encoding::utf_32;
}

} // namespace sst

#endif // SST_CATALOG_PICK_UTF_ENCODING_HPP
