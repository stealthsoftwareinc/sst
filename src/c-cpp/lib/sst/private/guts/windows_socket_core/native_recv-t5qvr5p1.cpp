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
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_W32_WSAEWOULDBLOCK.h>
#include <sst/catalog/min.hpp>
#include <sst/catalog/promote_t.hpp>
#include <sst/catalog/sst_w32_WSAGetLastError.h>
#include <sst/catalog/sst_w32_recv.h>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/wsa_exception.hpp>

namespace sst {
namespace guts {

std::size_t windows_socket_core::native_recv(native_t const socket,
                                             void * const data,
                                             std::size_t const size,
                                             bool * const eof,
                                             int const flags) {
  SST_ASSERT((native_valid(socket)));
  SST_ASSERT((data != nullptr));
  using t1 = std::common_type<std::size_t, int>::type;
  using t2 = sst::promote_t<t1>;
  t2 const n1 = static_cast<t2>(size);
  t2 const n2 = static_cast<t2>(sst::type_max<int>::value);
  t2 const n3 = static_cast<int>(sst::min(n1, n2));
  int const n4 =
      sst_w32_recv(socket, reinterpret_cast<char *>(data), n3, flags);
  if (n4 < 0) {
    int const e = sst_w32_WSAGetLastError();
    if (e == SST_W32_WSAEWOULDBLOCK) {
      if (eof != nullptr) {
        *eof = false;
      }
      return 0;
    }
    throw sst::wsa_exception("recv()", e);
  }
  if (eof != nullptr) {
    *eof = (size > 0 && n4 == 0);
  }
  return static_cast<std::size_t>(n4);
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
