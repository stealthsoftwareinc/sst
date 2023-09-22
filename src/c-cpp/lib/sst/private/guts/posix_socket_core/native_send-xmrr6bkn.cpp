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
#include <sst/private/guts/posix_socket_core.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/posix_socket_core.hpp>
//

#include <sst/config.h>

#if SST_WITH_POSIX

#include <errno.h>

#include <cstddef>
#include <type_traits>

#include <sys/socket.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/errno_exception.hpp>
#include <sst/catalog/min.hpp>
#include <sst/catalog/promote_t.hpp>
#include <sst/catalog/type_max.hpp>

namespace sst {
namespace guts {

std::size_t posix_socket_core::native_send(native_t const socket,
                                           void const * const data,
                                           std::size_t const size,
                                           int const flags) {
  SST_ASSERT((native_valid(socket)));
  SST_ASSERT((data != nullptr));
  using t1 = std::common_type<std::size_t, ssize_t>::type;
  using t2 = sst::promote_t<t1>;
  t2 const n1 = static_cast<t2>(size);
  t2 const n2 = static_cast<t2>(sst::type_max<ssize_t>::value);
  t2 const n3 = static_cast<std::size_t>(sst::min(n1, n2));
  ssize_t const n4 = send(socket, data, n3, flags);
  if (n4 < 0) {
    int const e = errno;
    if (e == EAGAIN || e == EWOULDBLOCK || e == EINTR) {
      return 0;
    }
    throw sst::errno_exception("send()", e);
  }
  return static_cast<std::size_t>(n4);
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
