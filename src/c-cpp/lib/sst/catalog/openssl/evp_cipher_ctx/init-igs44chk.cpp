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
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/openssl/evp_cipher_type.hpp>
#include <sst/catalog/openssl/get_builtin_evp_cipher.hpp>
#include <sst/catalog/openssl/has_builtin_evp_cipher.hpp>

#include <openssl/evp.h>

namespace sst {
namespace openssl {

evp_cipher_ctx &
evp_cipher_ctx::init(sst::openssl::evp_cipher_type const type,
                     void const * const key,
                     void const * const iv,
                     bool const encrypt) {
  assert_invariants();
  SST_ASSERT((state_ != state_t::active));
  SST_ASSERT((sst::openssl::has_builtin_evp_cipher(type)));
  SST_ASSERT((key != nullptr));
  SST_ASSERT((iv != nullptr));
  state_ = state_t::active;
  allocate();
  EVP_CIPHER const * const cipher = static_cast<EVP_CIPHER const *>(
      sst::openssl::get_builtin_evp_cipher(type));
  if (::EVP_CipherInit_ex(static_cast<EVP_CIPHER_CTX *>(ctx_),
                          cipher,
                          nullptr,
                          static_cast<unsigned char const *>(key),
                          static_cast<unsigned char const *>(iv),
                          encrypt ? 1 : 0)
      != 1) {
    sst::openssl::err_exception e("EVP_CipherInit_ex()");
    clear();
    throw e;
  }
  block_size_ = ::EVP_CIPHER_block_size(cipher);
  slop_ = 0;
  return *this;
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
