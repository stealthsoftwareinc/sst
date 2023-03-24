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

#ifndef SST_PRIVATE_GUTS_SOCKET_SHELL_HPP
#define SST_PRIVATE_GUTS_SOCKET_SHELL_HPP

#include <cstddef>
#include <list>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/gai_flags.hpp>
#include <sst/catalog/inet_pref.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/make_unique.hpp>
#include <sst/catalog/min.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size_max_v.hpp>
#include <sst/catalog/socket_family.hpp>
#include <sst/catalog/socket_protocol.hpp>
#include <sst/catalog/socket_shutdown.hpp>
#include <sst/catalog/socket_type.hpp>
#include <sst/catalog/to_string.hpp>

namespace sst {
namespace guts {

template<class Core>
class socket_shell : Core {

  //--------------------------------------------------------------------
  // state_t
  //--------------------------------------------------------------------

  enum class state_t {
    empty,
    created,
    bound,
    listening,
    connecting,
    connected,
    closed,
  };

  //--------------------------------------------------------------------

public:

  //--------------------------------------------------------------------
  // Inherited types
  //--------------------------------------------------------------------

  using address_info_t = typename Core::address_info_t;
  using address_t = typename Core::address_t;
  using native_t = typename Core::native_t;

  //--------------------------------------------------------------------

private:

  //--------------------------------------------------------------------
  // prune
  //--------------------------------------------------------------------
  //
  // Remove any infos that don't match the existing socket and throw an
  // exception if there's none left. A function that accepts an address
  // in a convenience form can generally use prune(resolve(...)).front()
  // to convert the address to an address_info_t.
  //

  std::list<address_info_t>
  prune(std::list<address_info_t> infos) const {
    if (state_ != state_t::empty) {
      std::remove_if(
          infos.begin(),
          infos.end(),
          [this](address_info_t const & info) {
            if (family_ != sst::socket_family::unspec) {
              if (info.native_family() != native_family_) {
                return true;
              }
            }
            if (socktype_ != sst::socket_type::unspec) {
              if (info.native_socktype() != native_socktype_) {
                return true;
              }
            }
            if (protocol_ != sst::socket_protocol::unspec) {
              if (info.native_protocol() != native_protocol_) {
                return true;
              }
            }
            return false;
          });
    }
    if (infos.size() == 0) {
      throw std::runtime_error("Network address not found.");
    }
    return infos;
  }

  //--------------------------------------------------------------------

public:

  //--------------------------------------------------------------------
  // Inherited functions
  //--------------------------------------------------------------------

  using Core::have_reuseport;
  using Core::native_accept;
  using Core::native_bind;
  using Core::native_blocking;
  using Core::native_close;
  using Core::native_connect;
  using Core::native_getsockname;
  using Core::native_getsockopt;
  using Core::native_listen;
  using Core::native_recv;
  using Core::native_resolve;
  using Core::native_send;
  using Core::native_setsockopt;
  using Core::native_shutdown;
  using Core::native_so_reuseaddr;
  using Core::native_so_reuseport;
  using Core::native_socket;
  using Core::native_sol_socket;
  using Core::native_valid;
  using Core::to_family;
  using Core::to_native;
  using Core::to_protocol;
  using Core::to_socktype;

  //--------------------------------------------------------------------
  // socket_shell-k7qkc8wp
  //--------------------------------------------------------------------

  explicit socket_shell() {
  }

  //--------------------------------------------------------------------

  socket_shell(socket_shell const &) = delete;

  //--------------------------------------------------------------------

  socket_shell & operator=(socket_shell const &) = delete;

  //--------------------------------------------------------------------
  // socket_shell-oa95dsxn
  //--------------------------------------------------------------------

  socket_shell(socket_shell && other) noexcept
      : moved_from_(std::move(other.moved_from_)),
        state_(std::move(other.state_)),
        native_(std::move(other.native_)),
        family_(std::move(other.family_)),
        native_family_(std::move(other.native_family_)),
        socktype_(std::move(other.socktype_)),
        native_socktype_(std::move(other.native_socktype_)),
        protocol_(std::move(other.protocol_)),
        native_protocol_(std::move(other.native_protocol_)),
        blocking_(std::move(other.blocking_)),
        reuseaddr_(std::move(other.reuseaddr_)),
        reuseport_(std::move(other.reuseport_)),
        shutdown_(std::move(other.shutdown_)),
        eof_(std::move(other.eof_)),
        have_local_address_(std::move(other.have_local_address_)),
        local_address_(std::move(other.local_address_)),
        have_remote_address_(std::move(other.have_remote_address_)),
        remote_address_(std::move(other.remote_address_)) {
  }

