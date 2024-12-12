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

#ifndef SST_CATALOG_STEP_HPP
#define SST_CATALOG_STEP_HPP

#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/pos.hpp>

namespace sst {

template<class Src,
         class End,
         sst::enable_if_t<sst::is_input_iterator<Src>::value
                          && sst::is_sentinel<End, Src>::value> = 0>
void step(Src & src, End const &) noexcept(noexcept(++src)) {
  ++src;
}

template<
    class Src,
    class End,
    sst::enable_if_t<sst::is_input_iterator<Src>::value
                     && sst::is_value_sentinel<End, Src>::value> = 0>
void step(Src & src, End const &) noexcept(noexcept(++src)) {
  ++src;
}

template<class Src,
         class End,
         sst::enable_if_t<
             sst::is_input_iterator<Src>::value
             && (sst::is_sentinel<End, Src>::value
                 || sst::is_value_sentinel<End, Src>::value)> = 0>
void step(Src & src, End const & end, sst::pos<Src, End> &) noexcept(
    noexcept(sst::step(src, end))) {
  sst::step(src, end);
}

template<class Src,
         class End,
         sst::enable_if_t<sst::is_input_iterator<Src>::value
                          && sst::is_integer_ish<End>::value> = 0>
void step(Src & src, End const &, sst::pos<Src, End> & pos) noexcept(
    noexcept((++src, ++pos.value))) {
  ++src;
  ++pos.value;
}

} // namespace sst

#endif // SST_CATALOG_STEP_HPP
