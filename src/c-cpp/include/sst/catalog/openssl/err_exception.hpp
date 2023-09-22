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

#ifndef SST_CATALOG_OPENSSL_ERR_EXCEPTION_HPP
#define SST_CATALOG_OPENSSL_ERR_EXCEPTION_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <string>

#include <sst/catalog/error_code_exception.hpp>
#include <sst/catalog/openssl/exception.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

//----------------------------------------------------------------------

namespace guts {
namespace openssl {
namespace err_exception {

struct code_t final {
  unsigned long code = 0UL;
  char const * file = nullptr;
  int line = 0;
  char const * func = nullptr;
  char const * data = nullptr;
};

struct SST_DLL_EXPORT code_to_string {
  std::string operator()(code_t const code) const;
};

struct SST_DLL_EXPORT default_code final {
  code_t operator()() const;
};

} // namespace err_exception
} // namespace openssl
} // namespace guts

//----------------------------------------------------------------------
// explicit-s8h7r9i8
//----------------------------------------------------------------------

extern template class SST_DLL_EXPORT
    error_code_exception<guts::openssl::err_exception::code_t,
                         guts::openssl::err_exception::code_to_string,
                         guts::openssl::err_exception::default_code,
                         sst::openssl::exception>;

//----------------------------------------------------------------------

namespace openssl {

using err_exception = sst::error_code_exception<
    guts::openssl::err_exception::code_t,
    guts::openssl::err_exception::code_to_string,
    guts::openssl::err_exception::default_code,
    sst::openssl::exception>;

} // namespace openssl

//----------------------------------------------------------------------

} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_OPENSSL_ERR_EXCEPTION_HPP
