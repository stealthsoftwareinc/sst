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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_CONSOLIDATE_HELPER_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_CONSOLIDATE_HELPER_HPP

#include <vector>

namespace sst {
namespace guts {

template<class Socket, class Entry>
template<class Pfd>
void generic_socket_poll_set<Socket, Entry>::consolidate_helper() {

  recover_after_exception();

  using pfds_t = std::vector<Pfd>;
  if (pfds_ == nullptr) {
    pfds_ = new pfds_t;
  }
  pfds_t & pfds = *static_cast<pfds_t *>(pfds_.get());

  if (entries_ == nullptr) {
    using element = typename decltype(entries_)::element_type;
    entries_.reset(new element);
  }

  if (new_entries_ == nullptr) {
    using element = typename decltype(new_entries_)::element_type;
    new_entries_.reset(new element);
  }

  if (deletions_ == nullptr) {
    using element = typename decltype(deletions_)::element_type;
    deletions_.reset(new element);
  }

  entries_->insert(entries_->end(),
                   new_entries_->cbegin(),
                   new_entries_->cend());

  new_entries_->clear();

  entries_size_ = pfds_size_;
  new_entries_size_ = 0;

  SST_ASSERT((deletions_ != nullptr));
  SST_ASSERT((!failed_deletion_.first));
  SST_ASSERT((entries_size_ == pfds_size_));
  SST_ASSERT((new_entries_size_ == 0));
  for (auto it = deletions_->begin(); it != deletions_->end();) {
    size_type const i = *it;
    Pfd & dst_pfd = pfds[i];
    Entry & dst_entry = (*entries_)[i];
    Pfd const & src_pfd = pfds[pfds_size_ - 1];
    Entry const & src_entry = (*entries_)[pfds_size_ - 1];
    it = deletions_->erase(it);
    if (i < pfds_size_ - 1) {
      dst_pfd = src_pfd;
      dst_entry = src_entry;
    }
    --pfds_size_;
    --entries_size_;
    pfds.pop_back();
    entries_->pop_back();
  }

} //

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_CONSOLIDATE_HELPER_HPP
