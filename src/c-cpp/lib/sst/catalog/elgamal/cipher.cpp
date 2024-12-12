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
#include <sst/catalog/elgamal/cipher.hpp>
// Include twice to test idempotence.
#include <sst/catalog/elgamal/cipher.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER >= 0x10100000

#include <stdexcept>
#include <vector>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/elgamal/ciphertext.hpp>
#include <sst/catalog/elgamal/common.hpp>
#include <sst/catalog/elgamal/serialization.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/openssl/ec_group.hpp>
#include <sst/catalog/openssl/ec_point.hpp>
#include <sst/catalog/openssl/err_exception.hpp>
#include <sst/catalog/perfect_le.hpp>

#include <openssl/ec.h>

namespace sst {

namespace elgamal {

cipher::cipher(sst::openssl::ec_group const & group,
               sst::openssl::ec_point const & pkey,
               sst::bignum const & skey)
    : skey_(skey),
      pkey_(pkey, group),
      group_(group) {
}

cipher::cipher(sst::openssl::ec_group const & group,
               sst::openssl::ec_point const & pkey)
    : pkey_(pkey, group),
      group_(group) {
}

cipher::cipher(sst::openssl::ec_group const & group)
    : cipher(group, sst::openssl::ec_point(group)) {
}

cipher::cipher(int const curve_nid)
    : cipher(sst::openssl::ec_group::wrap(
          EC_GROUP_new_by_curve_name(curve_nid),
          "EC_GROUP_new_by_curve_name()")) {
}

sst::elgamal::ciphertext
cipher::encrypt_point(sst::openssl::ec_point const & message) const {
  sst::openssl::ec_point first(group());
  sst::openssl::ec_point second(group());

  sst::bignum const rand_num = random_element(group());

  if (EC_POINT_mul(group(),
                   first,
                   rand_num.peek(),
                   nullptr,
                   nullptr,
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }

  if (EC_POINT_mul(group(),
                   second,
                   nullptr,
                   pkey_,
                   rand_num.peek(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }

  if (EC_POINT_add(group(), second, second, message, sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  }

  return {first, second, group()};
}

void cipher::serialize_secret_key(
    std::vector<unsigned char> & dst) const {
  auto const s = skey_.to_bytes();
  dst.insert(dst.end(), s.begin(), s.end());
}

std::vector<unsigned char> cipher::serialize_secret_key() const {
  std::vector<unsigned char> dst;
  serialize_secret_key(dst);
  return dst;
}

void cipher::serialize_public_key(
    std::vector<unsigned char> & dst) const {
  serialize_point(dst, pkey_, group());
}

std::vector<unsigned char> cipher::serialize_public_key() const {
  std::vector<unsigned char> dst;
  serialize_public_key(dst);
  return dst;
}

void cipher::deserialize_skey(
    std::vector<unsigned char> const & src,
    std::vector<unsigned char>::size_type & idx,
    std::vector<unsigned char>::size_type const size) {
  skey_.set_from_bytes(src.data() + idx, src.data() + idx + size);
  idx += size;
}

void cipher::deserialize_skey(std::vector<unsigned char> const & src) {
  std::vector<unsigned char>::size_type idx = 0;
  deserialize_skey(src, idx, src.size());
}

void cipher::deserialize_pkey(
    std::vector<unsigned char> const & src,
    std::vector<unsigned char>::size_type & idx) {
  deserialize_point(src, idx, pkey_, group());
}

void cipher::deserialize_pkey(std::vector<unsigned char> const & src) {
  std::vector<unsigned char>::size_type idx = 0;
  deserialize_pkey(src, idx);
}

void cipher::keygen() {
  skey_ = random_element(group());

  if (EC_POINT_mul(group(),
                   pkey_,
                   skey_.peek(),
                   nullptr,
                   nullptr,
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }
}

sst::openssl::ec_point cipher::decrypt_to_point(
    sst::elgamal::ciphertext const & message_enc) const {
  sst::openssl::ec_point message(group());

  if (EC_POINT_mul(group(),
                   message,
                   nullptr,
                   message_enc.first(),
                   skey_.peek(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }

  if (EC_POINT_invert(group(), message, sst::bignum::ctx()) == 0) {
    throw sst::openssl::err_exception("EC_POINT_invert()");
  }
  if (EC_POINT_add(group(),
                   message,
                   message,
                   message_enc.second(),
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_add()");
  }
  return message;
}

sst::openssl::ec_point
cipher::encode(std::vector<unsigned char> const & message) const {
  SST_ASSERT(sst::perfect_le(message.size() * sst::char_bit_v,
                             EC_GROUP_order_bits(group())));

  sst::openssl::ec_point r(group());

  sst::bignum exponent;
  exponent.set_from_bytes(message, sst::integer_rep::pure_unsigned());

  if (EC_POINT_mul(group(),
                   r,
                   exponent.peek(),
                   nullptr,
                   nullptr,
                   sst::bignum::ctx())
      == 0) {
    throw sst::openssl::err_exception("EC_POINT_mul()");
  }
  return r;
}

} // namespace elgamal
} // namespace sst

#endif // #if OPENSSL_VERSION_NUMBER

#endif // #if SST_WITH_OPENSSL_CRYPTO
