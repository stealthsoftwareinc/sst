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

#ifndef SST_CATALOG_OPENSSL_SHA256_T_HPP
#define SST_CATALOG_OPENSSL_SHA256_T_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/openssl/md_ctx.hpp>
#include <sst/catalog/seq_hash_shell.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace openssl {

class SST_DLL_EXPORT sha256_t
    : public sst::seq_hash_shell<sst::openssl::md_ctx> {

public:

  sha256_t();

}; //

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_OPENSSL_SHA256_T_HPP