  //--------------------------------------------------------------------

  socket_shell & operator=(socket_shell && other) noexcept {
    if (this != &other) {
      if (!moved_from_ && state_ != state_t::closed) {
        close(std::nothrow);
      }
      moved_from_ = std::move(other.moved_from_);
      state_ = std::move(other.state_);
      native_ = std::move(other.native_);
      family_ = std::move(other.family_);
      native_family_ = std::move(other.native_family_);
      socktype_ = std::move(other.socktype_);
      native_socktype_ = std::move(other.native_socktype_);
      protocol_ = std::move(other.protocol_);
      native_protocol_ = std::move(other.native_protocol_);
      blocking_ = std::move(other.blocking_);
      reuseaddr_ = std::move(other.reuseaddr_);
      reuseport_ = std::move(other.reuseport_);
      shutdown_ = std::move(other.shutdown_);
      eof_ = std::move(other.eof_);
      have_local_address_ = std::move(other.have_local_address_);
      local_address_ = std::move(other.local_address_);
      have_remote_address_ = std::move(other.have_remote_address_);
      remote_address_ = std::move(other.remote_address_);
    }
    return *this;
  }

  //--------------------------------------------------------------------

  ~socket_shell() noexcept {
    destroy();
  }

  //--------------------------------------------------------------------
  // accept-jrmqwfn3
  //--------------------------------------------------------------------

  socket_shell accept() {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::listening));
      if (state_ != state_t::listening) {
        listen();
      }
      socket_shell x;
      std::size_t const n = local_address().native_size();
      sst::basic_ptr<void> const p(n);
      native_t const y = native_accept(native_, p.get(), n);
      if (native_valid(y)) {
        x.state_ = state_t::connected;
        x.native_ = y;
        x.family_ = family_;
        x.native_family_ = native_family_;
        x.socktype_ = socktype_;
        x.native_socktype_ = native_socktype_;
        x.protocol_ = protocol_;
        x.native_protocol_ = native_protocol_;
        x.local_address_.reset(new address_t(local_address(y)));
        x.have_local_address_ = true;
        x.remote_address_.reset(new address_t(p.get(), n));
        x.have_remote_address_ = true;
      }
      return x;
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // accept-kqww0nxa
  //--------------------------------------------------------------------

