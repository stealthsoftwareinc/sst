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

#ifndef SST_CATALOG_SEEDED_CRYPTO_RNG_HPP
#define SST_CATALOG_SEEDED_CRYPTO_RNG_HPP

#include <cstddef>

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>
#include <sst/catalog/openssl/evp_cipher_type.hpp>
#include <sst/catalog/openssl/evp_keystream_key_rng.hpp>

namespace sst {

template<std::size_t SeedSize>
class seeded_crypto_rng;

//----------------------------------------------------------------------
// 16-byte seed
//----------------------------------------------------------------------

#if 0

#elif SST_WITH_OPENSSL_CRYPTO

#define SST_base                                                       \
  sst::openssl::evp_keystream_key_rng<                                 \
      sst::openssl::evp_cipher_type::aes_128_ctr>

template<>
class seeded_crypto_rng<16> : public SST_base {
  using base = SST_base;
public:
  using base::base;
};

#undef SST_base

#endif

//----------------------------------------------------------------------

} // namespace sst

#endif // SST_CATALOG_SEEDED_CRYPTO_RNG_HPP
