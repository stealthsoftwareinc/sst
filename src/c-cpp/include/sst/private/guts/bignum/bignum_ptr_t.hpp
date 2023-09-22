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

#ifndef SST_PRIVATE_GUTS_BIGNUM_BIGNUM_PTR_T_HPP
#define SST_PRIVATE_GUTS_BIGNUM_BIGNUM_PTR_T_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <utility>

#include <sst/private/bignum_st.h>

#include <openssl/bn.h>

namespace sst {
namespace guts {
namespace bignum {

class bignum_ptr_t final {

  BIGNUM * p_ = nullptr;

public:

  constexpr bignum_ptr_t() noexcept = default;

  constexpr bignum_ptr_t(BIGNUM * const p) noexcept : p_(p) {
  }

  ~bignum_ptr_t() noexcept {
    if (p_ != nullptr && !(p_->flags & BN_FLG_STATIC_DATA)) {
      BN_free(p_);
    }
  }

  bignum_ptr_t(bignum_ptr_t const &) = delete;
  bignum_ptr_t & operator=(bignum_ptr_t const &) = delete;

  bignum_ptr_t(bignum_ptr_t && b) noexcept : p_(b.p_) {
    b.p_ = nullptr;
  }

  friend void swap(bignum_ptr_t & a, bignum_ptr_t & b) noexcept {
    std::swap(a.p_, b.p_);
  }

  bignum_ptr_t & operator=(bignum_ptr_t && b) noexcept {
    swap(*this, b);
    return *this;
  }

  operator BIGNUM *() const noexcept {
    return p_;
  }

  BIGNUM * operator->() const noexcept {
    return *this;
  }

  bool operator=(bignum_ptr_t const & other) const {
    return p_ == other.p_;
  }
};

} // namespace bignum
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_PRIVATE_GUTS_BIGNUM_BIGNUM_PTR_T_HPP
