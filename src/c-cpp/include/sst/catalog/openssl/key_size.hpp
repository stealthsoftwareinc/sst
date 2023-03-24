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

#ifndef SST_CATALOG_OPENSSL_KEY_SIZE_HPP
#define SST_CATALOG_OPENSSL_KEY_SIZE_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <stdexcept>

#include <sst/catalog/openssl/evp_cipher_type.hpp>

namespace sst {
namespace openssl {

//----------------------------------------------------------------------
// key_size (i5ivhy44)
//----------------------------------------------------------------------

#define SST_F(c, k) : type == sst::openssl::evp_cipher_type::c ? (k)

constexpr int
key_size(sst::openssl::evp_cipher_type const type) noexcept {
  // clang-format off
  return false ? 0

    SST_F(aes_128_ctr, 16)

  : throw std::logic_error("sst::openssl::key_size(sst::openssl::evp_cipher_type type): Missing case.");
  // clang-format on
}

#undef SST_F

//----------------------------------------------------------------------

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // #ifndef SST_CATALOG_OPENSSL_KEY_SIZE_HPP