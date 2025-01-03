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

#ifndef SST_CATALOG_WINDOWS_BCRYPT_RNG_CORE_HPP
#define SST_CATALOG_WINDOWS_BCRYPT_RNG_CORE_HPP

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/size_max_v.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/config.h>

#if SST_WITH_WINDOWS_BCRYPT

#include <cstddef>

namespace sst {

class SST_DLL_EXPORT windows_bcrypt_rng_core {
  sst::moved_from moved_from_;
  std::size_t buffer_size_;

protected:
  using read_size_t = unsigned long;

  template<class Size>
  explicit windows_bcrypt_rng_core(Size const buffer_size)
      : buffer_size_((SST_ASSERT((buffer_size > 0)),
                      sst::unsigned_lt(buffer_size, sst::size_max_v) ?
                          static_cast<std::size_t>(buffer_size) :
                          static_cast<std::size_t>(sst::size_max_v))) {
  }

  explicit windows_bcrypt_rng_core();

  windows_bcrypt_rng_core(windows_bcrypt_rng_core const &) = delete;

  windows_bcrypt_rng_core(windows_bcrypt_rng_core &&) noexcept =
      default;

  windows_bcrypt_rng_core &
  operator=(windows_bcrypt_rng_core const &) = delete;

  windows_bcrypt_rng_core &
  operator=(windows_bcrypt_rng_core &&) = delete;

  ~windows_bcrypt_rng_core() noexcept = default;

  std::size_t buffer_size() const noexcept;

  void read(unsigned char * dst, read_size_t n);
};

} // namespace sst

#endif // #if SST_WITH_WINDOWS_BCRYPT

#endif // SST_CATALOG_WINDOWS_BCRYPT_RNG_CORE_HPP
