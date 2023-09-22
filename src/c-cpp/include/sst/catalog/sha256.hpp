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

#ifndef SST_CATALOG_SHA256_HPP
#define SST_CATALOG_SHA256_HPP

#include <sst/catalog/SST_FORWARDING_FUNCTION.hpp>
#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

//----------------------------------------------------------------------

#undef SST_F
#if 0

#elif SST_WITH_OPENSSL_CRYPTO
#include <sst/catalog/openssl/sha256.hpp>
#define SST_F sst::openssl::sha256

#endif

//----------------------------------------------------------------------

#ifdef SST_F

#define SST_FT_cpp_sst_sha256 (1)
namespace sst {
SST_FORWARDING_FUNCTION(sha256, SST_F)
} // namespace sst
#undef SST_F

#else

#define SST_FT_cpp_sst_sha256 (0)

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_SHA256_HPP
