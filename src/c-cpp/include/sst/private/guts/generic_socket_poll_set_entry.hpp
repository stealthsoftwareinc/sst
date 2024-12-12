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

#ifndef SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ENTRY_HPP
#define SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ENTRY_HPP

#include <cstddef>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_WITH_POSIX.h>
#include <sst/catalog/SST_WITH_WINDOWS_WS2_32.h>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/posix_socket.hpp>
#include <sst/catalog/windows_socket.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace guts {

template<class, class>
class generic_socket_poll_set;

template<class Socket>
class generic_socket_poll_set_entry final {

  template<class, class>
  friend class generic_socket_poll_set;

  //--------------------------------------------------------------------
  // can_recv
  //--------------------------------------------------------------------

public:

  bool can_recv() const;

  //--------------------------------------------------------------------
  // can_send
  //--------------------------------------------------------------------

public:

  bool can_send() const;

  //--------------------------------------------------------------------
  // construct
  //--------------------------------------------------------------------

public:

  template<class Position>
  explicit generic_socket_poll_set_entry(void * const pfds,
                                         Position const position,
                                         Socket & socket)
      : pfds_(pfds),
        position_(sst::checked_cast<decltype(position_)>(position)),
        socket_(&socket) {
    SST_ASSERT((pfds != nullptr));
  }

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_entry &
  operator=(generic_socket_poll_set_entry const & other) noexcept {
    deleted_ = other.deleted_;
    pfds_ = other.pfds_;
    position_ = other.position_;
    socket_ = other.socket_;
    return *this;
  }

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_entry(
      generic_socket_poll_set_entry const & other) noexcept
      : deleted_(other.deleted_),
        pfds_(other.pfds_),
        position_(other.position_),
        socket_(other.socket_) {
  }

  //--------------------------------------------------------------------
  // deleted_
  //--------------------------------------------------------------------
  //
  // Indicates whether this entry has been marked for deletion in the
  // associated poll set.
  //

private:

  mutable bool deleted_ = false;

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~generic_socket_poll_set_entry() noexcept {
  }

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_entry &
  operator=(generic_socket_poll_set_entry && other) noexcept {
    deleted_ = other.deleted_;
    pfds_ = other.pfds_;
    position_ = other.position_;
    socket_ = other.socket_;
    return *this;
  }

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

public:

  generic_socket_poll_set_entry(
      generic_socket_poll_set_entry && other) noexcept
      : deleted_(other.deleted_),
        pfds_(other.pfds_),
        position_(other.position_),
        socket_(other.socket_) {
  }

  //--------------------------------------------------------------------
  // pfds_
  //--------------------------------------------------------------------
  //
  // The associated poll set's pfds vector.
  //
  // We use a void pointer to help prevent this header file from
  // requiring any system headers, which helps reduce compilation
  // difficulties. In the implementation files, we'll convert the
  // pointer to the proper type as needed.
  //

private:

  void * pfds_;

  //--------------------------------------------------------------------
  // position_
  //--------------------------------------------------------------------
  //
  // The position of this entry in the associated pfds vector.
  //

private:

  std::size_t position_;

  //--------------------------------------------------------------------
  // socket
  //--------------------------------------------------------------------

public:

  Socket & socket() const noexcept;

  //--------------------------------------------------------------------
  // socket_
  //--------------------------------------------------------------------

private:

  Socket * socket_;

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------
// can_recv-posix
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
bool generic_socket_poll_set_entry<sst::posix_socket>::can_recv() const;

#endif

//----------------------------------------------------------------------
// can_recv-windows
//----------------------------------------------------------------------

#if SST_WITH_WINDOWS_WS2_32

template<>
bool generic_socket_poll_set_entry<sst::windows_socket>::can_recv()
    const;

#endif

//----------------------------------------------------------------------
// can_send-posix
//----------------------------------------------------------------------

#if SST_WITH_POSIX

template<>
bool generic_socket_poll_set_entry<sst::posix_socket>::can_send() const;

#endif

//----------------------------------------------------------------------
// can_send-windows
//----------------------------------------------------------------------

#if SST_WITH_WINDOWS_WS2_32

template<>
bool generic_socket_poll_set_entry<sst::windows_socket>::can_send()
    const;

#endif

//----------------------------------------------------------------------

} // namespace guts
} // namespace sst

//----------------------------------------------------------------------

#include <sst/private/guts/generic_socket_poll_set_entry/socket.hpp>

//----------------------------------------------------------------------

#endif // SST_PRIVATE_GUTS_GENERIC_SOCKET_POLL_SET_ENTRY_HPP
