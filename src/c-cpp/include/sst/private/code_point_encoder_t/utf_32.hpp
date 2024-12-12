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

#ifndef SST_PRIVATE_CODE_POINT_ENCODER_T_UTF_32_HPP
#define SST_PRIVATE_CODE_POINT_ENCODER_T_UTF_32_HPP

#include <cstdint>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/promote_unsigned_t.hpp>
#include <sst/catalog/text_encoding.hpp>
#include <sst/catalog/unsigned_le.hpp>

namespace sst {

template<class Options>
class code_point_encoder_t<sst::text_encoding::utf_32, Options> {

  //--------------------------------------------------------------------
  // code_unit_t
  //--------------------------------------------------------------------

public:

  using code_unit_t = std::uint_least32_t;

  //--------------------------------------------------------------------
  // code_unit_
  //--------------------------------------------------------------------

private:

  code_unit_t code_unit_ = 0;

  //--------------------------------------------------------------------
  // options_
  //--------------------------------------------------------------------

private:

  Options options_;

  //--------------------------------------------------------------------
  // size_
  //--------------------------------------------------------------------

private:

  int size_ = 0;

  //--------------------------------------------------------------------
  // construct
  //--------------------------------------------------------------------

public:

  explicit code_point_encoder_t(Options options = Options()) noexcept(
      noexcept(Options(std::move(options))))
      : options_(std::move(options)) {
  }

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

#define SST_F(x) x = other.x

  code_point_encoder_t &
  operator=(code_point_encoder_t const & other) noexcept(
      noexcept(SST_F(options_))) {
    if (this != &other) {
      SST_F(code_unit_);
      SST_F(options_);
      SST_F(size_);
    }
    return *this;
  }

#undef SST_F

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

#define SST_F(x) x(other.x)

  code_point_encoder_t(code_point_encoder_t const & other) noexcept(
      noexcept(Options(other.options_)))
      : SST_F(code_unit_),
        SST_F(options_),
        SST_F(size_) {
  }

#undef SST_F

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~code_point_encoder_t() noexcept {
  }

  //--------------------------------------------------------------------
  // get
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() code_unit_t const * get() const noexcept {
    SST_ASSERT((ready()));
    return &code_unit_;
  }

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

#define SST_F(x) x = std::move(other.x)

  code_point_encoder_t &
  operator=(code_point_encoder_t && other) noexcept(
      noexcept(SST_F(options_))) {
    if (this != &other) {
      SST_F(code_unit_);
      SST_F(options_);
      SST_F(size_);
    }
    return *this;
  }

#undef SST_F

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

public:

#define SST_F(x) x(std::move(other.x))

  code_point_encoder_t(code_point_encoder_t && other) noexcept(
      noexcept(Options(std::move(other.options_))))
      : SST_F(code_unit_),
        SST_F(options_),
        SST_F(size_) {
  }

#undef SST_F

  //--------------------------------------------------------------------
  // put
  //--------------------------------------------------------------------

private:

  using work_t = sst::promote_unsigned_t<char32_t>;

public:

  template<class CodePoint>
  void put(CodePoint const & code_point) noexcept(
      noexcept(static_cast<work_t>(code_point))) {
    SST_ASSERT((!sst::is_negative(code_point)));
    SST_ASSERT((sst::unsigned_le(code_point, 0xFFFFFFFF)));
    work_t const x = static_cast<work_t>(code_point);
    code_unit_ = static_cast<code_unit_t>(x);
    size_ = 1;
  }

  //--------------------------------------------------------------------
  // ready
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() bool ready() const noexcept {
    return size_ > 0;
  }

  //--------------------------------------------------------------------
  // reset
  //--------------------------------------------------------------------

public:

  void reset() noexcept {
    size_ = 0;
  }

  //--------------------------------------------------------------------
  // size
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() int size() const noexcept {
    return size_;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_PRIVATE_CODE_POINT_ENCODER_T_UTF_32_HPP
