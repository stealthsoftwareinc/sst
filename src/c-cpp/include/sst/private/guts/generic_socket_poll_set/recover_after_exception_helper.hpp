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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_RECOVER_AFTER_EXCEPTION_HELPER_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_RECOVER_AFTER_EXCEPTION_HELPER_HPP

#include <iterator>
#include <vector>

#include <sst/catalog/unsigned_gt.hpp>

namespace sst {
namespace guts {

template<class Socket, class Entry>
template<class Pfd>
void generic_socket_poll_set<Socket,
                             Entry>::recover_after_exception_helper() {

  if (pfds_ != nullptr) {
    using pfds_t = std::vector<Pfd>;
    pfds_t & pfds = *static_cast<pfds_t *>(pfds_.get());
    if (sst::unsigned_gt(pfds.size(), pfds_size_)) {
      auto it = pfds.begin();
      std::advance(it, pfds_size_);
      pfds.erase(it, pfds.end());
    }
  }

  if (entries_ != nullptr) {
    if (sst::unsigned_gt(entries_->size(), entries_size_)) {
      auto it = entries_->begin();
      std::advance(it, entries_size_);
      entries_->erase(it, entries_->end());
    }
  }

  if (new_entries_ != nullptr) {
    if (sst::unsigned_gt(new_entries_->size(), new_entries_size_)) {
      auto it = new_entries_->begin();
      std::advance(it, new_entries_size_);
      new_entries_->erase(it, new_entries_->end());
    }
  }

  if (failed_deletion_.first) {
    deletions_->erase(failed_deletion_.second);
    failed_deletion_.first = false;
  }

} //

} // namespace guts
} // namespace sst

#endif // #ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_RECOVER_AFTER_EXCEPTION_HELPER_HPP
