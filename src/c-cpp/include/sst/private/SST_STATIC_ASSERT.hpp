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

#ifndef SST_PRIVATE_SST_STATIC_ASSERT_HPP
#define SST_PRIVATE_SST_STATIC_ASSERT_HPP

#include <sst/catalog/SST_DISPATCH.h>

#define SST_STATIC_ASSERT_3(ARGSTR, CONDITION, MESSAGE)                \
  static_assert(CONDITION, MESSAGE)

#define SST_STATIC_ASSERT_2(ARGSTR, CONDITION)                         \
  static_assert(CONDITION, ARGSTR)

#define SST_STATIC_ASSERT(...)                                         \
  SST_DISPATCH(SST_STATIC_ASSERT_, #__VA_ARGS__, __VA_ARGS__)          \
  (#__VA_ARGS__, __VA_ARGS__)

#endif // SST_PRIVATE_SST_STATIC_ASSERT_HPP
