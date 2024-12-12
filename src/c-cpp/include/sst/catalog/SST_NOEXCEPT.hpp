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

#ifndef SST_CATALOG_SST_NOEXCEPT_HPP
#define SST_CATALOG_SST_NOEXCEPT_HPP

//
// TODO: Move this documentation into the manual.
//
// SST_NOEXCEPT is a wrapper for the noexcept specifier that can be
// enabled or disabled at configure time using --with-noexcept or
// --without-noexcept.
//
// SST_NOEXCEPT is useful because it's not uncommon for compilers to
// have bugs related to the noexcept specifier, and simply removing all
// noexcept specifiers generally lets the code compile without affecting
// correctness.
//
// By default, if neither --with-noexcept nor --without-noexcept is
// specified at configure time, SST_NOEXCEPT is enabled except for
// specific compiler versions that have been observed to be buggy.
//
// Note that SST_NOEXCEPT should only be used to replace the noexcept
// specifier, not the noexcept operator. For replacing the noexcept
// operator, see SST_NOEXCEPT_OR.
//

#include <sst/catalog/SST_WITH_NOEXCEPT.h>

#if SST_WITH_NOEXCEPT
#define SST_NOEXCEPT(...) noexcept(__VA_ARGS__)
#else
#define SST_NOEXCEPT(...)
#endif

#endif // SST_CATALOG_SST_NOEXCEPT_HPP
