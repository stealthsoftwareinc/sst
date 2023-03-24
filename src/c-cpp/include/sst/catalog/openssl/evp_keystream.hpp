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

#ifndef SST_CATALOG_OPENSSL_EVP_KEYSTREAM_HPP
#define SST_CATALOG_OPENSSL_EVP_KEYSTREAM_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/begin.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/int_max_v.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/to_unsigned.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/unsigned_ge.hpp>
#include <sst/catalog/unsigned_max.hpp>
#include <sst/catalog/unsigned_min.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace openssl {

class SST_DLL_EXPORT evp_keystream {

  sst::moved_from moved_from_;
  sst::openssl::evp_cipher_ctx ctx_;
  std::vector<unsigned char> buf_;
  std::vector<unsigned char> zero_;
  decltype(buf_.size()) buf_i_ = 0;

public:

  //--------------------------------------------------------------------
  // ctor (hb5528k5)
  //--------------------------------------------------------------------

  explicit evp_keystream(sst::openssl::evp_cipher_ctx && ctx);

  //--------------------------------------------------------------------

  evp_keystream(evp_keystream const & other) = default;

  //--------------------------------------------------------------------

  evp_keystream & operator=(evp_keystream const & other) = default;

  //--------------------------------------------------------------------
  // Move constructor
  //--------------------------------------------------------------------

  evp_keystream(evp_keystream && other) noexcept
      : moved_from_(std::move(other.moved_from_)),
        ctx_(std::move(other.ctx_)),
        buf_(std::move(other.buf_)),
        zero_(std::move(other.zero_)),
        buf_i_(std::move(other.buf_i_)) {
  }

  //--------------------------------------------------------------------
  // Move assignment
  //--------------------------------------------------------------------

