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

#ifndef SST_CATALOG_FILE_RNG_CORE_HPP
#define SST_CATALOG_FILE_RNG_CORE_HPP

#include <cstdio>
#include <sst/catalog/SST_ASSERT.h>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/moved_from.hpp>
#include <sst/catalog/size_max_v.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <string>
#include <utility>

namespace sst {

class SST_DLL_EXPORT file_rng_core {
  sst::moved_from moved_from_;
  std::string file_;
  FILE * stream_ = nullptr;
  bool keep_open_;
  std::size_t buffer_size_;

  void open();

  void close() noexcept;

protected:
  using read_size_t = std::size_t;

  template<class Size>
  explicit file_rng_core(std::string file,
                         bool const keep_open,
                         Size const buffer_size)
      : file_((SST_ASSERT((buffer_size > 0)), std::move(file))),
        keep_open_(keep_open),
        buffer_size_((SST_ASSERT((buffer_size > 0)),
                      sst::unsigned_lt(buffer_size, sst::size_max_v) ?
                          static_cast<std::size_t>(buffer_size) :
                          static_cast<std::size_t>(sst::size_max_v))) {
  }

  explicit file_rng_core(std::string file = "/dev/urandom",
                         bool const keep_open = true);

  file_rng_core(file_rng_core const &) = delete;

  file_rng_core(file_rng_core &&) noexcept = default;

  file_rng_core & operator=(file_rng_core const &) = delete;

  file_rng_core & operator=(file_rng_core &&) = delete;

  ~file_rng_core() noexcept;

  std::size_t buffer_size() const noexcept;

  void read(unsigned char * dst, std::size_t n);
};

} // namespace sst

#endif // #ifndef SST_CATALOG_FILE_RNG_CORE_HPP
