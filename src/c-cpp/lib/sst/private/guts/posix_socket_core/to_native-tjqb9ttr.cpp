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

#include <cstdlib>

#include <netinet/in.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/socket_protocol.hpp>

namespace sst {
namespace guts {

int posix_socket_core::to_native(sst::socket_protocol const protocol) {
  switch (protocol) {
    case sst::socket_protocol::unspec: {
      return 0;
    } break;
    case sst::socket_protocol::tcp: {
      return IPPROTO_TCP;
    } break;
    case sst::socket_protocol::udp: {
      return IPPROTO_UDP;
    } break;
    default: {
      SST_ASSERT((protocol != sst::socket_protocol::other));
      SST_ASSERT((!"Missing case."));
      std::abort();
    } break;
  }
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
