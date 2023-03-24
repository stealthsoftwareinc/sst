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

// Include first to test independence.
#include <sst/catalog/what.hpp>
// Include twice to test idempotence.
#include <sst/catalog/what.hpp>
//

#include <exception>
#include <string>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/what_suffix.hpp>

namespace sst {

namespace {

void chain(std::string & s,
           std::exception const & exception,
           char const * const separator,
           char const * const prefix) {
  SST_ASSERT(prefix != nullptr);
  s += prefix;
  s += exception.what();
  try {
    std::rethrow_if_nested(exception);
  } catch (std::exception const & e) {
    chain(s, e, separator, sst::what_suffix(exception, separator));
  }
}

} // namespace

std::string what::message(std::exception const & exception,
                          char const * const separator) {
  std::string s = exception.what();
  try {
    std::rethrow_if_nested(exception);
  } catch (std::exception const & e) {
    chain(s, e, separator, sst::what_suffix(exception, separator));
  }
  s += '.';
  return s;
}

} // namespace sst
