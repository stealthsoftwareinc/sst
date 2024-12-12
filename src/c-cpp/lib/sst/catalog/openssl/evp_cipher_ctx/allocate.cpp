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

// Include first to test independence.
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/openssl/err_exception.hpp>

#include <openssl/evp.h>
#include <openssl/opensslv.h>

namespace sst {
namespace openssl {

void evp_cipher_ctx::allocate() {
  if (ctx_ == nullptr) {
#if OPENSSL_VERSION_NUMBER >= 0x10100000
    ctx_ = ::EVP_CIPHER_CTX_new();
    if (ctx_ == nullptr) {
      sst::openssl::err_exception e("EVP_CIPHER_CTX_new()");
      clear();
      throw e;
    }
#else
    try {
      ctx_.allocate(sizeof(EVP_CIPHER_CTX));
    } catch (...) {
      clear();
      throw;
    }
    ::EVP_CIPHER_CTX_init(static_cast<EVP_CIPHER_CTX *>(ctx_));
#endif
  }
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