  socket_shell accept(address_t const & address) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::listening));
      if (state_ != state_t::listening) {
        listen(address);
      }
      return accept();
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // accept-sgrjwnuw
  //--------------------------------------------------------------------

  socket_shell accept(address_info_t const & info) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::listening));
      if (state_ != state_t::listening) {
        listen(info);
      }
      return accept();
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // accept-e3s4roiu
  //--------------------------------------------------------------------

  socket_shell accept(
      std::string const & host,
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::listening));
      SST_ASSERT((port <= 65535));
      return accept(prune(resolve(host, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // accept-tsc20w1p
  //--------------------------------------------------------------------

  socket_shell accept(
      std::string const & host,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    return accept(host, 0, pref, protocol);
  }

  //--------------------------------------------------------------------
  // accept-t1w9w54y
  //--------------------------------------------------------------------

  socket_shell accept(
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::listening));
      SST_ASSERT((port <= 65535));
      return accept(prune(resolve(true, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // bind-acsjjhs7
  //--------------------------------------------------------------------

  socket_shell & bind(address_t const & address) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT(
          (state_ == state_t::empty || state_ == state_t::created));
      create_if_necessary(address);
      native_bind(native_, address);
      state_ = state_t::bound;
      local_address_.reset(new address_t(local_address(native_)));
      have_local_address_ = true;
      return *this;
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // bind-q33cpjqf
  //--------------------------------------------------------------------

  socket_shell & bind(address_info_t const & info) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT(
          (state_ == state_t::empty || state_ == state_t::created));
      create_if_necessary(info);
      return bind(info.address());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // bind-mpdmo646
  //--------------------------------------------------------------------

  socket_shell & bind(
      std::string const & host,
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT(
          (state_ == state_t::empty || state_ == state_t::created));
      SST_ASSERT((port <= 65535));
      return bind(prune(resolve(host, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // bind-di4bhxs8
  //--------------------------------------------------------------------

  socket_shell & bind(
      std::string const & host,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    return bind(host, 0, pref, protocol);
  }

  //--------------------------------------------------------------------
  // bind-s2x6brj7
  //--------------------------------------------------------------------

  socket_shell & bind(
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT(
          (state_ == state_t::empty || state_ == state_t::created));
      SST_ASSERT((port <= 65535));
      return bind(prune(resolve(true, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // blocking-gbdxbxh0
  //--------------------------------------------------------------------
  //
  // Gets whether this socket is in blocking mode.
  //

  SST_NODISCARD() bool blocking() const {
    SST_ASSERT((!moved_from_));
    return blocking_;
  }

  //--------------------------------------------------------------------
  // blocking-ezb5ektp
  //--------------------------------------------------------------------
  //
  // Sets whether this socket is in blocking mode.
  //

  socket_shell & blocking(bool const value) {
    SST_ASSERT((!moved_from_));
    if (value != blocking_) {
      if (state_ != state_t::empty) {
        native_blocking(native_, value);
      }
      blocking_ = value;
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // close-u9xqzyte
  //--------------------------------------------------------------------

  void close() {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((state_ != state_t::closed));
    state_t const s = state_;
    state_ = state_t::closed;
    if (s != state_t::empty) {
      native_close(native_);
    }
  }

  //--------------------------------------------------------------------
  // close-q0c9gvy4
  //--------------------------------------------------------------------

  void close(std::nothrow_t) noexcept {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((state_ != state_t::closed));
    state_t const s = state_;
    state_ = state_t::closed;
    if (s != state_t::empty) {
      native_close(native_, std::nothrow);
    }
  }

  //--------------------------------------------------------------------
  // closed
  //--------------------------------------------------------------------

  bool closed() const noexcept {
    SST_ASSERT((!moved_from_));
    return state_ == state_t::closed;
  }

  //--------------------------------------------------------------------
  // connect-i9jsa9na
  //--------------------------------------------------------------------

  bool connect(address_t const & address) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::connecting));
      create_if_necessary(address);
      if (state_ != state_t::connecting) {
        remote_address_.reset(new address_t(address));
        have_remote_address_ = true;
      } else {
        SST_ASSERT((address == *remote_address_));
      }
      bool const connected = native_connect(native_,
                                            address.native(),
                                            address.native_size());
      if (connected) {
        local_address_.reset(new address_t(local_address(native_)));
        have_local_address_ = true;
        state_ = state_t::connected;
      } else {
        state_ = state_t::connecting;
      }
      return connected;
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // connect-h12g0941
  //--------------------------------------------------------------------

  bool connect() {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::connecting));
      return connect(*remote_address_);
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // connect-r9f7pcan
  //--------------------------------------------------------------------

  bool connect(address_info_t const & info) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::connecting));
      create_if_necessary(info);
      return connect(info.address());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // connect-dq20kiiq
  //--------------------------------------------------------------------

  bool connect(
      std::string const & host,
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::connecting));
      SST_ASSERT((port <= 65535));
      return connect(
          prune(resolve(host, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // connect-in6p9hwt
  //--------------------------------------------------------------------

  bool connect(
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound
                  || state_ == state_t::connecting));
      SST_ASSERT((port <= 65535));
      return connect(
          prune(resolve(false, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // default_family-trkkmx8g
  //--------------------------------------------------------------------

  static sst::socket_family default_family() {
    return sst::socket_family::inet;
  }

  //--------------------------------------------------------------------
  // default_protocol-mgn3jw2g
  //--------------------------------------------------------------------

  static sst::socket_protocol
  default_protocol(sst::socket_family const family) {
    switch (family) {
      case sst::socket_family::inet: {
        return sst::socket_protocol::tcp;
      } break;
      case sst::socket_family::inet6: {
        return sst::socket_protocol::tcp;
      } break;
      default: {
        return sst::socket_protocol::tcp;
      } break;
    }
  }

  //--------------------------------------------------------------------
  // default_socktype-kq7060td
  //--------------------------------------------------------------------

  static sst::socket_type
  default_socktype(sst::socket_family const family) {
    switch (family) {
      case sst::socket_family::inet: {
        return sst::socket_type::stream;
      } break;
      case sst::socket_family::inet6: {
        return sst::socket_type::stream;
      } break;
      default: {
        return sst::socket_type::stream;
      } break;
    }
  }

  //--------------------------------------------------------------------
  // empty-v5wc14fa
  //--------------------------------------------------------------------

  bool empty() const {
    SST_ASSERT((!moved_from_));
    return state_ == state_t::empty;
  }

  //--------------------------------------------------------------------
  // eof-oqsqrp5z
  //--------------------------------------------------------------------

  bool eof() const {
    SST_ASSERT((!moved_from_));
    return eof_;
  }

  //--------------------------------------------------------------------
  // have_local_address
  //--------------------------------------------------------------------

  bool have_local_address() const {
    SST_ASSERT((!moved_from_));
    return have_local_address_;
  }

  //--------------------------------------------------------------------
  // have_remote_address
  //--------------------------------------------------------------------

  bool have_remote_address() const {
    SST_ASSERT((!moved_from_));
    return have_remote_address_;
  }

  //--------------------------------------------------------------------
  // listen-r84fn654
  //--------------------------------------------------------------------

  socket_shell & listen() {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound));
      create_if_necessary();
      native_listen(native_);
      if (state_ != state_t::bound) {
        local_address_.reset(new address_t(local_address(native_)));
        have_local_address_ = true;
      }
      state_ = state_t::listening;
      return *this;
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // listen-o5dt9x15
  //--------------------------------------------------------------------

  socket_shell & listen(address_t const & address) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound));
      if (state_ != state_t::bound) {
        bind(address);
      }
      return listen();
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // listen-p40i7xrf
  //--------------------------------------------------------------------

  socket_shell & listen(address_info_t const & info) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound));
      if (state_ != state_t::bound) {
        bind(info);
      }
      return listen();
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // listen-h4hq6dd7
  //--------------------------------------------------------------------

  socket_shell & listen(
      std::string const & host,
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound));
      SST_ASSERT((port <= 65535));
      return listen(prune(resolve(host, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // listen-ea1swr4h
  //--------------------------------------------------------------------

  socket_shell & listen(
      std::string const & host,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    return listen(host, 0, pref, protocol);
  }

  //--------------------------------------------------------------------
  // listen-eptk4hja
  //--------------------------------------------------------------------

  socket_shell & listen(
      unsigned int const port,
      sst::inet_pref const pref = sst::inet_pref::prefer_inet,
      sst::socket_protocol const protocol = sst::socket_protocol::tcp) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty || state_ == state_t::created
                  || state_ == state_t::bound));
      SST_ASSERT((port <= 65535));
      return listen(prune(resolve(true, port, pref, protocol)).front());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // local_address-js22fg2f
  //--------------------------------------------------------------------

  static address_t local_address(native_t const socket) {
    SST_ASSERT((native_valid(socket)));
    std::size_t n = address_t::native_size_max();
    sst::basic_ptr<void> const p(n);
    native_getsockname(socket, p.get(), &n);
    return address_t(p.get(), n);
  }

  //--------------------------------------------------------------------
  // local_address-e4vqc93b
  //--------------------------------------------------------------------

  SST_NODISCARD() address_t const & local_address() const {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((have_local_address_));
    return *local_address_;
  }

  //--------------------------------------------------------------------
  // native
  //--------------------------------------------------------------------
  //
  // Gets the native handle of this socket.
  //

public:

  SST_NODISCARD() native_t native() const noexcept {
    SST_ASSERT((state_ != state_t::empty));
    SST_ASSERT((state_ != state_t::closed));
    return native_;
  }

  //--------------------------------------------------------------------
  // native_accept-fkhabndv
  //--------------------------------------------------------------------

public:

  static native_t
  native_accept(native_t const socket,
                typename address_t::native_t * const address,
                std::size_t const address_size) {
    SST_ASSERT((native_valid(socket)));
    SST_ASSERT((address != nullptr));
    std::size_t n = address_size;
    native_t const s = native_accept(socket, address, &n);
    SST_ASSERT((n == address_size));
    return s;
  }

  //--------------------------------------------------------------------
  // native_bind-kr2vmnqh
  //--------------------------------------------------------------------

  static void native_bind(native_t const socket,
                          address_t const & address) {
    native_bind(socket, address.native(), address.native_size());
  }

  //--------------------------------------------------------------------
  // native_bind-pv56234m
  //--------------------------------------------------------------------

  static void native_bind(native_t const socket,
                          address_info_t const & info) {
    native_bind(socket, info.address());
  }

  //--------------------------------------------------------------------
  // native_getsockname-m0kujv60
  //--------------------------------------------------------------------

  static void
  native_getsockname(native_t const socket,
                     typename address_t::native_t * const address,
                     std::size_t const address_size) {
    SST_ASSERT((native_valid(socket)));
    SST_ASSERT((address != nullptr));
    std::size_t n = address_size;
    native_getsockname(socket, address, &n);
    SST_ASSERT((n == address_size));
  }

  //--------------------------------------------------------------------
  // native_getsockopt_bool-ajgxs8xn
  //--------------------------------------------------------------------

  static bool native_getsockopt_bool(native_t const socket,
                                     int const level,
                                     int const option) {
    SST_ASSERT((native_valid(socket)));
    int v;
    std::size_t n = sizeof(v);
    native_getsockopt(socket, level, option, &v, &n);
    SST_ASSERT((n == sizeof(v)));
    return v != 0;
  }

  //--------------------------------------------------------------------
  // native_resolve-vekyhjn5
  //--------------------------------------------------------------------

  static std::list<address_info_t>
  native_resolve(char const * const node,
                 char const * const service,
                 sst::gai_flags const flags,
                 sst::socket_family const family,
                 sst::socket_type const socktype,
                 sst::socket_protocol const protocol) {
    return native_resolve(node,
                          service,
                          to_native(flags),
                          to_native(family),
                          to_native(socktype),
                          to_native(protocol));
  }

  //--------------------------------------------------------------------
  // native_setsockopt-ivcpr4a8
  //--------------------------------------------------------------------

  static void native_setsockopt(native_t const socket,
                                int const level,
                                int const option,
                                bool const value) {
    SST_ASSERT((native_valid(socket)));
    int const v = value ? 1 : 0;
    native_setsockopt(socket, level, option, &v, sizeof(v));
  }

  //--------------------------------------------------------------------
  // native_socket-yi9ggven
  //--------------------------------------------------------------------

  static native_t native_socket(sst::socket_family const family,
                                sst::socket_type const socktype,
                                sst::socket_protocol const protocol) {
    SST_ASSERT((family != sst::socket_family::other));
    SST_ASSERT((socktype != sst::socket_type::other));
    SST_ASSERT((protocol != sst::socket_protocol::other));
    return native_socket(to_native(family),
                         to_native(socktype),
                         to_native(protocol));
  }

  //--------------------------------------------------------------------
  // native_socket-qvooixmj
  //--------------------------------------------------------------------

  static native_t native_socket(address_info_t const & info) {
    return native_socket(info.family(),
                         info.socktype(),
                         info.protocol());
  }

  //--------------------------------------------------------------------
  // recv_exactly-adk1y5fy
  //--------------------------------------------------------------------

  template<class Size>
  socket_shell & recv_exactly(void * data, Size size) {
    SST_ASSERT((state_ != state_t::empty));
    SST_ASSERT((state_ != state_t::closed));
    SST_ASSERT((blocking_));
    SST_ASSERT((data != nullptr));
    SST_ASSERT((!sst::is_negative(size)));
    do {
      Size const k = recv_some(data, size);
      if (eof()) {
        throw std::runtime_error("Unexpected EOF on a socket.");
      }
      data = static_cast<unsigned char *>(data) + k;
      size -= k;
    } while (size > 0);
    return *this;
  }

  //--------------------------------------------------------------------
  // recv_some-xsbfyot9
  //--------------------------------------------------------------------

  template<class Size>
  SST_NODISCARD()
  Size recv_some(void * const data, Size const size) {
    SST_ASSERT((state_ != state_t::empty));
    SST_ASSERT((state_ != state_t::closed));
    SST_ASSERT((data != nullptr));
    SST_ASSERT((!sst::is_negative(size)));
    using t1 = typename std::common_type<Size, std::size_t>::type;
    using t2 = sst::promote_t<t1>;
    t2 const n1 = static_cast<t2>(size);
    t2 const n2 = static_cast<t2>(sst::size_max_v);
    t2 const n3 = static_cast<std::size_t>(sst::min(n1, n2));
    return static_cast<Size>(native_recv(native_, data, n3, &eof_));
  }

  //--------------------------------------------------------------------
  // remote_address
  //--------------------------------------------------------------------

  SST_NODISCARD() address_t const & remote_address() const {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((have_remote_address_));
    return *remote_address_;
  }

  //--------------------------------------------------------------------
  // resolve-xt248uxj
  //--------------------------------------------------------------------

  static std::list<address_info_t>
  resolve(std::string const & host,
          unsigned int const port,
          sst::inet_pref const pref = sst::inet_pref::prefer_inet,
          sst::socket_protocol protocol = sst::socket_protocol::tcp) {
    SST_ASSERT((port <= 65535));
    return inet_filter(
        native_resolve(host.c_str(),
                       sst::to_string(port).c_str(),
                       sst::gai_flags::none(),
                       (pref == sst::inet_pref::require_inet ?
                            sst::socket_family::inet :
                        pref == sst::inet_pref::require_inet6 ?
                            sst::socket_family::inet6 :
                            sst::socket_family::unspec),
                       (protocol == sst::socket_protocol::tcp ?
                            sst::socket_type::stream :
                        protocol == sst::socket_protocol::udp ?
                            sst::socket_type::dgram :
                            sst::socket_type::unspec),
                       protocol),
        pref);
  }

  //--------------------------------------------------------------------
  // resolve-ubjwwwk5
  //--------------------------------------------------------------------

  static std::list<address_info_t>
  resolve(std::string const & host,
          sst::inet_pref const pref = sst::inet_pref::prefer_inet,
          sst::socket_protocol protocol = sst::socket_protocol::tcp) {
    return inet_filter(
        native_resolve(host.c_str(),
                       nullptr,
                       sst::gai_flags::none(),
                       (pref == sst::inet_pref::require_inet ?
                            sst::socket_family::inet :
                        pref == sst::inet_pref::require_inet6 ?
                            sst::socket_family::inet6 :
                            sst::socket_family::unspec),
                       (protocol == sst::socket_protocol::tcp ?
                            sst::socket_type::stream :
                        protocol == sst::socket_protocol::udp ?
                            sst::socket_type::dgram :
                            sst::socket_type::unspec),
                       protocol),
        pref);
  }

  //--------------------------------------------------------------------
  // resolve-jbhr0wp3
  //--------------------------------------------------------------------

  static std::list<address_info_t>
  resolve(bool const passive,
          unsigned int const port,
          sst::inet_pref const pref = sst::inet_pref::prefer_inet,
          sst::socket_protocol protocol = sst::socket_protocol::tcp) {
    SST_ASSERT((port <= 65535));
    return inet_filter(
        native_resolve(nullptr,
                       sst::to_string(port).c_str(),
                       passive ? sst::gai_flags::passive() :
                                 sst::gai_flags::none(),
                       (pref == sst::inet_pref::require_inet ?
                            sst::socket_family::inet :
                        pref == sst::inet_pref::require_inet6 ?
                            sst::socket_family::inet6 :
                            sst::socket_family::unspec),
                       (protocol == sst::socket_protocol::tcp ?
                            sst::socket_type::stream :
                        protocol == sst::socket_protocol::udp ?
                            sst::socket_type::dgram :
                            sst::socket_type::unspec),
                       protocol),
        pref);
  }

  //--------------------------------------------------------------------
  // reuseaddr-c2xvzdor
  //--------------------------------------------------------------------

  SST_NODISCARD() bool reuseaddr() const {
    SST_ASSERT((!moved_from_));
    return reuseaddr_;
  }

  //--------------------------------------------------------------------
  // reuseaddr-mr4zm4ph
  //--------------------------------------------------------------------

  socket_shell & reuseaddr(bool const value) {
    SST_ASSERT((!moved_from_));
    if (value != reuseaddr_) {
      if (state_ != state_t::empty) {
        native_setsockopt(native_,
                          native_sol_socket(),
                          native_so_reuseaddr(),
                          value);
      }
      reuseaddr_ = value;
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // reuseport-yy076xah
  //--------------------------------------------------------------------

  SST_NODISCARD() bool reuseport() const {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((have_reuseport()));
    return reuseport_;
  }

  //--------------------------------------------------------------------
  // reuseport-h87tj4bw
  //--------------------------------------------------------------------

  socket_shell & reuseport(bool const value) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((have_reuseport()));
    if (value != reuseport_) {
      if (state_ != state_t::empty) {
        native_setsockopt(native_,
                          native_sol_socket(),
                          native_so_reuseport(),
                          value);
      }
      reuseport_ = value;
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // send_exactly-jpxpf3nq
  //--------------------------------------------------------------------

  template<class Size>
  socket_shell & send_exactly(void const * data, Size size) {
    SST_ASSERT((state_ != state_t::empty));
    SST_ASSERT((state_ != state_t::closed));
    SST_ASSERT((blocking_));
    SST_ASSERT((data != nullptr));
    SST_ASSERT((!sst::is_negative(size)));
    do {
      Size const k = send_some(data, size);
      data = static_cast<unsigned char const *>(data) + k;
      size -= k;
    } while (size > 0);
    return *this;
  }

  //--------------------------------------------------------------------
  // send_some-xsbfyot9
  //--------------------------------------------------------------------

  template<class Size>
  SST_NODISCARD()
  Size send_some(void const * const data, Size const size) {
    SST_ASSERT((state_ != state_t::empty));
    SST_ASSERT((state_ != state_t::closed));
    SST_ASSERT((data != nullptr));
    SST_ASSERT((!sst::is_negative(size)));
    using t1 = typename std::common_type<Size, std::size_t>::type;
    using t2 = sst::promote_t<t1>;
    t2 const n1 = static_cast<t2>(size);
    t2 const n2 = static_cast<t2>(sst::size_max_v);
    t2 const n3 = static_cast<std::size_t>(sst::min(n1, n2));
    return static_cast<Size>(native_send(native_, data, n3));
  }

  //--------------------------------------------------------------------
  // socket-d8pt8zqu
  //--------------------------------------------------------------------

  socket_shell &
  socket(int const family, int const socktype, int const protocol) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty));
      native_ = native_socket(family, socktype, protocol);
      state_ = state_t::created;
      family_ = to_family(family);
      native_family_ = family;
      socktype_ = to_socktype(socktype);
      native_socktype_ = socktype;
      protocol_ = to_protocol(protocol);
      native_protocol_ = protocol;
      if (!blocking_) {
        native_blocking(native_, blocking_);
      }
      if (reuseaddr_) {
        native_setsockopt(native_,
                          native_sol_socket(),
                          native_so_reuseaddr(),
                          reuseaddr_);
      }
      if (reuseport_) {
        native_setsockopt(native_,
                          native_sol_socket(),
                          native_so_reuseport(),
                          reuseport_);
      }
      return *this;
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // shutdown-bzfpw0g6
  //--------------------------------------------------------------------

  SST_NODISCARD() sst::socket_shutdown shutdown() const {
    SST_ASSERT((!moved_from_));
    return shutdown_;
  }

  //--------------------------------------------------------------------
  // shutdown-y1r0wh80
  //--------------------------------------------------------------------

  socket_shell & shutdown(sst::socket_shutdown const how) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ != state_t::empty));
      SST_ASSERT((state_ != state_t::closed));
      SST_ASSERT((!(how & shutdown_)));
      if (how != sst::socket_shutdown::none()) {
        native_shutdown(native_, to_native(how));
        shutdown_ |= how;
      }
      return *this;
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // socket-r0hmjtfz
  //--------------------------------------------------------------------

  socket_shell & socket(sst::socket_family const family,
                        sst::socket_type const socktype,
                        sst::socket_protocol const protocol) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty));
      SST_ASSERT((family != sst::socket_family::other));
      SST_ASSERT((socktype != sst::socket_type::other));
      SST_ASSERT((protocol != sst::socket_protocol::other));
      return socket(to_native(family),
                    to_native(socktype),
                    to_native(protocol));
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------
  // socket-kcdvki2v
  //--------------------------------------------------------------------

  socket_shell & socket(address_info_t const & info) {
    try {
      SST_ASSERT((!moved_from_));
      SST_ASSERT((state_ == state_t::empty));
      return socket(info.family(), info.socktype(), info.protocol());
    } catch (...) {
      destroy();
      throw;
    }
  }

  //--------------------------------------------------------------------

private:

  //--------------------------------------------------------------------

  void destroy() noexcept {
    if (!moved_from_) {
      if (state_ != state_t::empty && state_ != state_t::closed) {
        native_close(native_, std::nothrow);
      }
      state_ = state_t::closed;
    }
  }

  //--------------------------------------------------------------------

  void create_if_necessary() {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((state_ != state_t::closed));
    if (state_ == state_t::empty) {
      sst::socket_family const family = default_family();
      socket(family,
             default_socktype(family),
             default_protocol(family));
    }
  }

  //--------------------------------------------------------------------

  void create_if_necessary(address_t const & address) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((state_ != state_t::closed));
    if (state_ == state_t::empty) {
      socket(address.native_family(),
             to_native(default_socktype(address.family())),
             to_native(default_protocol(address.family())));
    } else {
      if (family_ != sst::socket_family::unspec) {
        SST_ASSERT((address.native_family() == native_family_));
      }
    }
  }

  //--------------------------------------------------------------------

  void create_if_necessary(address_info_t const & info) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((state_ != state_t::closed));
    if (state_ == state_t::empty) {
      socket(info);
    } else {
      if (family_ != sst::socket_family::unspec) {
        SST_ASSERT((info.native_family() == native_family_));
      }
      if (socktype_ != sst::socket_type::unspec) {
        SST_ASSERT((info.native_socktype() == native_socktype_));
      }
      if (protocol_ != sst::socket_protocol::unspec) {
        SST_ASSERT((info.native_protocol() == native_protocol_));
      }
    }
  }

  //--------------------------------------------------------------------

  static std::list<address_info_t>
  inet_filter(std::list<address_info_t> infos,
              sst::inet_pref const pref) {
    using info = address_info_t;
    sst::socket_family constexpr inet = sst::socket_family::inet;
    sst::socket_family constexpr inet6 = sst::socket_family::inet6;
    if (pref == sst::inet_pref::require_inet) {
      std::remove_if(infos.begin(), infos.end(), [](info const & a) {
        return a.family() != inet;
      });
    } else if (pref == sst::inet_pref::require_inet6) {
      std::remove_if(infos.begin(), infos.end(), [](info const & a) {
        return a.family() != inet6;
      });
    } else {
      std::remove_if(infos.begin(), infos.end(), [](info const & a) {
        return a.family() != inet && a.family() != inet6;
      });
      if (pref == sst::inet_pref::prefer_inet) {
        infos.sort([](info const & a, info const & b) {
          return a.family() == inet && b.family() == inet6;
        });
      } else if (pref == sst::inet_pref::prefer_inet6) {
        infos.sort([](info const & a, info const & b) {
          return a.family() == inet6 && b.family() == inet;
        });
      }
    }
    return infos;
  }

  //--------------------------------------------------------------------

  sst::moved_from moved_from_{};

  state_t state_ = state_t::empty;

  native_t native_{};

  sst::socket_family family_{};
  int native_family_{};

  sst::socket_type socktype_{};
  int native_socktype_{};

  sst::socket_protocol protocol_{};
  int native_protocol_{};

  bool blocking_ = true;

  bool reuseaddr_ = false;
  bool reuseport_ = false;

  sst::socket_shutdown shutdown_ = sst::socket_shutdown::none();

  bool eof_ = false;

  bool have_local_address_ = false;
  std::unique_ptr<address_t> local_address_{};

  bool have_remote_address_ = false;
  std::unique_ptr<address_t> remote_address_{};

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // #ifndef SST_PRIVATE_GUTS_SOCKET_SHELL_HPP
