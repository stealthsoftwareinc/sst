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

// Include first to test independence.
#include <sst/catalog/file_rng_core.hpp>
// Include twice to test idempotence.
#include <sst/catalog/file_rng_core.hpp>
//

#include <cstdio>
#include <sst/catalog/SST_ASSERT.hpp>
#include <stdexcept>
#include <string>
#include <utility>

namespace sst {

void file_rng_core::open() {
  SST_ASSERT((!moved_from_));
  if (stream_ == nullptr) {
    stream_ = std::fopen(file_.c_str(), "rb");
    if (stream_ == nullptr) {
      throw std::runtime_error("Error opening file: " + file_);
    }
  }
}

void file_rng_core::close() noexcept {
  SST_ASSERT((!moved_from_));
  if (stream_ != nullptr) {
    static_cast<void>(std::fclose(stream_));
    stream_ = nullptr;
  }
}

file_rng_core::file_rng_core(std::string file, bool const keep_open)
    : file_rng_core(std::move(file), keep_open, 1024) {
}

file_rng_core::~file_rng_core() noexcept {
  if (!moved_from_) {
    close();
  }
}

std::size_t file_rng_core::buffer_size() const noexcept {
  return buffer_size_;
}

void file_rng_core::read(unsigned char * const dst,
                         std::size_t const n) {
  SST_ASSERT((!moved_from_));
  if (n > 0) {
    open();
    if (std::fread(dst, n, 1, stream_) != 1) {
      throw std::runtime_error("Error reading file: " + file_);
    }
    if (!keep_open_) {
      close();
    }
  }
}

} // namespace sst
