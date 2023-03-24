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

#include <list>

#include <netdb.h>
#include <sys/socket.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/make_basic.hpp>
#include <sst/catalog/posix_gai_exception.hpp>

namespace sst {
namespace guts {

std::list<posix_socket_core::address_info_t>
posix_socket_core::native_resolve(char const * const node,
                                  char const * const service,
                                  int const flags,
                                  int const family,
                                  int const socktype,
                                  int const protocol) {
  SST_ASSERT((node != nullptr || service != nullptr));
  addrinfo hints{};
  hints.ai_flags = flags;
  hints.ai_family = family;
  hints.ai_socktype = socktype;
  hints.ai_protocol = protocol;
  addrinfo * p;
  int const e = getaddrinfo(node, service, &hints, &p);
  if (e != 0) {
    throw sst::posix_gai_exception("getaddrinfo()", {e, errno});
  }
  auto const p_deleter =
      sst::make_basic(p, [](addrinfo * const p) { freeaddrinfo(p); });
  std::list<address_info_t> c;
  while (p != nullptr) {
    c.emplace_back(p, service == nullptr);
    p = p->ai_next;
  }
  return c;
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
