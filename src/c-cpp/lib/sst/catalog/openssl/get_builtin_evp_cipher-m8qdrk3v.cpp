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
#include <sst/catalog/openssl/get_builtin_evp_cipher.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/get_builtin_evp_cipher.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <cstdlib>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/openssl/evp_cipher_type.hpp>
#include <sst/catalog/openssl/has_builtin_evp_cipher.hpp>

#include <openssl/evp.h>

namespace sst {
namespace openssl {

#define SST_F(type)                                                    \
  case sst::openssl::evp_cipher_type::type: {                          \
    void const * const cipher = ::EVP_##type();                        \
    if (cipher == nullptr) {                                           \
      throw sst::openssl::err_exception("EVP_" #type "()");            \
    }                                                                  \
    return cipher;                                                     \
  } break;

void const *
get_builtin_evp_cipher(sst::openssl::evp_cipher_type const type) {
  SST_ASSERT((sst::openssl::has_builtin_evp_cipher(type)));
  // clang-format off
  switch (type) {

    SST_F(aes_128_ctr)

    default:
      SST_ASSERT("Missing case." && (false));
      std::abort();
  }
  // clang-format on
}

#undef SST_F

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
