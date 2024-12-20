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

#ifndef SST_CATALOG_COUNT_IT_HPP
#define SST_CATALOG_COUNT_IT_HPP

#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/guts/it_t.hpp>

namespace sst {

//----------------------------------------------------------------------
//
// Returns a sentinel iterator that will compare equal to i after i has
// been incremented n times.
//

template<class Count,
         class Iterator,
         class T = sst::remove_cvref_t<Count>>
guts::it_t<Iterator, T> count_it(Iterator const i, Count const n) {
  return guts::it_t<Iterator, T>(nullptr, i, true, n, 0, false);
}

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_COUNT_IT_HPP
