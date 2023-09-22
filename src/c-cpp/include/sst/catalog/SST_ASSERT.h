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

#ifndef SST_CATALOG_SST_ASSERT_H
#define SST_CATALOG_SST_ASSERT_H

#ifdef __cplusplus
#include <sst/catalog/SST_ASSERT.hpp>
#else

//----------------------------------------------------------------------

#include <sst/catalog/SST_DEBUG.h>
#include <sst/catalog/SST_DISPATCH.h>
#include <sst/catalog/SST_MAYBE_UNUSED.h>
#include <sst/private/sst_assertion_failed.h>

//----------------------------------------------------------------------
// SST_DEBUG_ASSERT_helper
//----------------------------------------------------------------------

SST_MAYBE_UNUSED()
static void SST_DEBUG_ASSERT_helper(char const * const file,
                                    unsigned long const line,
                                    char const * const argstr,
                                    int const condition,
                                    char const * const message) {
  if (!condition) {
    sst_assertion_failed(file, line, argstr, message);
  }
}

//----------------------------------------------------------------------
// SST_DEBUG_ASSERT
//----------------------------------------------------------------------

#define SST_DEBUG_ASSERT_3(ARGSTR, CONDITION, MESSAGE)                 \
  (SST_DEBUG_ASSERT_helper(__FILE__,                                   \
                           (unsigned long)__LINE__,                    \
                           ARGSTR,                                     \
                           (CONDITION) != 0,                           \
                           MESSAGE))

#define SST_DEBUG_ASSERT_2(ARGSTR, CONDITION)                          \
  SST_DEBUG_ASSERT_3(ARGSTR, CONDITION, 0)

#define SST_DEBUG_ASSERT(...)                                          \
  SST_DISPATCH(SST_DEBUG_ASSERT_, #__VA_ARGS__, __VA_ARGS__)           \
  (#__VA_ARGS__, __VA_ARGS__)

//----------------------------------------------------------------------
// SST_NDEBUG_ASSERT
//----------------------------------------------------------------------

#define SST_NDEBUG_ASSERT(...) ((void)sizeof(__VA_ARGS__))

//----------------------------------------------------------------------
// SST_ASSERT
//----------------------------------------------------------------------

#if SST_DEBUG

#define SST_ASSERT(...)                                                \
  SST_DISPATCH(SST_DEBUG_ASSERT_, #__VA_ARGS__, __VA_ARGS__)           \
  (#__VA_ARGS__, __VA_ARGS__)

#else

#define SST_ASSERT(...) SST_NDEBUG_ASSERT(__VA_ARGS__)

#endif

//----------------------------------------------------------------------

#endif // !__cplusplus

#endif // SST_CATALOG_SST_ASSERT_H
