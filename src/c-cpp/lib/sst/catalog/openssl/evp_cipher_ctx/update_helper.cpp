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

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/overlap.hpp>

#include <openssl/evp.h>

namespace sst {
namespace openssl {

void evp_cipher_ctx::update_helper(void const * const src,
                                   int const src_size,
                                   void * const dst,
                                   int * const dst_size) {
  assert_invariants();
  SST_ASSERT((state_ == state_t::active));
  SST_ASSERT((src != nullptr));
  SST_ASSERT((src_size >= 0));
  SST_ASSERT((dst != nullptr));
  SST_ASSERT((dst_size != nullptr));
  int n;
  if (::EVP_CipherUpdate(static_cast<EVP_CIPHER_CTX *>(ctx_),
                         static_cast<unsigned char *>(dst),
                         &n,
                         static_cast<unsigned char const *>(src),
                         src_size)
      != 1) {
    sst::openssl::err_exception e("EVP_CipherUpdate()");
    clear();
    throw e;
  }
  // TODO: Some cipher implementations are probably fine with certain
  //       kinds of overlaps, like src == dst.
  SST_ASSERT((!sst::overlap(src, src_size, dst, n)));
  SST_ASSERT((!sst::overlap(src, src_size, dst_size)));
  SST_ASSERT((!sst::overlap(dst, n, dst_size)));
  slop_ += src_size % block_size_;
  slop_ %= block_size_;
  *dst_size = n;
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
