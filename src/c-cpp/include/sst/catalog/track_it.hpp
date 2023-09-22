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

#ifndef SST_CATALOG_TRACK_IT_HPP
#define SST_CATALOG_TRACK_IT_HPP

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/guts/it_t.hpp>

namespace sst {

//----------------------------------------------------------------------
//
// Returns a wrapper iterator around i that updates i as it moves.
//

template<class Count = int,
         class Iterator,
         sst::enable_if_t<sst::is_integer_ish<Count>::value> = 0,
         class W = guts::it_t<Iterator, sst::remove_cvref_t<Count>>>
W track_it(Iterator & i) {
  using Tag = typename W::track_it_tag;
  return W(Tag(), i);
}

//----------------------------------------------------------------------
//
// Returns a wrapper iterator around i that updates i as it moves and
// limits the number of increments to n. This should only be used for
// single pass algorithms.
//

template<class Count,
         class Iterator,
         sst::enable_if_t<sst::is_integer_ish<Count>::value> = 0,
         class W = guts::it_t<Iterator, sst::remove_cvref_t<Count>>>
W track_it(Iterator & i, Count const & n) {
  using Tag = typename W::track_it_tag;
  return W(Tag(), i, n);
}

//----------------------------------------------------------------------
//
// Returns a wrapper iterator around i that updates i as it moves and
// limits the number of increments to *n. Also updates *n as it moves.
// This should only be used for single pass algorithms.
//

template<class Count,
         class Iterator,
         sst::enable_if_t<sst::is_integer_ish<Count>::value> = 0,
         class W = guts::it_t<Iterator, sst::remove_cvref_t<Count>>>
W track_it(Iterator & i, Count * const n) {
  SST_ASSERT((n != nullptr));
  using Tag = typename W::track_it_tag;
  return W(Tag(), i, n);
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_TRACK_IT_HPP
