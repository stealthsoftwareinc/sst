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
#include <sst/private/guts/windows_sockaddr.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/windows_sockaddr.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <stddef.h>

#include <algorithm>
#include <cstddef>

#include <sst/catalog/SST_W32_AF_INET.h>
#include <sst/catalog/SST_W32_AF_INET6.h>
#include <sst/catalog/SST_W32_INET6_ADDRSTRLEN.h>
#include <sst/catalog/SST_W32_INET_ADDRSTRLEN.h>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/sst_w32_SOCKADDR_IN.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN6.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrap.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN6_wrapper.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN_wrap.h>
#include <sst/catalog/sst_w32_SOCKADDR_IN_wrapper.h>
#include <sst/catalog/sst_w32_inet_ntop.h>
#include <sst/catalog/sst_w32_ntohs.h>
#include <sst/catalog/wsa_exception.hpp>

namespace sst {
namespace guts {

windows_sockaddr::windows_sockaddr(void const * const address,
                                   std::size_t const address_size,
                                   bool const service_was_null)
    : base(address, address_size, native_family(address)) {

  switch (native_family()) {

      //----------------------------------------------------------------

    case SST_W32_AF_INET: {

      sst_w32_SOCKADDR_IN_wrapper addr;
      sst_w32_SOCKADDR_IN_wrap(
          reinterpret_cast<sst_w32_SOCKADDR_IN const *>(native_.get()),
          &addr);

      family_ = sst::socket_family::inet;

      sst::checked_resize(ip_, SST_W32_INET_ADDRSTRLEN);
      if (sst_w32_inet_ntop(addr.sin_family,
                            &addr.sin_addr,
                            &ip_[0],
                            sst::checked_cast<size_t>(ip_.size()))
          == nullptr) {
        throw sst::wsa_exception();
      }
      ip_.erase(std::find(ip_.begin(), ip_.end(), '\0'), ip_.end());
      have_ip_ = true;

      // If this address came from a getaddrinfo call in which the
      // service parameter was null, it may be unsafe to read the port.
      if (!service_was_null) {
        port_ = sst_w32_ntohs(addr.sin_port);
        have_port_ = true;
      }

    } break;

      //----------------------------------------------------------------

    case SST_W32_AF_INET6: {

      sst_w32_SOCKADDR_IN6_wrapper addr;
      sst_w32_SOCKADDR_IN6_wrap(
          reinterpret_cast<sst_w32_SOCKADDR_IN6 const *>(native_.get()),
          &addr);

      family_ = sst::socket_family::inet6;

      sst::checked_resize(ip_, SST_W32_INET6_ADDRSTRLEN);
      if (sst_w32_inet_ntop(addr.sin6_family,
                            &addr.sin6_addr,
                            &ip_[0],
                            sst::checked_cast<size_t>(ip_.size()))
          == nullptr) {
        throw sst::wsa_exception();
      }
      ip_.erase(std::find(ip_.begin(), ip_.end(), '\0'), ip_.end());
      have_ip_ = true;

      // If this address came from a getaddrinfo call in which the
      // service parameter was null, it may be unsafe to read the port.
      if (!service_was_null) {
        port_ = sst_w32_ntohs(addr.sin6_port);
        have_port_ = true;
      }

    } break;

      //----------------------------------------------------------------
  }
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
