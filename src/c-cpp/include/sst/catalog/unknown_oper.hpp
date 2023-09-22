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

#ifndef SST_CATALOG_UNKNOWN_OPER_HPP
#define SST_CATALOG_UNKNOWN_OPER_HPP

#include <stdexcept>
#include <utility>

#include <sst/catalog/SST_NORETURN.h>
#include <sst/catalog/begin.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_char.hpp>

namespace sst {

template<class Operand,
         sst::enable_if_t<sst::is_char<
             decltype(std::declval<Operand const &>()[0])>::value> = 0>
SST_NORETURN()
void unknown_oper(Operand const & operand) {
  throw std::runtime_error("Unknown operand: " + sst::c_quote(operand));
}

template<class Operands,
         sst::enable_if_t<sst::is_char<decltype((*sst::begin(
             std::declval<Operands const &>()))[0])>::value> = 0>
SST_NORETURN()
void unknown_oper(Operands const & operands) {
  unknown_oper(*sst::begin(operands));
}

} // namespace sst

#endif // SST_CATALOG_UNKNOWN_OPER_HPP
