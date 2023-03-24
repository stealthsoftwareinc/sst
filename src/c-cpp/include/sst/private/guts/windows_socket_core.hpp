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

#ifndef SST_PRIVATE_GUTS_WINDOWS_SOCKET_CORE_HPP
#define SST_PRIVATE_GUTS_WINDOWS_SOCKET_CORE_HPP

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <cstddef>
#include <list>
#include <new>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/gai_flags.hpp>
#include <sst/catalog/socket_family.hpp>
#include <sst/catalog/socket_protocol.hpp>
#include <sst/catalog/socket_shutdown.hpp>
#include <sst/catalog/socket_type.hpp>
#include <sst/catalog/sst_w32_SOCKET.h>
#include <sst/catalog/windows_socket_library_scope.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/guts/windows_addrinfo.hpp>
#include <sst/private/guts/windows_sockaddr.hpp>

namespace sst {
namespace guts {

class SST_DLL_EXPORT windows_socket_core {

protected:

  //--------------------------------------------------------------------
  // address_t
  //--------------------------------------------------------------------

  using address_t = guts::windows_sockaddr;

  //--------------------------------------------------------------------
  // address_info_t
  //--------------------------------------------------------------------

  using address_info_t = guts::windows_addrinfo;

  //--------------------------------------------------------------------
  // native_t
  //--------------------------------------------------------------------

  using native_t = sst_w32_SOCKET;

  //--------------------------------------------------------------------
  // have_reuseport
  //--------------------------------------------------------------------

  SST_NODISCARD() static bool have_reuseport();

  //--------------------------------------------------------------------
  // native_accept-htwt5m9m
  //--------------------------------------------------------------------

  static native_t native_accept(native_t socket,
                                address_t::native_t * address,
                                std::size_t * address_size);

  //--------------------------------------------------------------------
  // native_bind-r8mjjktc
  //--------------------------------------------------------------------

  static void native_bind(native_t socket,
                          address_t::native_t const * address,
                          std::size_t address_size);

  //--------------------------------------------------------------------
  // native_blocking-ynnxvbr9
  //--------------------------------------------------------------------

  void native_blocking(native_t socket, bool value);

  //--------------------------------------------------------------------
  // native_close-tyvqcfu3
  //--------------------------------------------------------------------

  static void native_close(native_t socket);

  //--------------------------------------------------------------------
  // native_close-sksw29y8
  //--------------------------------------------------------------------

  static void native_close(native_t socket, std::nothrow_t) noexcept;

  //--------------------------------------------------------------------
  // native_connect-ikbwzko3
  //--------------------------------------------------------------------

  static bool native_connect(native_t socket,
                             address_t::native_t const * address,
                             std::size_t address_size);

  //--------------------------------------------------------------------
  // native_getsockname-bvqwz0ni
  //--------------------------------------------------------------------

  static void native_getsockname(native_t socket,
                                 address_t::native_t * address,
                                 std::size_t * address_size);

  //--------------------------------------------------------------------
  // native_getsockopt-ou6xew4e
  //--------------------------------------------------------------------

  static void native_getsockopt(native_t socket,
                                int level,
                                int option,
                                void * value,
                                std::size_t * size);

  //--------------------------------------------------------------------
  // native_listen-nx9u4w2o
  //--------------------------------------------------------------------

  static void native_listen(native_t socket, int backlog = -1);

  //--------------------------------------------------------------------
  // native_recv-t5qvr5p1
  //--------------------------------------------------------------------

  std::size_t native_recv(native_t socket,
                          void * data,
                          std::size_t size,
                          bool * eof = nullptr,
                          int flags = 0);

  //--------------------------------------------------------------------
  // native_resolve-rjk2t08u
  //--------------------------------------------------------------------

  static std::list<address_info_t>
  native_resolve(char const * const node,
                 char const * const service,
                 int const flags,
                 int const family,
                 int const socktype,
                 int const protocol);

  //--------------------------------------------------------------------
  // native_send-xmrr6bkn
  //--------------------------------------------------------------------

  std::size_t native_send(native_t socket,
                          void const * data,
                          std::size_t size,
                          int flags = 0);

  //--------------------------------------------------------------------
  // native_setsockopt-krr2jqwc
  //--------------------------------------------------------------------

  static void native_setsockopt(native_t socket,
                                int level,
                                int option,
                                void const * value,
                                std::size_t size);

  //--------------------------------------------------------------------
  // native_shutdown-cfy4dm91
  //--------------------------------------------------------------------

  static void native_shutdown(native_t socket, int how);

  //--------------------------------------------------------------------
  // native_shutdown-d2movxm6
  //--------------------------------------------------------------------

  static void
  native_shutdown(native_t socket, int how, std::nothrow_t) noexcept;

  //--------------------------------------------------------------------
  // native_so_reuseaddr
  //--------------------------------------------------------------------

  static int native_so_reuseaddr() noexcept;

  //--------------------------------------------------------------------
  // native_so_reuseport
  //--------------------------------------------------------------------

  static int native_so_reuseport();

  //--------------------------------------------------------------------
  // native_socket-zevidq9r
  //--------------------------------------------------------------------

  static native_t native_socket(int domain, int type, int protocol);

  //--------------------------------------------------------------------
  // native_sol_socket
  //--------------------------------------------------------------------

  static int native_sol_socket() noexcept;

  //--------------------------------------------------------------------
  // native_valid-hd5ritdy
  //--------------------------------------------------------------------

  static bool native_valid(native_t socket);

  //--------------------------------------------------------------------
  // to_family-sm4h6y03
  //--------------------------------------------------------------------

  static sst::socket_family to_family(int family);

  //--------------------------------------------------------------------
  // to_native-cb3efxv8
  //--------------------------------------------------------------------

  static int to_native(sst::socket_family family);

  //--------------------------------------------------------------------
  // to_native-uu75kdq2
  //--------------------------------------------------------------------

  static int to_native(sst::gai_flags flags);

  //--------------------------------------------------------------------
  // to_native-tjqb9ttr
  //--------------------------------------------------------------------

  static int to_native(sst::socket_protocol protocol);

  //--------------------------------------------------------------------
  // to_native-r5utg8tq
  //--------------------------------------------------------------------

  static int to_native(sst::socket_type socktype);

  //--------------------------------------------------------------------
  // to_native-af9e0eds
  //--------------------------------------------------------------------

  static int to_native(sst::socket_shutdown how);

  //--------------------------------------------------------------------
  // to_protocol-mjsfax6h
  //--------------------------------------------------------------------

  static sst::socket_protocol to_protocol(int protocol);

  //--------------------------------------------------------------------
  // to_socktype-iz6ukdpk
  //--------------------------------------------------------------------

  static sst::socket_type to_socktype(int socktype);

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32

#endif // #ifndef SST_PRIVATE_GUTS_WINDOWS_SOCKET_CORE_HPP
