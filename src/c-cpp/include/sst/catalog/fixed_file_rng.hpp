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

#ifndef SST_CATALOG_FIXED_FILE_RNG_HPP
#define SST_CATALOG_FIXED_FILE_RNG_HPP

#include <utility>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/file_rng.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

template<char const * File>
class fixed_file_rng final {

  SST_STATIC_ASSERT((File != nullptr));

  using g_t = sst::file_rng;
  g_t g_;

public:

  using result_type = g_t::result_type;

  static constexpr result_type max() noexcept {
    return g_t::max();
  }

  static constexpr result_type min() noexcept {
    return g_t::min();
  }

  explicit fixed_file_rng(bool const keep_open = true)
      : g_(File, keep_open) {
  }

  template<class Size>
  explicit fixed_file_rng(bool const keep_open, Size const buffer_size)
      : g_(File, keep_open, buffer_size) {
  }

  fixed_file_rng(fixed_file_rng const &) = delete;

  fixed_file_rng(fixed_file_rng &&) noexcept = default;

  fixed_file_rng & operator=(fixed_file_rng const &) = delete;

  fixed_file_rng & operator=(fixed_file_rng &&) = delete;

  ~fixed_file_rng() noexcept {
  }

  result_type operator()() {
    return g_();
  }

  template<class... Args>
  auto operator()(Args &&... args)
      -> decltype(g_(std::forward<Args>(args)...)) {
    return g_(std::forward<Args>(args)...);
  }

  //--------------------------------------------------------------------
};

} // namespace sst

#endif // #ifndef SST_CATALOG_FIXED_FILE_RNG_HPP
