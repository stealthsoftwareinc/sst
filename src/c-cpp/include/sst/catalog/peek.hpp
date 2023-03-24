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

#ifndef SST_CATALOG_PEEK_HPP
#define SST_CATALOG_PEEK_HPP

#include <utility>

#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/peek_ptr.hpp>
#include <sst/catalog/pos.hpp>

namespace sst {

template<class Src,
         class End,
         sst::enable_if_t<sst::is_input_iterator<Src>::value
                          && sst::is_sentinel<End, Src>::value> = 0>
SST_NODISCARD()
constexpr sst::peek_ptr<Src> peek(
    Src const & src,
    End const & end) noexcept(SST_NOEXCEPT(src == end ?
                                               sst::peek_ptr<Src>() :
                                               sst::peek_ptr<Src>(
                                                   src))) {
  return src == end ? sst::peek_ptr<Src>() : sst::peek_ptr<Src>(src);
}

template<
    class Src,
    class End,
    sst::enable_if_t<sst::is_input_iterator<Src>::value
                     && sst::is_value_sentinel<End, Src>::value> = 0>
SST_NODISCARD()
sst::peek_ptr<Src> peek(Src const & src, End const & end) noexcept(
    SST_NOEXCEPT(*sst::peek_ptr<Src>(src) == end,
                 sst::peek_ptr<Src>(),
                 sst::peek_ptr<Src>(sst::peek_ptr<Src>(src)))) {
  sst::peek_ptr<Src> ptr(src);
  return *ptr == end ? sst::peek_ptr<Src>() : std::move(ptr);
}

template<class Src,
         class End,
         sst::enable_if_t<
             sst::is_input_iterator<Src>::value
             && (sst::is_sentinel<End, Src>::value
                 || sst::is_value_sentinel<End, Src>::value)> = 0>
SST_NODISCARD()
constexpr auto peek(
    Src const & src,
    End const & end,
    sst::pos<Src, End> const &) noexcept(SST_NOEXCEPT(sst::peek(src,
                                                                end)))
    -> decltype(sst::peek(src, end)) {
  return sst::peek(src, end);
}

template<class Src,
         class End,
         sst::enable_if_t<sst::is_input_iterator<Src>::value
                          && sst::is_integer_ish<End>::value> = 0>
SST_NODISCARD()
constexpr sst::peek_ptr<Src> peek(
    Src const & src,
    End const & end,
    sst::pos<Src, End> const &
        pos) noexcept(SST_NOEXCEPT(pos.value == end ?
                                       sst::peek_ptr<Src>() :
                                       sst::peek_ptr<Src>(src))) {
  return pos.value == end ? sst::peek_ptr<Src>() :
                            sst::peek_ptr<Src>(src);
}

} // namespace sst

#endif // #ifndef SST_CATALOG_PEEK_HPP
