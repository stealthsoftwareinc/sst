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

#ifndef SST_CATALOG_BOXED_HPP
#define SST_CATALOG_BOXED_HPP

#include <utility>

#include <sst/SST_CPP_CONSTEXPR.hpp>
#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

template<class T, class Tag>
class boxed {

public:

  using value_type = sst::remove_cvref_t<T>;

private:

  value_type value_;

  //--------------------------------------------------------------------
  // Default operations
  //--------------------------------------------------------------------
  //
  // Construction is forwarded to value_type and always explicit.
  //
  // Copy construction, copy assignment, move construction, move
  // assignment, and destruction are intentionally omitted so the
  // compiler will implicitly declare/define them.
  //

public:

  template<class... Args,
           sst::enable_if_t<
               SST_COMPILES(value_type(std::declval<Args>()...))> = 0>
  explicit constexpr boxed(Args &&... args) noexcept(
      SST_NOEXCEPT(value_type(std::forward<Args>(args)...)))
      : value_(std::forward<Args>(args)...) {
  }

  //--------------------------------------------------------------------
  // Value retrieval
  //--------------------------------------------------------------------

  explicit SST_CPP14_CONSTEXPR operator T &() noexcept {
    return value_;
  }

  explicit constexpr operator T const &() const noexcept {
    return value_;
  }

  SST_CPP14_CONSTEXPR T & value() noexcept {
    return value_;
  }

  constexpr T const & value() const noexcept {
    return value_;
  }

  //--------------------------------------------------------------------
  // Comparisons for aliases and publicly derived classes
  //--------------------------------------------------------------------

  constexpr bool operator<(boxed const & b) const
      noexcept(noexcept(std::declval<T>() < std::declval<T>())) {
    return value() < b.value();
  }

  constexpr bool operator>(boxed const & b) const
      noexcept(noexcept(std::declval<T>() > std::declval<T>())) {
    return value() > b.value();
  }

  constexpr bool operator<=(boxed const & b) const
      noexcept(noexcept(std::declval<T>() <= std::declval<T>())) {
    return value() <= b.value();
  }

  constexpr bool operator>=(boxed const & b) const
      noexcept(noexcept(std::declval<T>() >= std::declval<T>())) {
    return value() >= b.value();
  }

  constexpr bool operator==(boxed const & b) const
      noexcept(noexcept(std::declval<T>() == std::declval<T>())) {
    return value() == b.value();
  }

  constexpr bool operator!=(boxed const & b) const
      noexcept(noexcept(std::declval<T>() != std::declval<T>())) {
    return value() != b.value();
  }

  //--------------------------------------------------------------------
  // Comparisons for privately derived classes
  //--------------------------------------------------------------------

  constexpr bool operator<(Tag const & b) const
      noexcept(noexcept(std::declval<T>() < std::declval<T>())) {
    return value() < b.value();
  }

  constexpr bool operator>(Tag const & b) const
      noexcept(noexcept(std::declval<T>() > std::declval<T>())) {
    return value() > b.value();
  }

  constexpr bool operator<=(Tag const & b) const
      noexcept(noexcept(std::declval<T>() <= std::declval<T>())) {
    return value() <= b.value();
  }

  constexpr bool operator>=(Tag const & b) const
      noexcept(noexcept(std::declval<T>() >= std::declval<T>())) {
    return value() >= b.value();
  }

  constexpr bool operator==(Tag const & b) const
      noexcept(noexcept(std::declval<T>() == std::declval<T>())) {
    return value() == b.value();
  }

  constexpr bool operator!=(Tag const & b) const
      noexcept(noexcept(std::declval<T>() != std::declval<T>())) {
    return value() != b.value();
  }
};

} // namespace sst

#endif // #ifndef SST_CATALOG_BOXED_HPP
