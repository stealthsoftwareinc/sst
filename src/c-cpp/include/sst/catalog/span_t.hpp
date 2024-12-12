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

#ifndef SST_CATALOG_SPAN_T_HPP
#define SST_CATALOG_SPAN_T_HPP

#include <cstddef>
#include <type_traits>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

//
// TODO: Allow Size to be a bigint.
//
// TODO: Allow Size to be std::integral_constant for static spans. Use a
//       partial specialization for this.
//

template<class T = unsigned char, class Size = std::size_t>
class span_t {

  SST_STATIC_ASSERT((std::is_integral<Size>::value));

public:

  using value_type = sst::remove_cvref_t<T>;
  using size_type = sst::remove_cvref_t<Size>;

  //--------------------------------------------------------------------
  // begin
  //--------------------------------------------------------------------

public:

  T * begin() const noexcept {
    return data_;
  }

  //--------------------------------------------------------------------
  // construct
  //--------------------------------------------------------------------

public:

  span_t(T * const data, Size const size) : data_(data), size_(size) {
    SST_ASSERT((!sst::is_negative(size)));
    SST_ASSERT((data != nullptr || size == 0));
  }

  //--------------------------------------------------------------------
  // copy-assign
  //--------------------------------------------------------------------

public:

  span_t & operator=(span_t const & other) = default;

  //--------------------------------------------------------------------
  // copy-construct
  //--------------------------------------------------------------------

public:

  span_t(span_t const & other) = default;

  //--------------------------------------------------------------------
  // data
  //--------------------------------------------------------------------

private:

  T * data_;

public:

  T * data() const noexcept {
    return data_;
  }

  //--------------------------------------------------------------------
  // destruct
  //--------------------------------------------------------------------

public:

  ~span_t() noexcept = default;

  //--------------------------------------------------------------------
  // end
  //--------------------------------------------------------------------

public:

  T * end() const noexcept {
    return data_ + size_;
  }

  //--------------------------------------------------------------------
  // move-assign
  //--------------------------------------------------------------------

  // Intentionally omitted.

  //--------------------------------------------------------------------
  // move-construct
  //--------------------------------------------------------------------

  // Intentionally omitted.

  //--------------------------------------------------------------------
  // size
  //--------------------------------------------------------------------

private:

  Size size_;

public:

  Size size() const {
    return size_;
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // SST_CATALOG_SPAN_T_HPP
