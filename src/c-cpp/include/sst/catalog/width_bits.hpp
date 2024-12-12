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

#ifndef SST_CATALOG_WIDTH_BITS_HPP
#define SST_CATALOG_WIDTH_BITS_HPP

#include <type_traits>

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_bits.hpp>

namespace sst {

//----------------------------------------------------------------------

template<class, class = sst::enable_t>
class width_bits;

//----------------------------------------------------------------------

template<class T>
class width_bits<T, sst::enable_if_t<sst::is_integer<T>::value>>
    : public std::integral_constant<
          sst::remove_cvref_t<T>,
          static_cast<sst::remove_cvref_t<T>>(
              sst::value_bits<T>::value
              + static_cast<sst::remove_cvref_t<T>>(
                  std::is_signed<T>::value))> {};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_WIDTH_BITS_HPP
