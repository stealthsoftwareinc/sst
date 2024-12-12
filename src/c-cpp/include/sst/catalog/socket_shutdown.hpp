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

#ifndef SST_CATALOG_SOCKET_SHUTDOWN_HPP
#define SST_CATALOG_SOCKET_SHUTDOWN_HPP

#include <sst/catalog/ones_mask.hpp>

namespace sst {

class socket_shutdown {

  using value_t = unsigned int;

  value_t value_;

  constexpr socket_shutdown(value_t const value) noexcept
      : value_(value) {
  }

  enum class exponents : value_t {
    send,
    recv,
    both,
  };

public:

  static constexpr socket_shutdown none() noexcept {
    return static_cast<value_t>(0);
  }

  static constexpr socket_shutdown send() noexcept {
    return static_cast<value_t>(1)
           << static_cast<value_t>(exponents::send);
  }

  static constexpr socket_shutdown recv() noexcept {
    return static_cast<value_t>(1)
           << static_cast<value_t>(exponents::recv);
  }

  static constexpr socket_shutdown both() noexcept {
    return sst::ones_mask<value_t>(
        static_cast<value_t>(exponents::both));
  }

  friend bool constexpr operator==(socket_shutdown const a,
                                   socket_shutdown const b) noexcept {
    return a.value_ == b.value_;
  }

  friend bool constexpr operator!=(socket_shutdown const a,
                                   socket_shutdown const b) noexcept {
    return a.value_ != b.value_;
  }

  constexpr operator bool() const noexcept {
    return *this != none();
  }

  friend socket_shutdown constexpr
  operator&(socket_shutdown const a, socket_shutdown const b) noexcept {
    return a.value_ & b.value_;
  }

  friend socket_shutdown constexpr
  operator|(socket_shutdown const a, socket_shutdown const b) noexcept {
    return a.value_ | b.value_;
  }

  friend socket_shutdown constexpr
  operator^(socket_shutdown const a, socket_shutdown const b) noexcept {
    return a.value_ ^ b.value_;
  }

  friend socket_shutdown constexpr
  operator~(socket_shutdown const a) noexcept {
    return a ^ both();
  }

  socket_shutdown & operator&=(socket_shutdown const b) noexcept {
    return *this = *this & b;
  }

  socket_shutdown & operator|=(socket_shutdown const b) noexcept {
    return *this = *this | b;
  }

  socket_shutdown & operator^=(socket_shutdown const b) noexcept {
    return *this = *this ^ b;
  }

}; //

} // namespace sst

#endif // SST_CATALOG_SOCKET_SHUTDOWN_HPP
