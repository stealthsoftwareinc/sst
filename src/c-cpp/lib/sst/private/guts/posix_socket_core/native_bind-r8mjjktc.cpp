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

#include <cstddef>

#include <sys/socket.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/errno_exception.hpp>

namespace sst {
namespace guts {

void posix_socket_core::native_bind(
    native_t const socket,
    address_t::native_t const * const address,
    std::size_t const address_size) {
  SST_ASSERT((native_valid(socket)));
  SST_ASSERT((address != nullptr));
  SST_ASSERT((address_size > 0));
  if (bind(socket,
           static_cast<struct sockaddr const *>(address),
           sst::checked_cast<socklen_t>(address_size))
      != 0) {
    throw sst::errno_exception("bind()");
  }
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
