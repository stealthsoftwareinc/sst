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
#include <sst/catalog/openssl/err_exception.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/err_exception.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/err.h>
#include <openssl/opensslv.h>

namespace sst {
namespace guts {
namespace openssl {
namespace err_exception {

code_t default_code::operator()() const {
  code_t a;
  while (true) {
    code_t b;
    char const * data;
    int flags;
#if OPENSSL_VERSION_NUMBER >= 0x30000000
    b.code =
        ERR_get_error_all(&b.file, &b.line, &b.func, &data, &flags);
#else
    b.code = ERR_get_error_line_data(&b.file, &b.line, &data, &flags);
#endif
    if (b.code == 0UL) {
      return a;
    }
    if (flags & ERR_TXT_STRING) {
      b.data = data;
    }
    a = b;
  }
}

} // namespace err_exception
} // namespace openssl
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO
