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
#include <sst/private/guts/windows_socket_core.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/windows_socket_core.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <cstddef>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_W32_WSAEWOULDBLOCK.h>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/sst_w32_SOCKADDR.h>
#include <sst/catalog/sst_w32_WSAGetLastError.h>
#include <sst/catalog/sst_w32_accept.h>
#include <sst/catalog/wsa_exception.hpp>

namespace sst {
namespace guts {

windows_socket_core::native_t
windows_socket_core::native_accept(native_t const socket,
                                   address_t::native_t * const address,
                                   std::size_t * const address_size) {
  SST_ASSERT((native_valid(socket)));
  SST_ASSERT((address == nullptr || address_size != nullptr));
  int nn;
  int * const n = address != nullptr ? &nn : nullptr;
  if (n != nullptr) {
    *n = sst::checked_cast<int>(*address_size);
  }
  native_t const s =
      sst_w32_accept(socket,
                     static_cast<sst_w32_SOCKADDR *>(address),
                     n);
  if (native_valid(s)) {
    if (n != nullptr) {
      *address_size = sst::checked_cast<std::size_t>(*n);
    }
    return s;
  }
  int const e = sst_w32_WSAGetLastError();
  if (e == SST_W32_WSAEWOULDBLOCK) {
    return s;
  }
  throw sst::wsa_exception("accept()", e);
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
