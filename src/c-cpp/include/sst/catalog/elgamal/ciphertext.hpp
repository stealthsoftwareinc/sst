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

#ifndef SST_CATALOG_ELGAMAL_CIPHERTEXT_HPP
#define SST_CATALOG_ELGAMAL_CIPHERTEXT_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER >= 0x10100000

#include <vector>

#include <sst/catalog/bignum.hpp>
#include <sst/catalog/elgamal/common.hpp>
#include <sst/catalog/openssl/ec_point.hpp>

namespace sst {
namespace elgamal {

class ciphertext final {
public:

  ciphertext(sst::openssl::ec_point const & first,
             sst::openssl::ec_point const & second,
             sst::openssl::ec_group const & group);

  ciphertext(sst::openssl::ec_group const & group);

  ~ciphertext() noexcept = default;

  ciphertext(ciphertext const & other);

  ciphertext & operator=(ciphertext const & other);

  ciphertext(ciphertext && other) noexcept = default;

  ciphertext & operator=(ciphertext && other) noexcept = default;

  void invert();

  ciphertext operator-() const {
    ciphertext tmp = *this;
    tmp.invert();
    return tmp;
  }

  ciphertext operator+(ciphertext const & other) const;

  ciphertext operator-(ciphertext const & other) const {
    return *this + (-other);
  }

  ciphertext & operator+=(ciphertext const & other);

  ciphertext & operator*=(sst::bignum const & scalar);

  ciphertext & operator/=(sst::bignum const & scalar);

  void set_to_identity();

  void set(sst::openssl::ec_point const & first,
           sst::openssl::ec_point const & second);

  sst::openssl::ec_point const & first() const {
    return first_;
  };

  sst::openssl::ec_point const & second() const {
    return second_;
  };

  sst::openssl::ec_group const & group() const {
    return group_;
  };

  void rerandomize(sst::openssl::ec_point const & pkey);

  static ciphertext
  deserialize(std::vector<unsigned char> const & src,
              std::vector<unsigned char>::size_type & idx,
              sst::openssl::ec_group const & group);

  static ciphertext deserialize(std::vector<unsigned char> const & src,
                                sst::openssl::ec_group const & group) {
    std::vector<unsigned char>::size_type idx = 0;
    return deserialize(src, idx, group);
  }

  void serialize(std::vector<unsigned char> & buf) const;

protected:
private:
  sst::openssl::ec_point first_;
  sst::openssl::ec_point second_;
  sst::openssl::ec_group group_;
};

} // namespace elgamal
} // namespace sst

#endif // #if OPENSSL_VERSION_NUMBER

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_ELGAMAL_CIPHERTEXT_HPP
