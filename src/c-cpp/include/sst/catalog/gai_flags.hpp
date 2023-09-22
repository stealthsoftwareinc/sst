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

#ifndef SST_CATALOG_GAI_FLAGS_HPP
#define SST_CATALOG_GAI_FLAGS_HPP

#include <sst/catalog/ones_mask.hpp>

namespace sst {

class gai_flags {

  using value_t = unsigned int;

  value_t value_;

  constexpr gai_flags(value_t const value) noexcept : value_(value) {
  }

  enum class exponents : value_t {
    passive,

    all
  };

public:

  static constexpr gai_flags none() noexcept {
    return static_cast<value_t>(0);
  }

#define SST_F(x)                                                       \
  static constexpr gai_flags x() noexcept {                            \
    return static_cast<value_t>(1)                                     \
           << static_cast<value_t>(exponents::x);                      \
  }

  SST_F(passive)

#undef SST_F

  static constexpr gai_flags all() noexcept {
    return sst::ones_mask<value_t>(
        static_cast<value_t>(exponents::all));
  }

  friend bool constexpr operator==(gai_flags const a,
                                   gai_flags const b) noexcept {
    return a.value_ == b.value_;
  }

  friend bool constexpr operator!=(gai_flags const a,
                                   gai_flags const b) noexcept {
    return a.value_ != b.value_;
  }

  constexpr operator bool() const noexcept {
    return *this != none();
  }

  friend gai_flags constexpr operator&(gai_flags const a,
                                       gai_flags const b) noexcept {
    return a.value_ & b.value_;
  }

  friend gai_flags constexpr operator|(gai_flags const a,
                                       gai_flags const b) noexcept {
    return a.value_ | b.value_;
  }

  friend gai_flags constexpr operator^(gai_flags const a,
                                       gai_flags const b) noexcept {
    return a.value_ ^ b.value_;
  }

  friend gai_flags constexpr operator~(gai_flags const a) noexcept {
    return a ^ all();
  }
};

} // namespace sst

#endif // SST_CATALOG_GAI_FLAGS_HPP
