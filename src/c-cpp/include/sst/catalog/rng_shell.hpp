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

#ifndef SST_CATALOG_RNG_SHELL_HPP
#define SST_CATALOG_RNG_SHELL_HPP

#include <algorithm>
#include <utility>
#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/begin.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte_pointer.hpp>
#include <sst/catalog/is_integer.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_output_iterator.hpp>
#include <sst/catalog/min.hpp>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/size_max_v.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/unsigned_gt.hpp>
#include <sst/catalog/unsigned_lt.hpp>

namespace sst {

template<class Core>
class rng_shell final : public Core {
  using read_size_t = typename Core::read_size_t;

  static constexpr read_size_t read_size_max() {
    return sst::type_max<read_size_t>::value;
  }

  static constexpr std::size_t buffer_size_limit() {
    return (sst::unsigned_lt(sst::size_max_v, read_size_max()) ?
                sst::size_max_v :
                static_cast<std::size_t>(read_size_max()))
           / 8;
  }

  static constexpr read_size_t read_size_limit() {
    return read_size_max() / 8;
  }

  sst::moved_from moved_from_;
  std::vector<unsigned char> buffer_;
  std::size_t i_;

  void refill() {
    SST_ASSERT((!moved_from_));
    if (i_ == buffer_.size()) {
      this->read(buffer_.data(),
                 static_cast<read_size_t>(buffer_.size()));
      i_ = 0;
    }
  }

  template<class OutputIt, class Size>
  OutputIt generate(OutputIt dst, Size n) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((!sst::is_negative(n)));
    while (n > 0) {
      refill();
      std::size_t const r = buffer_.size() - i_;
      Size const k = sst::unsigned_lt(n, r) ? n : static_cast<Size>(r);
      dst = std::copy_n(buffer_.data() + i_, k, dst);
      i_ += static_cast<std::size_t>(k);
      n -= k;
    }
    return dst;
  }

public:
  using result_type = unsigned char;

  static constexpr unsigned char min() noexcept {
    return 0;
  }

  static constexpr unsigned char max() noexcept {
    return sst::uchar_max_v;
  }

  template<class... Args>
  explicit rng_shell(Args &&... args)
      : Core(std::forward<Args>(args)...),
        buffer_((SST_ASSERT((this->buffer_size() > 0)),
                 sst::min(this->buffer_size(), buffer_size_limit()))),
        i_(buffer_.size()) {
  }

  rng_shell(rng_shell const &) = delete;

  rng_shell(rng_shell &&) noexcept = default;

  rng_shell & operator=(rng_shell const &) = delete;

  rng_shell & operator=(rng_shell &&) = delete;

  ~rng_shell() noexcept = default;

  unsigned char operator()() {
    SST_ASSERT((!moved_from_));
    refill();
    return buffer_[i_++];
  }

  //--------------------------------------------------------------------
  // operator() (pffpgm6w)
  //--------------------------------------------------------------------

  template<class OutputIt,
           class Size,
           sst::enable_if_t<!sst::is_byte_pointer<OutputIt>::value> = 0>
  OutputIt operator()(OutputIt const dst, Size const n) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((!sst::is_negative(n)));
    return generate(dst, n);
  }

  //--------------------------------------------------------------------
  // operator() (zxuxyv49)
  //--------------------------------------------------------------------

  template<class OutputIt,
           class Size,
           sst::enable_if_t<sst::is_byte_pointer<OutputIt>::value> = 0>
  OutputIt operator()(OutputIt const dst, Size n) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((dst != nullptr));
    SST_ASSERT((!sst::is_negative(n)));
    unsigned char * p = reinterpret_cast<unsigned char *>(dst);
    while (sst::unsigned_gt(n, buffer_size_limit())) {
      Size const k = sst::unsigned_lt(n, read_size_limit()) ?
                         n :
                         static_cast<Size>(read_size_limit());
      this->read(p, static_cast<read_size_t>(k));
      p += k;
      n -= k;
    }
    return reinterpret_cast<OutputIt>(generate(p, n));
  }

  //--------------------------------------------------------------------
  // operator() (a6zszky8)
  //--------------------------------------------------------------------

  template<
      class Dst,
      sst::enable_if_t<sst::is_output_iterator<
                           decltype(sst::begin(std::declval<Dst &>())),
                           unsigned char>::value
                       && sst::is_integer<decltype(sst::size(
                           std::declval<Dst &>()))>::value> = 0>
  Dst & operator()(Dst & dst) {
    SST_ASSERT((!moved_from_));
    (*this)(sst::begin(dst), sst::size(dst));
    return dst;
  }

  //--------------------------------------------------------------------
  // operator() (q8bmwtex)
  //--------------------------------------------------------------------

  template<class Dst = std::vector<unsigned char>,
           class Size,
           sst::enable_if_t<sst::is_integer<Size>::value> = 0>
  sst::remove_cvref_t<Dst> operator()(Size const size) {
    SST_ASSERT((!moved_from_));
    SST_ASSERT((!sst::is_negative(size)));
    sst::remove_cvref_t<Dst> dst;
    sst::checked_resize(dst, size);
    (*this)(dst);
    return dst;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_CATALOG_RNG_SHELL_HPP
