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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_POLL_WITH_TIMEOUT_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_POLL_WITH_TIMEOUT_HPP

#include <chrono>

#include <sst/catalog/checked_cast.hpp>
#include <sst/private/guts/generic_socket_poll_set_iterator.hpp>

namespace sst {
namespace guts {

template<class Socket, class Entry>
template<class Duration>
typename generic_socket_poll_set<Socket, Entry>::size_type
generic_socket_poll_set<Socket, Entry>::poll(Duration const & timeout) {
  using ms = std::chrono::milliseconds;
  auto const n = std::chrono::duration_cast<ms>(timeout).count();
  return poll_helper(n < 0 ? -1 : sst::checked_cast<int>(n));
}

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_POLL_WITH_TIMEOUT_HPP
