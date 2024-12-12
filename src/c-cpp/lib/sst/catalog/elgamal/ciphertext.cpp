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
#include <sst/catalog/elgamal/ciphertext.hpp>
// Include twice to test idempotence.
#include <sst/catalog/elgamal/ciphertext.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/opensslv.h>
#include <openssl/bn.h>

#if OPENSSL_VERSION_NUMBER >= 0x10100000

#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/elgamal/common.hpp>
#include <sst/catalog/elgamal/serialization.hpp>
#include <sst/catalog/openssl/ec_group.hpp>
#include <sst/catalog/openssl/ec_point.hpp>
#include <sst/catalog/openssl/err_exception.hpp>

#include <openssl/ec.h>

namespace sst {

namespace elgamal {

ciphertext::ciphertext(sst::openssl::ec_point const & first,
                       sst::openssl::ec_point const & second,
                       sst::openssl::ec_group const & group)
    : first_(first, group),
      second_(second, group),
      group_(group) {
}

ciphertext::ciphertext(sst::openssl::ec_group const & group)
    : ciphertext(sst::openssl::ec_point(group),
                 sst::openssl::ec_point(group),
                 group) {
}

ciphertext::ciphertext(ciphertext const & other)
    : ciphertext(other.first(), other.second(), other.group()) {
}

ciphertext & ciphertext::operator=(ciphertext const & other) {
  if (this == &other) {
    return *this;
  }
  if (EC_GROUP_cmp(group(), other.group(), sst::bignum::ctx()) != 0) {
    throw sst::openssl::err_exception("EC_GROUP_cmp");
  }
  first_ = sst::openssl::ec_point(other.first(), group());
  second_ = sst::openssl::ec_point(other.second(), group());

  return *this;
}

void ciphertext::invert() {
  sst::openssl::ec_point first_tmp(first(), group());

  if (EC_POINT_invert(group(), first_tmp, sst::bignum::ctx()) == 0) {
    throw sst::openssl::err_exception("EC_POINT_invert()");
  }

  if (EC_POINT_invert(group(), second_, sst::bignum::ctx()) == 0) {
    throw sst::openssl::err_exception("EC_POINT_invert()");
  }

  first_ = std::move(first_tmp);
}

ciphertext ciphertext::operator+(ciphertext const & other) const {
  ciphertext tmp(first(), second(), group());

  if (EC_POINT_add(group(),
                   tmp.first_,
                   first(),
                   other.first(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  };
  if (EC_POINT_add(group(),
                   tmp.second_,
                   second(),
                   other.second(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  }
  return tmp;
}

ciphertext & ciphertext::operator+=(ciphertext const & other) {
  sst::openssl::ec_point first_tmp(group());

  if (EC_POINT_add(group(),
                   first_tmp,
                   first(),
                   other.first(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  }
  if (EC_POINT_add(group(),
                   second_,
                   second(),
                   other.second(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  }
  first_ = std::move(first_tmp);
  return *this;
}

ciphertext & ciphertext::operator*=(sst::bignum const & scalar) {

  if (scalar.is_zero()) {
    this->set_to_identity();
  } else if (scalar.is_negative()) {
    this->invert();
    this->operator*=(scalar.abs());
  } else {

    sst::openssl::ec_point first_tmp(group());

    if (EC_POINT_mul(group(),
                     first_tmp,
                     nullptr,
                     first(),
                     scalar.peek(),
                     sst::bignum::ctx())
        == 0) {
      throw sst::openssl::err_exception("EC_POINT_mul()");
    }

    if (EC_POINT_mul(group(),
                     second_,
                     nullptr,
                     second(),
                     scalar.peek(),
                     sst::bignum::ctx())
        == 0) {
      throw sst::openssl::err_exception("EC_POINT_mul()");
    }

    first_ = std::move(first_tmp);
  }
  return *this;
}

ciphertext & ciphertext::operator/=(sst::bignum const & scalar){
  auto order = EC_GROUP_get0_order(group_);
  sst::bignum mod = order;
  auto inv = sst::bignum::inv_mod(scalar,mod);
  *this *= inv;
  return *this;
}

void ciphertext::set_to_identity() {
  ciphertext tmp(*this);

  if (EC_POINT_set_to_infinity(group(), tmp.first_) == 0) {
    throw sst::openssl::err_exception("EC_POINT_set_to_infinity()");
  }
  if (EC_POINT_set_to_infinity(group(), tmp.second_) == 0) {
    throw sst::openssl::err_exception("EC_POINT_set_to_infinity()");
  }
  *this = tmp;
}
void ciphertext::set(sst::openssl::ec_point const & first,
                     sst::openssl::ec_point const & second) {

  first_ = sst::openssl::ec_point(first, group());
  second_ = sst::openssl::ec_point(second, group());
}

void ciphertext::rerandomize(sst::openssl::ec_point const & pkey) {
  auto const rand_num = sst::elgamal::random_element(group());

  sst::openssl::ec_point r1(group());

  if (EC_POINT_mul(group(),
                   r1,
                   rand_num.peek(),
                   nullptr,
                   nullptr,
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }

  if (EC_POINT_add(group(), first_, r1, first(), sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  };

  sst::openssl::ec_point r2(group());
  if (EC_POINT_mul(group(),
                   r2,
                   nullptr,
                   pkey,
                   rand_num.peek(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }

  if (EC_POINT_add(group(), second_, r2, first(), sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  };
}

ciphertext
ciphertext::deserialize(std::vector<unsigned char> const & src,
                        std::vector<unsigned char>::size_type & idx,
                        sst::openssl::ec_group const & group) {

  sst::openssl::ec_point first(group);
  sst::openssl::ec_point second(group);
  deserialize_point(src, idx, first, group);
  deserialize_point(src, idx, second, group);
  return {first, second, group};
}

void ciphertext::serialize(std::vector<unsigned char> & buf) const {
  sst::elgamal::serialize_point(buf, first(), group());
  sst::elgamal::serialize_point(buf, second(), group());
}

} // namespace elgamal
} // namespace sst

#endif // #if OPENSSL_VERSION_NUMBER
#endif // #if SST_WITH_OPENSSL_CRYPTO
