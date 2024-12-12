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

#include <list>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_W32_SIZEOF_ADDRINFOA.h>
#include <sst/catalog/make_basic.hpp>
#include <sst/catalog/sst_w32_ADDRINFOA.h>
#include <sst/catalog/sst_w32_ADDRINFOA_unwrap.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrap.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrapper.h>
#include <sst/catalog/sst_w32_freeaddrinfo.h>
#include <sst/catalog/sst_w32_getaddrinfo.h>
#include <sst/catalog/windows_gai_exception.hpp>

namespace sst {
namespace guts {

std::list<windows_socket_core::address_info_t>
windows_socket_core::native_resolve(char const * const node,
                                    char const * const service,
                                    int const flags,
                                    int const family,
                                    int const socktype,
                                    int const protocol) {
  SST_ASSERT((node != nullptr || service != nullptr));
  auto const hints =
      sst::make_basic<sst_w32_ADDRINFOA>(SST_W32_SIZEOF_ADDRINFOA);
  sst_w32_ADDRINFOA_wrapper w{};
  w.ai_flags = flags;
  w.ai_family = family;
  w.ai_socktype = socktype;
  w.ai_protocol = protocol;
  sst_w32_ADDRINFOA_unwrap(&w, hints.get());
  sst_w32_ADDRINFOA * p;
  auto const e = sst_w32_getaddrinfo(node, service, hints.get(), &p);
  if (e != 0) {
    throw sst::windows_gai_exception("getaddrinfo()", e);
  }
  auto const p_deleter =
      sst::make_basic(p, [](sst_w32_ADDRINFOA * const p) {
        sst_w32_freeaddrinfo(p);
      });
  std::list<address_info_t> c;
  while (p != nullptr) {
    c.emplace_back(p, service == nullptr);
    sst_w32_ADDRINFOA_wrap(p, &w);
    p = w.ai_next;
  }
  return c;
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
