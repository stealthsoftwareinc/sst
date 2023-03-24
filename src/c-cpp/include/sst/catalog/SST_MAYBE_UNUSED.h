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

#ifndef SST_CATALOG_SST_MAYBE_UNUSED_H
#define SST_CATALOG_SST_MAYBE_UNUSED_H

#include <sst/catalog/SST_C23_OR_LATER.h>
#include <sst/catalog/SST_CPP17_OR_LATER.h>

// clang-format off

#if SST_C23_OR_LATER || SST_CPP17_OR_LATER
  #define SST_MAYBE_UNUSED(...) [[maybe_unused __VA_ARGS__]]
#elif defined(__GNUC__)
  #define SST_MAYBE_UNUSED(...) __attribute__((__unused__))
#else
  #define SST_MAYBE_UNUSED(...)
#endif

// clang-format on

#endif // #ifndef SST_CATALOG_SST_MAYBE_UNUSED_H