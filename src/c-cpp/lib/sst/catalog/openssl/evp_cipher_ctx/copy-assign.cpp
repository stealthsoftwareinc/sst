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

#include <openssl/evp.h>
#include <openssl/opensslv.h>

namespace sst {
namespace openssl {

evp_cipher_ctx &
evp_cipher_ctx::operator=(evp_cipher_ctx const & other) {
  assert_invariants();
  if (this == &other) {
    return *this;
  }
  other.assert_invariants();
  if (other.state_ != state_t::empty) {
    allocate();
    if (::EVP_CIPHER_CTX_copy(
            static_cast<EVP_CIPHER_CTX *>(ctx_),
            static_cast<EVP_CIPHER_CTX const *>(other.ctx_))
        != 1) {
      sst::openssl::err_exception e("EVP_CIPHER_CTX_copy()");
      clear();
      throw e;
    }
  } else if (state_ == state_t::active) {
#if OPENSSL_VERSION_NUMBER >= 0x10100000
    if (::EVP_CIPHER_CTX_reset(static_cast<EVP_CIPHER_CTX *>(ctx_))
        != 1) {
      sst::openssl::err_exception e("EVP_CIPHER_CTX_reset()");
      clear();
      throw e;
    }
#else
    if (::EVP_CIPHER_CTX_cleanup(static_cast<EVP_CIPHER_CTX *>(ctx_))
        != 1) {
      sst::openssl::err_exception e("EVP_CIPHER_CTX_cleanup()");
      clear();
      throw e;
    }
    ::EVP_CIPHER_CTX_init(static_cast<EVP_CIPHER_CTX *>(ctx_));
#endif
  }
  state_ = other.state_;
  block_size_ = other.block_size_;
  slop_ = other.slop_;
  return *this;
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
