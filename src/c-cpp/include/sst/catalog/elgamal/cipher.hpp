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

#ifndef SST_CATALOG_ELGAMAL_CIPHER_HPP
#define SST_CATALOG_ELGAMAL_CIPHER_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER >= 0x10100000

#include <cstddef>
#include <vector>

#include <sst/catalog/bignum.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/checked.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/elgamal/ciphertext.hpp>
#include <sst/catalog/elgamal/serialization.hpp>
#include <sst/catalog/openssl/ec_group.hpp>
#include <sst/catalog/openssl/ec_point.hpp>

#include <openssl/ec.h>

namespace sst {
namespace elgamal {

class cipher final {
public:

  cipher(sst::openssl::ec_group const & group,
         sst::openssl::ec_point const & pkey,
         sst::bignum const & skey);

  cipher(sst::openssl::ec_group const & group,
         sst::openssl::ec_point const & pkey);

  cipher(sst::openssl::ec_group const & group);

  cipher(int const curve_nid);

  ~cipher() noexcept = default;

  cipher(cipher const & other)
      : skey_(other.skey_),
        pkey_(other.pkey_, other.group()),
        group_(other.group()) {
  }

  cipher(cipher && other) noexcept = default;

  cipher & operator=(cipher const & other) {
    *this = cipher(other);
    return *this;
  }

  cipher & operator=(cipher && other) noexcept = default;

  sst::elgamal::ciphertext
  encrypt_point(sst::openssl::ec_point const & message) const;

  sst::elgamal::ciphertext encrypt_small_domain(
      std::vector<unsigned char> const & message) const {
    return encrypt_point(encode(message));
  }

  template<typename Value = std::size_t, typename Size = int>
  sst::elgamal::ciphertext
  encrypt_small_domain(Value const & message,
                       Size const & n = 1) const {
    std::vector<unsigned char> buf;
    serialize_integer(buf, message, n);
    return encrypt_small_domain(buf);
  }

  template<typename Value = std::size_t, typename Size = int>
  Value
  decrypt_small_domain(sst::elgamal::ciphertext const & message_enc,
                       Size const & n = 1) const {
    auto const point = decrypt_to_point(message_enc);
    return decode(point, n);
  }

  void serialize_secret_key(std::vector<unsigned char> & dst) const;
  std::vector<unsigned char> serialize_secret_key() const;

  void serialize_public_key(std::vector<unsigned char> & dst) const;
  std::vector<unsigned char> serialize_public_key() const;

  void
  deserialize_skey(std::vector<unsigned char> const & src,
                   std::vector<unsigned char>::size_type & idx,
                   std::vector<unsigned char>::size_type const size);
  void deserialize_skey(std::vector<unsigned char> const & src);

  void deserialize_pkey(std::vector<unsigned char> const & src,
                        std::vector<unsigned char>::size_type & idx);
  void deserialize_pkey(std::vector<unsigned char> const & src);

  void keygen();

  sst::openssl::ec_group const & group() const {
    return group_;
  };

protected:
private:
  sst::bignum skey_{};
  sst::openssl::ec_point pkey_;
  sst::openssl::ec_group group_;

  sst::openssl::ec_point
  decrypt_to_point(sst::elgamal::ciphertext const & message_enc) const;

  sst::openssl::ec_point
  encode(std::vector<unsigned char> const & message) const;

  template<typename Value = std::size_t, typename Size = int>
  Value decode(sst::openssl::ec_point const & point,
               Size const & n = 1) const {
    sst::openssl::ec_point gen(EC_GROUP_get0_generator(group()),
                               group());
    sst::openssl::ec_point g(group());

    int cmp_code = 1 - EC_POINT_is_at_infinity(group(), point);
    int add_code = 1;

    auto const max_exp_size =
        (sst::checked(1U) << (sst::char_bit_v * sst::checked(n)))
            .value();
    decltype(+max_exp_size) exponent = 0;
    while (cmp_code == 1 && (exponent < max_exp_size)) {
      exponent++;

      add_code = EC_POINT_add(group(), g, g, gen, sst::bignum::ctx());
      if (add_code == 0) {
        throw sst::openssl::err_exception("EC_POINT_cmp");
      }

      cmp_code = EC_POINT_cmp(group(), g, point, sst::bignum::ctx());
      if (cmp_code == -1) {
        throw sst::openssl::err_exception("EC_POINT_add");
      }
    }

    return sst::checked_cast<Value>(exponent);
  }
};
} // namespace elgamal
} // namespace sst

#endif // #if OPENSSL_VERSION_NUMBER

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_ELGAMAL_CIPHER_HPP
