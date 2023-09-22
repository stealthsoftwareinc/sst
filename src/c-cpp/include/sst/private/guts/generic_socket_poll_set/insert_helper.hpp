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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_INSERT_HELPER_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_INSERT_HELPER_HPP

#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked.hpp>
#include <sst/catalog/to_unsigned.hpp>

namespace sst {
namespace guts {

template<class Socket, class Entry>
template<class Pfd>
void generic_socket_poll_set<Socket, Entry>::insert_helper(
    Socket & socket) {

  SST_ASSERT((!socket.empty()));
  SST_ASSERT((!socket.closed()));

  recover_after_exception();

  if (positions_ != nullptr) {
    auto const it = positions_->find(&socket);
    if (it != positions_->end()) {
      return;
    }
  }

  using pfds_t = std::vector<Pfd>;
  if (pfds_ == nullptr) {
    pfds_ = new pfds_t;
  }
  pfds_t & pfds = *static_cast<pfds_t *>(pfds_.get());

  if (new_entries_ == nullptr) {
    using element = typename decltype(new_entries_)::element_type;
    new_entries_.reset(new element);
  }

  if (positions_ == nullptr) {
    using element = typename decltype(positions_)::element_type;
    positions_.reset(new element);
  }

  pfds.emplace_back();
  initialize_pfd(&pfds.back(), socket);

  new_entries_->emplace_back(&pfds, pfds_size_, socket);

  auto const next_pfds_size_ = sst::checked_cast<decltype(pfds_size_)>(
      sst::checked(sst::to_unsigned(pfds_size_)) + 1U);

  auto const next_new_entries_size_ =
      sst::checked_cast<decltype(new_entries_size_)>(
          sst::checked(sst::to_unsigned(new_entries_size_)) + 1U);

  positions_->emplace(&socket, pfds_size_);

  pfds_size_ = next_pfds_size_;
  new_entries_size_ = next_new_entries_size_;

} //

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_INSERT_HELPER_HPP
