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

#ifndef SST_CATALOG_PEEK_PTR_HPP
#define SST_CATALOG_PEEK_PTR_HPP

#include <cstddef>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/enable_t.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/optional.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/value_type_t.hpp>

namespace sst {

template<class, class = sst::enable_t>
class peek_ptr;

//----------------------------------------------------------------------
// Input iterators that provide storage
//----------------------------------------------------------------------

template<class Src>
class peek_ptr<
    Src,
    sst::enable_if_t<sst::is_input_iterator<Src>::value
                     && std::is_lvalue_reference<
                         decltype(*std::declval<sst::remove_cvref_t<
                                      Src> &>())>::value>> {

  using value_t = sst::value_type_t<Src>;
  value_t const * p_ = nullptr;

  //--------------------------------------------------------------------
  // Construction
  //--------------------------------------------------------------------

public:

  constexpr explicit peek_ptr() SST_NOEXCEPT(true) = default;

  constexpr explicit peek_ptr(Src const & src) noexcept(noexcept(&*src))
      : p_(&*src) {
  }

  //--------------------------------------------------------------------
  // Value existence retrieval
  //--------------------------------------------------------------------

public:

  SST_NODISCARD()
  constexpr friend bool operator==(peek_ptr const & x,
                                   std::nullptr_t) noexcept {
    return x.p_ == nullptr;
  }

  SST_NODISCARD()
  constexpr friend bool operator==(std::nullptr_t,
                                   peek_ptr const & x) noexcept {
    return x.p_ == nullptr;
  }

  SST_NODISCARD()
  constexpr friend bool operator!=(peek_ptr const & x,
                                   std::nullptr_t) noexcept {
    return x.p_ != nullptr;
  }

  SST_NODISCARD()
  constexpr friend bool operator!=(std::nullptr_t,
                                   peek_ptr const & x) noexcept {
    return x.p_ != nullptr;
  }

  SST_NODISCARD() constexpr explicit operator bool() const noexcept {
    return p_ != nullptr;
  }

  //--------------------------------------------------------------------
  // Value retrieval
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() value_t const & operator*() const noexcept {
    SST_ASSERT((p_ != nullptr));
    return *p_;
  }

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------
// Input iterators that do not provide storage
//----------------------------------------------------------------------

template<class Src>
class peek_ptr<
    Src,
    sst::enable_if_t<sst::is_input_iterator<Src>::value
                     && !std::is_lvalue_reference<
                         decltype(*std::declval<sst::remove_cvref_t<
                                      Src> &>())>::value>> {

  using value_t = sst::value_type_t<Src>;
  sst::optional<value_t> p_;

  //--------------------------------------------------------------------
  // Construction
  //--------------------------------------------------------------------

public:

  constexpr explicit peek_ptr() SST_NOEXCEPT(true) = default;

  constexpr explicit peek_ptr(Src const & src) noexcept(
      noexcept(sst::optional<value_t>(*src)))
      : p_(*src) {
  }

  //--------------------------------------------------------------------
  // Value existence retrieval
  //--------------------------------------------------------------------

public:

  SST_NODISCARD()
  constexpr friend bool operator==(peek_ptr const & x,
                                   std::nullptr_t) noexcept {
    return !x.p_.has_value();
  }

  SST_NODISCARD()
  constexpr friend bool operator==(std::nullptr_t,
                                   peek_ptr const & x) noexcept {
    return !x.p_.has_value();
  }

  SST_NODISCARD()
  constexpr friend bool operator!=(peek_ptr const & x,
                                   std::nullptr_t) noexcept {
    return x.p_.has_value();
  }

  SST_NODISCARD()
  constexpr friend bool operator!=(std::nullptr_t,
                                   peek_ptr const & x) noexcept {
    return x.p_.has_value();
  }

  SST_NODISCARD() constexpr explicit operator bool() const noexcept {
    return p_.has_value();
  }

  //--------------------------------------------------------------------
  // Value retrieval
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() value_t const & operator*() const noexcept {
    SST_ASSERT((p_.has_value()));
    return *p_;
  }

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_PEEK_PTR_HPP
