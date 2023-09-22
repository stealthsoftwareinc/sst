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

#ifndef SST_CATALOG_MONO_TIME_HPP
#define SST_CATALOG_MONO_TIME_HPP

#include <chrono>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/mono_time_zero.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

//----------------------------------------------------------------------

template<class Duration>
Duration mono_time() {
  // sst::mono_time_zero() picks its zero value on its first call, so we
  // need to call it before std::chrono::steady_clock::now(). If we were
  // to write std::chrono::steady_clock::now() - sst::mono_time_zero(),
  // the left operand could be evaluated before the right operand, which
  // would produce an incorrect result when the right operand happens to
  // be the first call to sst::mono_time_zero().
  auto const a = sst::mono_time_zero();
  auto const b = std::chrono::steady_clock::now();
  SST_ASSERT((b >= a));
  return std::chrono::duration_cast<Duration>(b - a);
}

//----------------------------------------------------------------------

extern template SST_DLL_EXPORT std::chrono::seconds
mono_time<std::chrono::seconds>();

//----------------------------------------------------------------------

extern template SST_DLL_EXPORT std::chrono::milliseconds
mono_time<std::chrono::milliseconds>();

//----------------------------------------------------------------------

extern template SST_DLL_EXPORT std::chrono::microseconds
mono_time<std::chrono::microseconds>();

//----------------------------------------------------------------------

extern template SST_DLL_EXPORT std::chrono::nanoseconds
mono_time<std::chrono::nanoseconds>();

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_MONO_TIME_HPP
