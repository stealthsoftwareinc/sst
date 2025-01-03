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

#ifndef SST_CATALOG_SST_TEV_ARG_HPP
#define SST_CATALOG_SST_TEV_ARG_HPP

#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/guts/tracing_event/dummy.hpp>

#define SST_TEV_ARG_HELPER(tev, ...)                                   \
  ([&] {                                                               \
    if (::sst::remove_cvref_t<decltype((tev))>::enabled()) {           \
      try {                                                            \
        return ::sst::remove_cvref_t<decltype((tev))>(__FILE__,        \
                                                      __LINE__,        \
                                                      (tev),           \
                                                      __VA_ARGS__);    \
      } catch (...) {                                                  \
      }                                                                \
    }                                                                  \
    return ::sst::remove_cvref_t<decltype((tev))>(__FILE__, __LINE__); \
  }())

#define SST_TEV_ARG(...)                                               \
  (SST_TEV_ARG_HELPER(__VA_ARGS__, ::sst::guts::tracing_event::dummy()))

#endif // SST_CATALOG_SST_TEV_ARG_HPP
