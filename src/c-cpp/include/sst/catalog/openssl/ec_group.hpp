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

#ifndef SST_CATALOG_OPENSSL_EC_GROUP_HPP
#define SST_CATALOG_OPENSSL_EC_GROUP_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

struct ec_group_st;

namespace sst {
namespace openssl {

class SST_DLL_EXPORT ec_group {

  sst::basic_ptr<ec_group_st> group_ = nullptr;

  ec_group() SST_NOEXCEPT(true);

public:

  explicit ec_group(ec_group_st const * group);

  ec_group(ec_group const & other) : ec_group(other.group_.get()) {
  }

  ec_group(ec_group && other) SST_NOEXCEPT(true) = default;

  ec_group & operator=(ec_group const & other) {
    *this = ec_group(other);
    return *this;
  }

  ec_group & operator=(ec_group && other) SST_NOEXCEPT(true) = default;

  ~ec_group() SST_NOEXCEPT(true) = default;

  static ec_group wrap(ec_group_st * group,
                       char const * error = "Error creating EC_GROUP");

  operator ec_group_st *() SST_NOEXCEPT(true) {
    SST_ASSERT((this->group_ != nullptr));
    return this->group_.get();
  }

  operator ec_group_st const *() const SST_NOEXCEPT(true) {
    SST_ASSERT((this->group_ != nullptr));
    return this->group_.get();
  }

}; //

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_OPENSSL_EC_GROUP_HPP
