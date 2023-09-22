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

#ifndef SST_CATALOG_PRECISE_SLEEP_UNTIL_MONO_TIME_NS_HPP
#define SST_CATALOG_PRECISE_SLEEP_UNTIL_MONO_TIME_NS_HPP

#include <chrono>
#include <thread>

#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/mono_time_ns.hpp>
#include <sst/catalog/mono_time_ns_t.hpp>
#include <sst/catalog/sleep_slop.hpp>

namespace sst {

template<class Time>
sst::mono_time_ns_t precise_sleep_until_mono_time_ns(Time const & t) {
  sst::mono_time_ns_t const b =
      sst::checked_cast<sst::mono_time_ns_t>(t);
  sst::mono_time_ns_t a = sst::mono_time_ns();
  while (b - a > sst::sleep_slop()) {
    std::this_thread::sleep_for(
        std::chrono::nanoseconds(b - a - sst::sleep_slop()));
    a = sst::mono_time_ns();
  }
  while (b > a) {
    a = sst::mono_time_ns();
  }
  return a;
}

} // namespace sst

#endif // SST_CATALOG_PRECISE_SLEEP_UNTIL_MONO_TIME_NS_HPP
