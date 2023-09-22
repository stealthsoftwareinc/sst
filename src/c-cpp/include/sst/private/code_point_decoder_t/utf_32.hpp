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

#ifndef SST_PRIVATE_CODE_POINT_DECODER_T_UTF_32_HPP
#define SST_PRIVATE_CODE_POINT_DECODER_T_UTF_32_HPP

#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/code_point_decoder_t.hpp>
#include <sst/catalog/perfect_ge.hpp>
#include <sst/catalog/perfect_le.hpp>
#include <sst/catalog/text_encoding.hpp>

namespace sst {

template<class Options>
class code_point_decoder_t<sst::text_encoding::utf_32, Options> {

  //--------------------------------------------------------------------
  // code_point_
  //--------------------------------------------------------------------

private:

  char32_t code_point_ = 0;

  //--------------------------------------------------------------------
  // options_
  //--------------------------------------------------------------------

private:

  Options options_;

  //--------------------------------------------------------------------
  // ready_
  //--------------------------------------------------------------------

private:

  bool ready_ = false;

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
      SST_F(options_);
      SST_F(ready_);
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
        SST_F(options_),
        SST_F(ready_) {
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

  SST_NODISCARD() static constexpr bool empty() noexcept {
    return true;
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
  //
  // This is how many code units we've consumed so far in the current
  // code point being decoded.
  //
  // If we just consumed the last code unit of a code point, this will
  // be zero.
  //

public:

  SST_NODISCARD() static constexpr int index() noexcept {
    return 0;
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
      SST_F(options_);
      SST_F(ready_);
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
        SST_F(options_),
        SST_F(ready_) {
  }

#undef SST_F

  //--------------------------------------------------------------------
  // put
  //--------------------------------------------------------------------

public:

  static void flush() noexcept {
  }

  template<class CodeUnit>
  void put(CodeUnit const & code_unit) noexcept(
      noexcept(code_point_ = code_unit)) {
    // TODO: Support an option to check for out of range code units?
    SST_ASSERT((sst::perfect_ge(code_unit, -2147483648)));
    SST_ASSERT((sst::perfect_le(code_unit, 4294967295)));
    code_point_ = static_cast<char32_t>(static_cast<char32_t>(code_unit)
                                        & 0xFFFFFFFFU);
    ready_ = true;
  }

  //--------------------------------------------------------------------
  // ready
  //--------------------------------------------------------------------

public:

  SST_NODISCARD() bool ready() const noexcept {
    return ready_;
  }

  //--------------------------------------------------------------------
  // reset
  //--------------------------------------------------------------------

public:

  void reset() noexcept {
    ready_ = false;
  }

  //--------------------------------------------------------------------
  // size
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

public:

  SST_NODISCARD() int size() const noexcept {
    return ready_ ? 1 : 0;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_PRIVATE_CODE_POINT_DECODER_T_UTF_32_HPP
