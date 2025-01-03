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
#include <sst/private/guts/posix_sockaddr.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/posix_sockaddr.hpp>
//

#include <sst/config.h>

#if SST_WITH_POSIX

#include <algorithm>
#include <cstddef>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/errno_exception.hpp>
#include <sst/catalog/socket_family.hpp>

namespace sst {
namespace guts {

posix_sockaddr::posix_sockaddr(void const * const address,
                               std::size_t const address_size,
                               bool const service_was_null)
    : base(address, address_size, native_family(address)) {

  switch (native_family()) {

      //----------------------------------------------------------------

    case AF_INET: {

      auto const & addr =
          *reinterpret_cast<sockaddr_in const *>(native_.get());

      family_ = sst::socket_family::inet;

      sst::checked_resize(ip_, INET_ADDRSTRLEN);
      if (inet_ntop(addr.sin_family,
                    &addr.sin_addr,
                    &ip_[0],
                    sst::checked_cast<socklen_t>(ip_.size()))
          == nullptr) {
        throw sst::errno_exception();
      }
      ip_.erase(std::find(ip_.begin(), ip_.end(), '\0'), ip_.end());
      have_ip_ = true;

      // If this address came from a getaddrinfo call in which the
      // service parameter was null, it may be unsafe to read the port.
      if (!service_was_null) {
        port_ = ntohs(addr.sin_port);
        have_port_ = true;
      }

    } break;

      //----------------------------------------------------------------

    case AF_INET6: {

      auto const & addr =
          *reinterpret_cast<sockaddr_in6 const *>(native_.get());

      family_ = sst::socket_family::inet6;

      sst::checked_resize(ip_, INET6_ADDRSTRLEN);
      if (inet_ntop(addr.sin6_family,
                    &addr.sin6_addr,
                    &ip_[0],
                    sst::checked_cast<socklen_t>(ip_.size()))
          == nullptr) {
        throw sst::errno_exception();
      }
      ip_.erase(std::find(ip_.begin(), ip_.end(), '\0'), ip_.end());
      have_ip_ = true;

      // If this address came from a getaddrinfo call in which the
      // service parameter was null, it may be unsafe to read the port.
      if (!service_was_null) {
        port_ = ntohs(addr.sin6_port);
        have_port_ = true;
      }

    } break;

      //----------------------------------------------------------------
  }
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
