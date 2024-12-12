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

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_W32_FIONBIO.h>
#include <sst/catalog/sst_w32_ioctlsocket.h>
#include <sst/catalog/sst_w32_u_long.h>
#include <sst/catalog/wsa_exception.hpp>

namespace sst {
namespace guts {

void windows_socket_core::native_blocking(native_t const socket,
                                          bool const value) {
  SST_ASSERT((native_valid(socket)));
  sst_w32_u_long v = value ? 0 : 1;
  if (sst_w32_ioctlsocket(socket,
                          static_cast<long>(SST_W32_FIONBIO),
                          &v)
      != 0) {
    throw sst::wsa_exception("ioctlsocket()");
  }
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
