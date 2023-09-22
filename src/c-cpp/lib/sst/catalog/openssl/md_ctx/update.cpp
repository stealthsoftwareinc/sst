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
#include <sst/catalog/openssl/md_ctx.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/md_ctx.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <cstddef>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/hash_state.hpp>
#include <sst/catalog/openssl/err_exception.hpp>

#include <openssl/evp.h>

namespace sst {
namespace openssl {

namespace {

std::size_t find_r(unsigned char const * const p, std::size_t const k) {
  SST_ASSERT((p != nullptr || k == 0U));
  std::size_t r = 0U;
  while (r < k && p[r] != 0U) {
    ++r;
  }
  return r;
}

} // namespace

std::size_t md_ctx::update_helper(unsigned char const * const p,
                                  std::size_t k,
                                  bool const allow_zero) {
  try {
    SST_ASSERT((state_ == sst::hash_state::ready()
                || state_ == sst::hash_state::active()));
    SST_ASSERT((p != nullptr || k == 0U));
    std::size_t const r = allow_zero ? k : find_r(p, k);
    if (r > 0U) {
      if (EVP_DigestUpdate(static_cast<EVP_MD_CTX *>(ctx_), p, r)
          != 1) {
        throw sst::openssl::err_exception("EVP_DigestUpdate()");
      }
    }
    return r;
  } catch (...) {
    clear();
    throw;
  }
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
