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

#ifndef SST_PRIVATE_GUTS_SOCKADDR_COMMON_HPP
#define SST_PRIVATE_GUTS_SOCKADDR_COMMON_HPP

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/preinit.hpp>
#include <sst/catalog/socket_family.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace guts {

class SST_DLL_EXPORT sockaddr_common {

protected:

  //--------------------------------------------------------------------

  explicit sockaddr_common(void const * const address,
                           std::size_t const address_size,
                           int const address_family)
      : preinit_((SST_ASSERT((address != nullptr)), 0)),
        native_(address, address_size),
        native_size_(address_size),
        native_family_(address_family) {
  }

  //--------------------------------------------------------------------

  sockaddr_common(sockaddr_common const & other)
      : moved_from_(other.moved_from_),
        native_(other.native_.copy(other.native_size_)),
        native_size_(other.native_size_),
        native_family_(other.native_family_),
        family_(other.family_),
        have_ip_(other.have_ip_),
        ip_(other.ip_),
        have_port_(other.have_port_),
        port_(other.port_) {
  }

  //--------------------------------------------------------------------

  sockaddr_common & operator=(sockaddr_common const & other) {
    if (this != &other) {
      moved_from_ = other.moved_from_;
      native_ = other.native_.copy(other.native_size_);
      native_size_ = other.native_size_;
      native_family_ = other.native_family_;
      family_ = other.family_;
      have_ip_ = other.have_ip_;
      ip_ = other.ip_;
      have_port_ = other.have_port_;
      port_ = other.port_;
    }
    return *this;
  }

  //--------------------------------------------------------------------

  sockaddr_common(sockaddr_common &&) SST_NOEXCEPT(true) = default;

  sockaddr_common & operator=(sockaddr_common &&)
      SST_NOEXCEPT(true) = default;

  ~sockaddr_common() SST_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // family
  //--------------------------------------------------------------------

  sst::socket_family family() const {
    SST_ASSERT((!moved_from_));
    return family_;
  }

  //--------------------------------------------------------------------
  // have_ip
  //--------------------------------------------------------------------

  bool have_ip() const {
    SST_ASSERT((!moved_from_));
    return have_ip_;
  }

  //--------------------------------------------------------------------
  // have_port
  //--------------------------------------------------------------------

  bool have_port() const {
    SST_ASSERT((!moved_from_));
    return have_port_;
  }

  //--------------------------------------------------------------------
  // ip
  //--------------------------------------------------------------------

  std::string const & ip() const {
    SST_ASSERT((!moved_from_));
    return ip_;
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
    return native_family_;
  }

  //--------------------------------------------------------------------
  // native_size
  //--------------------------------------------------------------------

  std::size_t native_size() const {
    SST_ASSERT((!moved_from_));
    return native_size_;
  }

  //--------------------------------------------------------------------

  bool operator==(sockaddr_common const & other) const {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((!other.moved_from_));
    unsigned char const * const a =
        reinterpret_cast<unsigned char const *>(native_.get());
    unsigned char const * const b =
        reinterpret_cast<unsigned char const *>(other.native_.get());
    std::size_t const an = native_size_;
    std::size_t const bn = other.native_size_;
    return an == bn && std::equal(a, a + an, b);
  }

  //--------------------------------------------------------------------
  // port
  //--------------------------------------------------------------------

  unsigned int port() const {
    SST_ASSERT((!moved_from_));
    return port_;
  }

  //--------------------------------------------------------------------

private:

  sst::preinit preinit_{};

  //--------------------------------------------------------------------

protected:

  sst::moved_from moved_from_{};

  sst::basic_ptr<void> native_{};
  std::size_t native_size_{};

  int native_family_{};
  sst::socket_family family_ = sst::socket_family::other;

  bool have_ip_ = false;
  std::string ip_{};

  bool have_port_ = false;
  unsigned int port_{};

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_SOCKADDR_COMMON_HPP
