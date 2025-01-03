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

// Include first to test independence.
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrapper.h>
// Include twice to test idempotence.
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrapper.h>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <type_traits>
#include <utility>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrapper.h>

#define CHECK_TYPE(x)                                                  \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<                                                   \
          decltype(std::declval<sst_w32_SOCKADDR_IN6_wrapper>().x),    \
          decltype(std::declval<SOCKADDR_IN6>().x)>::value))

// sin6_family is supposed to be unsigned but it's commonly declared as
// signed in unofficial versions of the Windows API headers.
SST_STATIC_ASSERT(
    (std::is_same<decltype(std::declval<sst_w32_SOCKADDR_IN6_wrapper>()
                               .sin6_family),
                  typename std::make_unsigned<
                      decltype(std::declval<SOCKADDR_IN6>()
                                   .sin6_family)>::type>::value));

CHECK_TYPE(sin6_port);
CHECK_TYPE(sin6_flowinfo);
CHECK_TYPE(sin6_scope_id);

#undef CHECK_TYPE

#endif // #if SST_WITH_WINDOWS_WS2_32
