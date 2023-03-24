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

#ifndef SST_PRIVATE_CODE_POINT_DECODER_T_UTF_16_HPP
#define SST_PRIVATE_CODE_POINT_DECODER_T_UTF_16_HPP

#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_NODISCARD.h>
#include <sst/catalog/code_point_decoder_t.hpp>
#include <sst/catalog/malformed_code_point.hpp>
#include <sst/catalog/malformed_code_point_action.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/text_encoding.hpp>

namespace sst {

template<class Options>
class code_point_decoder_t<sst::text_encoding::utf_16, Options> {

  //--------------------------------------------------------------------
  // code_point_
  //--------------------------------------------------------------------

private:

  char32_t code_point_ = 0;

  //--------------------------------------------------------------------
  // index_
  //--------------------------------------------------------------------
  //
  // This is how many code units we've consumed so far in the current
  // code point being decoded.
  //
  // If we just consumed the last code unit of a code point, this will
  // be zero.
  //

private:

  int index_ = 0;

  //--------------------------------------------------------------------
  // options_
  //--------------------------------------------------------------------

private:

  Options options_;

  //--------------------------------------------------------------------
  // size_
  //--------------------------------------------------------------------
  //
  // This is how many code units are expected to be in the current code
  // point being decoded.
  //
  // If we just consumed the last code unit of a code point, this will
  // be the number of code units in the code point until the next code
  // unit is consumed.
  //
  // If we haven't consumed any code units yet, this will be zero.
  //
  // If we just ignored a malformed code point, this will be zero.
  //

private:

  int size_ = 0;

  //--------------------------------------------------------------------
  // construct
  //--------------------------------------------------------------------

public:

  explicit code_point_decoder_t(Options options = Options()) noexcept(
      noexcept(Options(std::move(options))))
      : options_(std::move(options)) {
  }

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

#define SST_F(x) x = other.x

  code_point_decoder_t &
  operator=(code_point_decoder_t const & other) noexcept(
      noexcept(SST_F(options_))) {
    if (this != &other) {
      SST_F(code_point_);
      SST_F(index_);
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

  code_point_decoder_t(code_point_decoder_t const & other) noexcept(
      noexcept(Options(other.options_)))
      : SST_F(code_point_),
        SST_F(index_),
        SST_F(options_),
        SST_F(size_) {
  }

#undef SST_F

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~code_point_decoder_t() noexcept {
  }

  //--------------------------------------------------------------------
  // empty
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() bool empty() const noexcept {
    return index_ == 0;
  }

  //--------------------------------------------------------------------
  // get
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() char32_t get() const noexcept {
    SST_ASSERT((ready()));
    return code_point_;
  }

  //--------------------------------------------------------------------
  // index
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() int index() const noexcept {
    return index_;
  }

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

public:

#define SST_F(x) x = std::move(other.x)

  code_point_decoder_t &
  operator=(code_point_decoder_t && other) noexcept(
      noexcept(SST_F(options_))) {
    if (this != &other) {
      SST_F(code_point_);
      SST_F(index_);
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

  code_point_decoder_t(code_point_decoder_t && other) noexcept(
      noexcept(Options(std::move(other.options_))))
      : SST_F(code_point_),
        SST_F(index_),
        SST_F(options_),
        SST_F(size_) {
  }

#undef SST_F

  //--------------------------------------------------------------------
  // put
  //--------------------------------------------------------------------

public:

  void flush() {
    if (ready()) {
      size_ = 0;
    } else if (!empty()) {
      if (options_.malformed_code_point_action()
          == sst::malformed_code_point_action::ignore) {
        size_ = 0;
        index_ = 0;
      } else {
        code_point_ = static_cast<char32_t>(0xFFFDU);
        size_ = index_;
        index_ = 0;
        if (options_.malformed_code_point_action()
            == sst::malformed_code_point_action::report) {
          throw sst::malformed_code_point("Malformed UTF-16 data.");
        }
      }
    }
  }

  template<class CodeUnit>
  void put(CodeUnit const & code_unit) {
    // TODO: Support an option to check for out of range code units?
    SST_ASSERT((sst::perfect_ge(code_unit, -32768)));
    SST_ASSERT((sst::perfect_le(code_unit, 65535)));
    unsigned int const u =
        static_cast<unsigned int>(code_unit) & 0xFFFFU;
    ++index_;
    if (index_ == 1) {
      if (u < 0xD800U || u >= 0xE000U) {
        code_point_ = static_cast<char32_t>(u);
        size_ = 1;
        index_ = 0;
      } else if (u < 0xDC00U) {
        code_point_ = static_cast<char32_t>(u - 0xD800U);
        size_ = 2;
      } else {
        flush();
      }
    } else if (u >= 0xDC00U && u < 0xE000U) {
      code_point_ <<= 10;
      code_point_ |= static_cast<char32_t>(u - 0xDC00U);
      code_point_ += static_cast<char32_t>(0x10000U);
      index_ = 0;
    } else {
      flush();
    }
  }

  //--------------------------------------------------------------------
  // ready
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() bool ready() const noexcept {
    return index_ == 0 && size_ > 0;
  }

  //--------------------------------------------------------------------
  // reset
  //--------------------------------------------------------------------

public:

  void reset() noexcept {
    index_ = 0;
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

#endif // #ifndef SST_PRIVATE_CODE_POINT_DECODER_T_UTF_16_HPP
