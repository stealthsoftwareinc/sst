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
#include <sst/private/guts/generic_socket_poll_set.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/generic_socket_poll_set.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <errno.h>

#include <vector>

#include <poll.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/errno_exception.hpp>
#include <sst/catalog/posix_socket.hpp>
#include <sst/catalog/posix_socket_poll_set_entry.hpp>

namespace sst {
namespace guts {

template<>
generic_socket_poll_set<sst::posix_socket,
                        sst::posix_socket_poll_set_entry>::size_type
generic_socket_poll_set<
    sst::posix_socket,
    sst::posix_socket_poll_set_entry>::poll_helper(int const timeout) {

  SST_ASSERT((timeout >= -1));

  consolidate();

  using pfds_t = std::vector<struct pollfd>;
  pfds_t & pfds = *static_cast<pfds_t *>(pfds_.get());

  if (pfds_size_ == 0) {
    return 0;
  }

  int const n = (::poll)(
      pfds.data(),
      sst::checked_cast<nfds_t>(sst::checked_cast<int>(pfds_size_)),
      timeout);

  if (n < 0) {
    int const e = errno;
    throw sst::errno_exception("poll()", e);
  }

  return static_cast<size_type>(n);

} //

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
