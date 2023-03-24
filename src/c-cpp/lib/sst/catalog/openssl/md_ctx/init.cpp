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

#include <utility>
#include <vector>

#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/emplace.hpp>
#include <sst/catalog/hash_state.hpp>
#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/unique_ptr.hpp>

#include <openssl/evp.h>
#include <openssl/opensslv.h>

namespace sst {
namespace openssl {

md_ctx & md_ctx::init() {
  try {
    if (md_ == nullptr) {
      attach(nullptr);
    }
    EVP_MD * const md = static_cast<EVP_MD *>(md_);
    EVP_MD_CTX * const ctx = static_cast<EVP_MD_CTX *>(lazy_ctx());
    if (state_ == sst::hash_state::active()) {
#if OPENSSL_VERSION_NUMBER >= 0x10100000
      if (EVP_MD_CTX_reset(ctx) != 1) {
        throw sst::openssl::err_exception("EVP_MD_CTX_reset()");
      }
#else
      if (EVP_MD_CTX_cleanup(ctx) != 1) {
        throw sst::openssl::err_exception("EVP_MD_CTX_cleanup()");
      }
      EVP_MD_CTX_init(ctx);
#endif
    }
    if (state_ != sst::hash_state::ready()) {
      if (EVP_DigestInit_ex(ctx, md, nullptr) != 1) {
        throw sst::openssl::err_exception("EVP_DigestInit_ex()");
      }
    }
    if (out_ == nullptr) {
      int const n = EVP_MD_size(md);
      if (n < 0) {
        throw sst::openssl::err_exception("EVP_MD_size()");
      }
      (void)sst::checked_cast<output_t::size_type>(n);
      sst::unique_ptr<std::vector<unsigned char>> p{sst::emplace};
      sst::checked_resize(*p, n);
      out_ = std::move(p);
    }
    state_ = sst::hash_state::ready();
    return *this;
  } catch (...) {
    clear();
    throw;
  }
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
