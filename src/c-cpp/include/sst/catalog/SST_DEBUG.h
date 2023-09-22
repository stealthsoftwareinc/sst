/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef SST_CATALOG_SST_DEBUG_H
#define SST_CATALOG_SST_DEBUG_H

#include <sst/catalog/SST_DEBUG_ABI.h>
#include <sst/catalog/SST_SUBSET_LIBRARY.h>
#include <sst/private/SST_DEBUG_DEFAULT.h>

/*
 * TODO: Move this documentation to the manual.
 * SST_DEBUG can be overridden and SST_DEBUG_ABI cannot. In a subset
 * library, SST_DEBUG and SST_DEBUG_ABI are the same, so overriding
 * SST_DEBUG also overrides SST_DEBUG_ABI. In a non-subset library,
 * SST_DEBUG_ABI is set at build time and cannot be changed, but
 * SST_DEBUG can still be overridden at any time.
 */

/* clang-format off */

#ifdef SST_DEBUG
  #if SST_DEBUG
    #undef SST_DEBUG
    #define SST_DEBUG (1)
  #else
    #undef SST_DEBUG
    #define SST_DEBUG (0)
  #endif
#elif SST_SUBSET_LIBRARY
  #define SST_DEBUG SST_DEBUG_DEFAULT
#else
  #define SST_DEBUG SST_DEBUG_ABI
#endif

/* clang-format on */

#endif // SST_CATALOG_SST_DEBUG_H
