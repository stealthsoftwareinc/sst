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

#ifndef SST_CATALOG_ASCII_LOWER_HPP
#define SST_CATALOG_ASCII_LOWER_HPP

#include <string>

#include <sst/catalog/SST_DEFINE_ALGORITHM.hpp>
#include <sst/catalog/decay_t.hpp>

namespace sst {

SST_DEFINE_ALGORITHM(ascii_lower,
                     (class Dst = std::string),
                     (sst::decay_t<Dst>))

} // namespace sst

#include <sst/private/ascii_lower/from_char.hpp>
#include <sst/private/ascii_lower/from_char_input_iterable.hpp>
#include <sst/private/ascii_lower/from_char_input_iterator.hpp>

#endif // SST_CATALOG_ASCII_LOWER_HPP
