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

#ifndef SST_CATALOG_SST_UNREACHABLE_HPP
#define SST_CATALOG_SST_UNREACHABLE_HPP

#if 0

//----------------------------------------------------------------------
#elif 0 // TODO: SST_CPP23_OR_LATER
//----------------------------------------------------------------------

#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>

#define SST_UNREACHABLE()                                              \
  (SST_ASSERT(false, "Unreachable code reached"), ::std::unreachable())

//----------------------------------------------------------------------
#else
//----------------------------------------------------------------------

#include <cstdlib>

#include <sst/catalog/SST_ASSERT.hpp>

#define SST_UNREACHABLE()                                              \
  (SST_ASSERT(false, "Unreachable code reached"), ::std::abort())

//----------------------------------------------------------------------
#endif

#endif // SST_CATALOG_SST_UNREACHABLE_HPP
