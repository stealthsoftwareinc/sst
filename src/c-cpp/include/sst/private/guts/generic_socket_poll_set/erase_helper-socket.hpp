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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ERASE_HELPER_SOCKET_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ERASE_HELPER_SOCKET_HPP

#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/private/guts/generic_socket_poll_set.hpp>

namespace sst {
namespace guts {

template<class Socket, class Entry>
template<class Pfd>
void generic_socket_poll_set<Socket, Entry>::erase_helper(
    Socket const & socket) {
  recover_after_exception();
  SST_ASSERT((!failed_deletion_.first));
  auto const it = positions_->find(&socket);
  if (it != positions_->end()) {
    size_type const i = it->second;
    using pfds_t = std::vector<Pfd>;
    pfds_t & pfds = *static_cast<pfds_t *>(pfds_.get());
    Pfd & pfd = pfds[i];
    Entry & entry = i < entries_size_ ?
                        (*entries_)[i] :
                        (*new_entries_)[i - entries_size_];
    deletions_->emplace(i);
    failed_deletion_.first = true;
    failed_deletion_.second = i;
    positions_->erase(it);
    failed_deletion_.first = false;
    erase_pfd(&pfd);
    SST_ASSERT((!entry.deleted_));
    entry.deleted_ = true;
  }
}

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ERASE_HELPER_SOCKET_HPP
