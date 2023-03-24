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

#include <sst/catalog/openssl/err_exception.hpp>

#include <openssl/evp.h>

namespace sst {
namespace openssl {

md_ctx & md_ctx::operator=(md_ctx const & other) {
  try {
    state_ = other.state_;
    if (other.md_ == nullptr) {
      md_ = nullptr;
    } else {
      attach(other.md_);
    }
    if (other.ctx_ == nullptr) {
      ctx_ = nullptr;
    } else {
      if (EVP_MD_CTX_copy_ex(
              static_cast<EVP_MD_CTX *>(lazy_ctx()),
              static_cast<EVP_MD_CTX const *>(other.ctx_))
          != 1) {
        throw sst::openssl::err_exception("EVP_MD_CTX_copy_ex()");
      }
    }
    out_ = other.out_;
    return *this;
  } catch (...) {
    clear();
    throw;
  }
}

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
