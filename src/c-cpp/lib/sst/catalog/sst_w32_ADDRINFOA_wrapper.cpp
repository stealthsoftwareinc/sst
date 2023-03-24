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

// Include first to test independence.
#include <sst/catalog/sst_w32_ADDRINFOA_wrapper.h>
// Include twice to test idempotence.
#include <sst/catalog/sst_w32_ADDRINFOA_wrapper.h>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <type_traits>
#include <utility>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrapper.h>

#define CHECK_TYPE(x)                                                  \
  SST_STATIC_ASSERT(                                                   \
      (std::is_same<                                                   \
          decltype(std::declval<sst_w32_ADDRINFOA_wrapper>().x),       \
          decltype(std::declval<ADDRINFOA>().x)>::value))

CHECK_TYPE(ai_flags);
CHECK_TYPE(ai_family);
CHECK_TYPE(ai_socktype);
CHECK_TYPE(ai_protocol);
CHECK_TYPE(ai_addrlen);
CHECK_TYPE(ai_canonname);
CHECK_TYPE(ai_addr);
CHECK_TYPE(ai_next);

#undef CHECK_TYPE

#endif // #if SST_WITH_WINDOWS_WS2_32
