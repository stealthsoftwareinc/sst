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
#include <sst/private/guts/generic_socket_poll_set_entry.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/generic_socket_poll_set_entry.hpp>
//

#include <sst/catalog/SST_WITH_WINDOWS_WS2_32.h>

#if SST_WITH_WINDOWS_WS2_32

#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_W32_POLLRDNORM.h>
#include <sst/catalog/sst_w32_WSAPOLLFD.h>
#include <sst/catalog/sst_w32_WSAPOLLFD_wrap.h>
#include <sst/catalog/sst_w32_WSAPOLLFD_wrapper.h>
#include <sst/catalog/windows_socket.hpp>
#include <sst/private/guts/generic_socket_poll_set/pfd_t-windows.hpp>

namespace sst {
namespace guts {

template<>
bool generic_socket_poll_set_entry<sst::windows_socket>::can_recv()
    const {
  SST_ASSERT((!deleted_));
  using pfds_t = std::vector<pfd_t>;
  pfds_t const & pfds = *static_cast<pfds_t const *>(pfds_);
  pfd_t const & pfd = pfds[position_];
  sst_w32_WSAPOLLFD_wrapper w{};
  sst_w32_WSAPOLLFD_wrap(
      reinterpret_cast<sst_w32_WSAPOLLFD const *>(&pfd),
      &w);
  return static_cast<bool>(w.revents & SST_W32_POLLRDNORM);
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