  evp_keystream & operator=(evp_keystream && other) noexcept {
    if (this != &other) {
      moved_from_ = std::move(other.moved_from_);
      ctx_ = std::move(other.ctx_);
      buf_ = std::move(other.buf_);
      zero_ = std::move(other.zero_);
      buf_i_ = std::move(other.buf_i_);
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // Destructor
  //--------------------------------------------------------------------

  ~evp_keystream() noexcept {
  }

  //--------------------------------------------------------------------
  // buffer_size (hox5uyzs)
  //--------------------------------------------------------------------

  int buffer_size() const noexcept {
    SST_ASSERT((!moved_from_));
    return static_cast<int>(buf_.size());
  }

  //--------------------------------------------------------------------
  // buffer_size (dspyk6uo)
  //--------------------------------------------------------------------

  template<class Size>
  evp_keystream & buffer_size(Size const size) {
    SST_STATIC_ASSERT((sst::is_integer<Size>::value));
    SST_ASSERT((!moved_from_));
    SST_ASSERT((!sst::is_negative(size)));
    auto const s = sst::to_unsigned(size);
    auto const b = sst::to_unsigned(ctx_.block_size());
    using m2_t = decltype(buf_.size());
    using m3_t = decltype(zero_.size());
    constexpr auto m1 = sst::to_unsigned(sst::int_max_v);
    constexpr auto m2 = sst::to_unsigned(sst::type_max<m2_t>::value);
    constexpr auto m3 = sst::to_unsigned(sst::type_max<m3_t>::value);
    auto const k = sst::to_unsigned(buf_.size() - buf_i_);
    auto const n = sst::unsigned_max(
        sst::unsigned_min(sst::unsigned_max(s, b) / b,
                          sst::unsigned_max(m1, b) / b,
                          sst::unsigned_max(m2, b) / b,
                          sst::unsigned_max(m3, b) / b)
            * b,
        k);
    std::vector<unsigned char> buf;
    std::vector<unsigned char> zero;
    sst::checked_resize(buf, n);
    sst::checked_resize(zero, n);
    std::copy_n(buf_.data() + buf_i_, k, buf.data() + (n - k));
    buf_ = std::move(buf);
    zero_ = std::move(zero);
    buf_i_ = static_cast<m2_t>(n - k);
    return *this;
  }

  //--------------------------------------------------------------------
  // max
  //--------------------------------------------------------------------

  static constexpr unsigned char max() noexcept {
    return sst::uchar_max_v;
  }

  //--------------------------------------------------------------------
  // min
  //--------------------------------------------------------------------

  static constexpr unsigned char min() noexcept {
    return 0;
  }

  //--------------------------------------------------------------------
  // operator() (y7cw5emn)
  //--------------------------------------------------------------------

  template<class Size>
  void * operator()(void * const dst, Size const size) {
    SST_STATIC_ASSERT((sst::is_integer<Size>::value));
    SST_ASSERT((!moved_from_));
    SST_ASSERT((dst != nullptr));
    SST_ASSERT((!sst::is_negative(size)));
    unsigned char * dst_p = static_cast<unsigned char *>(dst);
    decltype(+size) dst_n = size;
    {
      auto const k = sst::unsigned_min(dst_n, buf_.size() - buf_i_);
      dst_p = std::copy_n(buf_.data() + buf_i_, k, dst_p);
      dst_n -= static_cast<decltype(+dst_n)>(k);
      buf_i_ += static_cast<decltype(+buf_i_)>(k);
    }
    while (sst::unsigned_ge(dst_n, buf_.size())) {
      ctx_.update(zero_.data(), buf_.size(), dst_p);
      dst_p += buf_.size();
      dst_n -= static_cast<decltype(+dst_n)>(buf_.size());
    }
    if (dst_n > 0) {
      ctx_.update(zero_.data(), buf_.size(), buf_.data());
      dst_p = std::copy_n(buf_.data(), dst_n, dst_p);
      buf_i_ = static_cast<decltype(+buf_i_)>(dst_n);
    }
    return dst_p;
  }

  //--------------------------------------------------------------------
  // operator() (jx2foc8y)
  //--------------------------------------------------------------------

  template<class Dst,
           class Size,
           sst::enable_if_t<
               sst::is_output_iterator<Dst, unsigned char>::value
               && !std::is_convertible<Dst, void *>::value> = 0>
  Dst operator()(Dst dst, Size const size) {
    SST_STATIC_ASSERT((sst::is_integer<Size>::value));
    SST_ASSERT((!moved_from_));
    SST_ASSERT((!sst::is_negative(size)));
    decltype(+size) dst_n = size;
    goto start;
    while (dst_n > 0) {
      ctx_.update(zero_.data(), buf_.size(), buf_.data());
      buf_i_ = 0;
start:
      auto const k = sst::unsigned_min(dst_n, buf_.size() - buf_i_);
      auto src = &buf_[buf_i_];
      for (decltype(+k) i = 0; i < k; ++i) {
        *dst = *src++;
        ++dst;
      }
      dst_n -= static_cast<decltype(+dst_n)>(k);
      buf_i_ += static_cast<decltype(+buf_i_)>(k);
    }
    return dst;
  }

  //--------------------------------------------------------------------
  // operator() (zdt6ta28)
  //--------------------------------------------------------------------

  template<
      class Dst,
      sst::enable_if_t<sst::is_output_iterator<
                           decltype(sst::begin(std::declval<Dst &>())),
                           unsigned char>::value
                       && sst::is_integer<decltype(sst::size(
                           std::declval<Dst &>()))>::value> = 0>
  Dst & operator()(Dst & dst) {
    (*this)(sst::begin(dst), sst::size(dst));
    return dst;
  }

  //--------------------------------------------------------------------
  // operator() (a2kgojjw)
  //--------------------------------------------------------------------

  template<class Dst = std::vector<unsigned char>,
           class Size,
           sst::enable_if_t<sst::is_integer<Size>::value> = 0>
  sst::remove_cvref_t<Dst> operator()(Size const size) {
    SST_ASSERT((!sst::is_negative(size)));
    sst::remove_cvref_t<Dst> dst;
    sst::checked_resize(dst, size);
    (*this)(dst);
    return dst;
  }

  //--------------------------------------------------------------------
  // operator() (zvw44zyz)
  //--------------------------------------------------------------------

  unsigned char operator()() {
    unsigned char x;
    (*this)(&x, 1);
    return x;
  }

  //--------------------------------------------------------------------
  // result_type
  //--------------------------------------------------------------------

  using result_type = unsigned char;

  //--------------------------------------------------------------------
};

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // #ifndef SST_CATALOG_OPENSSL_EVP_KEYSTREAM_HPP
