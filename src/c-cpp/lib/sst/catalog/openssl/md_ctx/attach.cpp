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
#include <sst/catalog/openssl/md_ctx.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/md_ctx.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/hash_state.hpp>
#include <sst/catalog/openssl/err_exception.hpp>

#include <openssl/evp.h>
#include <openssl/opensslv.h>

namespace sst {
namespace openssl {

md_ctx & md_ctx::attach(void const * md) {
  try {
    SST_ASSERT((state_ == sst::hash_state::empty()));
    if (md == nullptr) {
      md = EVP_sha256();
      if (md == nullptr) {
        throw sst::openssl::err_exception("EVP_sha256()");
      }
    }
    EVP_MD const * const p = static_cast<EVP_MD const *>(md);
    EVP_MD * const q = const_cast<EVP_MD *>(p);
#if OPENSSL_VERSION_NUMBER >= 0x30000000
    if (EVP_MD_up_ref(q) != 1) {
      throw sst::openssl::err_exception("EVP_MD_up_ref()");
    }
#endif
    md_ = q;
    return *this;
  } catch (...) {
    clear();
    throw;
  }
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
