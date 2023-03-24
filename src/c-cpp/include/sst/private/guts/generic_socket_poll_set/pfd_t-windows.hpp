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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_PFD_T_WINDOWS_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_PFD_T_WINDOWS_HPP

#include <sst/catalog/SST_WITH_WINDOWS_WS2_32.h>

#if SST_WITH_WINDOWS_WS2_32

#include <array>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/SST_W32_SIZEOF_WSAPOLLFD.h>

namespace {

using pfd_t = std::array<unsigned char, SST_W32_SIZEOF_WSAPOLLFD>;

SST_STATIC_ASSERT((sizeof(pfd_t) == SST_W32_SIZEOF_WSAPOLLFD));

} // namespace

#endif // #if SST_WITH_WINDOWS_WS2_32

#endif // #ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_PFD_T_WINDOWS_HPP
