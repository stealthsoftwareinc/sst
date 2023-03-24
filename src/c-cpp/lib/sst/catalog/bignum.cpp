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

#include <sst/catalog/bignum.hpp>
#include <sst/config.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <utility>
#include <vector>

namespace sst {

namespace guts {
namespace bignum {

bignum_bn_ctx_t & bignum_bn_ctx() {
  static thread_local bignum_bn_ctx_t x;
  return x;
}

namespace {

thread_local std::vector<std::vector<unsigned char>> buffer_pool;

std::vector<unsigned char> acquire_buffer() {
  if (buffer_pool.empty()) {
    return std::vector<unsigned char>();
  }
  std::vector<unsigned char> buffer(std::move(buffer_pool.back()));
  buffer_pool.pop_back();
  return buffer;
}

void release_buffer(std::vector<unsigned char> && buffer) noexcept {
  buffer_pool.push_back(std::move(buffer));
}

} // namespace

buffer_t::buffer_t() : buffer(acquire_buffer()) {
}

buffer_t::~buffer_t() noexcept {
  release_buffer(std::move(buffer));
}

} // namespace bignum
} // namespace guts

} // namespace sst

#endif // SST_WITH_OPENSSL_CRYPTO
