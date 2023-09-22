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

#ifndef SST_PRIVATE_GUTS_ADDRINFO_COMMON_HPP
#define SST_PRIVATE_GUTS_ADDRINFO_COMMON_HPP

#include <cstddef>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/preinit.hpp>
#include <sst/catalog/socket_family.hpp>
#include <sst/catalog/socket_protocol.hpp>
#include <sst/catalog/socket_type.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace guts {

template<class Address>
class SST_DLL_EXPORT addrinfo_common {

protected:

  //--------------------------------------------------------------------
  // address_t
  //--------------------------------------------------------------------

  using address_t = Address;

  //--------------------------------------------------------------------

  explicit addrinfo_common(void const * const info,
                           std::size_t const info_size,
                           void const * const address,
                           std::size_t const address_size,
                           bool const service_was_null)
      : preinit_((SST_ASSERT((info != nullptr)),
                  SST_ASSERT((address != nullptr)),
                  0)),
        native_(info, info_size),
        native_size_(info_size),
        address_(address, address_size, service_was_null) {
  }

  //--------------------------------------------------------------------

  addrinfo_common(addrinfo_common const & other)
      : moved_from_(other.moved_from_),
        native_(other.native_.copy(other.native_size_)),
        native_size_(other.native_size_),
        native_socktype_(other.native_socktype_),
        socktype_(other.socktype_),
        native_protocol_(other.native_protocol_),
        protocol_(other.protocol_),
        address_(other.address_) {
  }

  //--------------------------------------------------------------------

  addrinfo_common & operator=(addrinfo_common const & other) {
    if (this != &other) {
      moved_from_ = other.moved_from_;
      native_ = other.native_.copy(other.native_size_);
      native_size_ = other.native_size_;
      native_socktype_ = other.native_socktype_;
      socktype_ = other.socktype_;
      native_protocol_ = other.native_protocol_;
      protocol_ = other.protocol_;
      address_ = other.address_;
    }
    return *this;
  }

  //--------------------------------------------------------------------
  //
  // This should normally use "noexcept = default", but this breaks on
  // g++ on CentOS 7 as tested on 2022-02-03. Manually implementing it
  // works.
  //

  addrinfo_common(addrinfo_common && other) noexcept
      : moved_from_(std::move(other.moved_from_)),
        native_(std::move(other.native_.copy(other.native_size_))),
        native_size_(std::move(other.native_size_)),
        native_socktype_(std::move(other.native_socktype_)),
        socktype_(std::move(other.socktype_)),
        native_protocol_(std::move(other.native_protocol_)),
        protocol_(std::move(other.protocol_)),
        address_(std::move(other.address_)) {
  }

  //--------------------------------------------------------------------
  //
  // This should normally use "noexcept = default", but this breaks on
  // g++ on CentOS 7 as tested on 2022-02-03. Manually implementing it
  // works.
  //

  addrinfo_common & operator=(addrinfo_common && other) noexcept {
    if (this != &other) {
      moved_from_ = std::move(other.moved_from_);
      native_ = std::move(other.native_.copy(other.native_size_));
      native_size_ = std::move(other.native_size_);
      native_socktype_ = std::move(other.native_socktype_);
      socktype_ = std::move(other.socktype_);
      native_protocol_ = std::move(other.native_protocol_);
      protocol_ = std::move(other.protocol_);
      address_ = std::move(other.address_);
    }
    return *this;
  }

  //--------------------------------------------------------------------
  //
  // This should normally use "noexcept = default", but this breaks on
  // g++ on CentOS 7 as tested on 2022-02-03. Manually implementing it
  // works.
  //

  ~addrinfo_common() noexcept {
  }

  //--------------------------------------------------------------------
  // address
  //--------------------------------------------------------------------

  address_t const & address() const {
    SST_ASSERT((!moved_from_));
    return address_;
  }

  //--------------------------------------------------------------------
  // family
  //--------------------------------------------------------------------

  sst::socket_family family() const {
    SST_ASSERT((!moved_from_));
    return address_.family();
  }

  //--------------------------------------------------------------------
  // native
  //--------------------------------------------------------------------

  void const * native() const {
    SST_ASSERT((!moved_from_));
    return native_.get();
  }

  //--------------------------------------------------------------------
  // native_family
  //--------------------------------------------------------------------

  int native_family() const {
    SST_ASSERT((!moved_from_));
    return address_.native_family();
  }

  //--------------------------------------------------------------------
  // native_protocol
  //--------------------------------------------------------------------

  int native_protocol() const {
    SST_ASSERT((!moved_from_));
    return native_protocol_;
  }

  //--------------------------------------------------------------------
  // native_size
  //--------------------------------------------------------------------

  std::size_t native_size() const {
    SST_ASSERT((!moved_from_));
    return native_size_;
  }

  //--------------------------------------------------------------------
  // native_socktype
  //--------------------------------------------------------------------

  int native_socktype() const {
    SST_ASSERT((!moved_from_));
    return native_socktype_;
  }

  //--------------------------------------------------------------------
  // protocol
  //--------------------------------------------------------------------

  sst::socket_protocol protocol() const {
    SST_ASSERT((!moved_from_));
    return protocol_;
  }

  //--------------------------------------------------------------------
  // socktype
  //--------------------------------------------------------------------

  sst::socket_type socktype() const {
    SST_ASSERT((!moved_from_));
    return socktype_;
  }

  //--------------------------------------------------------------------

private:

  sst::preinit preinit_{};

  //--------------------------------------------------------------------

protected:

  sst::moved_from moved_from_{};

  sst::basic_ptr<void> native_{};
  std::size_t native_size_{};

  int native_socktype_{};
  sst::socket_type socktype_ = sst::socket_type::other;

  int native_protocol_{};
  sst::socket_protocol protocol_ = sst::socket_protocol::other;

  address_t address_;

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_ADDRINFO_COMMON_HPP
