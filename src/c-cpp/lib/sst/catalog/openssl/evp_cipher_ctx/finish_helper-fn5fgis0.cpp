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

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/overlap.hpp>

#include <openssl/evp.h>

namespace sst {
namespace openssl {

void evp_cipher_ctx::finish_helper(void * const dst,
                                   int * const dst_size) {
  assert_invariants();
  SST_ASSERT((state_ == state_t::active));
  SST_ASSERT((dst != nullptr));
  SST_ASSERT((dst_size != nullptr));
  state_ = state_t::finished;
  int n;
  if (::EVP_CipherFinal_ex(static_cast<EVP_CIPHER_CTX *>(ctx_),
                           static_cast<unsigned char *>(dst),
                           &n)
      != 1) {
    sst::openssl::err_exception e("EVP_CipherFinal_ex()");
    clear();
    throw e;
  }
  SST_ASSERT((!sst::overlap(dst, n, dst_size)));
  *dst_size = n;
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
