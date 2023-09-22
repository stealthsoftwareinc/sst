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
#include <sst/private/guts/windows_addrinfo.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/windows_addrinfo.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <algorithm>
#include <cstddef>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_W32_IPPROTO_TCP.h>
#include <sst/catalog/SST_W32_IPPROTO_UDP.h>
#include <sst/catalog/SST_W32_SIZEOF_ADDRINFOA.h>
#include <sst/catalog/SST_W32_SOCK_DGRAM.h>
#include <sst/catalog/SST_W32_SOCK_STREAM.h>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/socket_protocol.hpp>
#include <sst/catalog/sst_w32_ADDRINFOA.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrap.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrapper.h>

namespace sst {
namespace guts {

windows_addrinfo::windows_addrinfo(
    void const * const info,
    sst_w32_ADDRINFOA_wrapper const & wrapper,
    bool const service_was_null)
    : base(info,
           SST_W32_SIZEOF_ADDRINFOA,
           wrapper.ai_addr,
           sst::checked_cast<std::size_t>(wrapper.ai_addrlen),
           service_was_null) {
  native_socktype_ = wrapper.ai_socktype;
  switch (native_socktype_) {
    case SST_W32_SOCK_STREAM: {
      socktype_ = sst::socket_type::stream;
    } break;
    case SST_W32_SOCK_DGRAM: {
      socktype_ = sst::socket_type::dgram;
    } break;
  }
  native_protocol_ = wrapper.ai_protocol;
  switch (native_protocol_) {
    case SST_W32_IPPROTO_TCP: {
      protocol_ = sst::socket_protocol::tcp;
    } break;
    case SST_W32_IPPROTO_UDP: {
      protocol_ = sst::socket_protocol::udp;
    } break;
  }
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
