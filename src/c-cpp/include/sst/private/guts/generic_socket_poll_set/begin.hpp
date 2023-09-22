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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_BEGIN_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_BEGIN_HPP

#include <sst/private/guts/generic_socket_poll_set_iterator.hpp>

namespace sst {
namespace guts {

template<class Socket, class Entry>
sst::guts::generic_socket_poll_set_iterator<Entry>
generic_socket_poll_set<Socket, Entry>::begin() const {
  return sst::guts::generic_socket_poll_set_iterator<Entry>(
      entries_.get(),
      entries_size_,
      deletions_.get(),
      failed_deletion_,
      0);
}

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_BEGIN_HPP
