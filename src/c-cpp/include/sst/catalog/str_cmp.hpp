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

#ifndef SST_CATALOG_STR_CMP_HPP
#define SST_CATALOG_STR_CMP_HPP

#include <iterator>

namespace sst {

template<class IteratorA,
         class IteratorB,
         class ValueType =
             typename std::iterator_traits<IteratorA>::value_type>
constexpr int str_cmp(IteratorA a,
                      IteratorB b,
                      ValueType const & null_terminator = ValueType()) {
  return *a == null_terminator ? (*b == null_terminator ? 0 : -1) :
         *b == null_terminator ? 1 :
         *a < *b               ? -1 :
         *b < *a               ? 1 :
                                 str_cmp(++a, ++b, null_terminator);
}

} // namespace sst

#endif // SST_CATALOG_STR_CMP_HPP
