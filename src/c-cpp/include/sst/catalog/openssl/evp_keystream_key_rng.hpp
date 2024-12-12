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

#ifndef SST_CATALOG_OPENSSL_EVP_KEYSTREAM_KEY_RNG_HPP
#define SST_CATALOG_OPENSSL_EVP_KEYSTREAM_KEY_RNG_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <array>

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/has_size.hpp>
#include <sst/catalog/is_byte_input_iterable.hpp>
#include <sst/catalog/is_byte_input_iterator.hpp>
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
#include <sst/catalog/openssl/evp_cipher_type.hpp>
#include <sst/catalog/openssl/evp_keystream.hpp>
#include <sst/catalog/openssl/iv_size.hpp>
#include <sst/catalog/openssl/key_size.hpp>
#include <sst/catalog/size.hpp>
#include <sst/catalog/unsigned_eq.hpp>

namespace sst {
namespace openssl {

template<sst::openssl::evp_cipher_type CipherType>
class evp_keystream_key_rng : public sst::openssl::evp_keystream {

public:

  //--------------------------------------------------------------------
  // cipher_type
  //--------------------------------------------------------------------

  static constexpr sst::openssl::evp_cipher_type
  cipher_type() noexcept {
    return CipherType;
  }

  //--------------------------------------------------------------------
  // key_size
  //--------------------------------------------------------------------

  static constexpr int key_size() noexcept {
    return sst::openssl::key_size(cipher_type());
  }

  // clang-format off
  SST_STATIC_ASSERT("The cipher type must use a key." && (key_size() > 0));
  // clang-format on

  //--------------------------------------------------------------------
  // iv_size
  //--------------------------------------------------------------------

  static constexpr int iv_size() noexcept {
    return sst::openssl::iv_size(cipher_type());
  }

  //--------------------------------------------------------------------

private:

  //--------------------------------------------------------------------

  template<
      class Key,
      sst::enable_if_t<sst::is_byte_input_iterator<Key>::value> = 0>
  static sst::openssl::evp_cipher_ctx make_ctx(Key & key) {
    std::array<unsigned char, key_size()> k;
    for (decltype(k.size()) i = 0; i < k.size(); ++i) {
      k[i] = static_cast<unsigned char>(*key);
      ++key;
    }
    std::array<unsigned char, iv_size()> iv{};
    sst::openssl::evp_cipher_ctx ctx;
    ctx.init(cipher_type(),
             k.data(),
             iv.size() > 0 ? iv.data() : nullptr);
    return ctx;
  }

  //--------------------------------------------------------------------

public:

  //--------------------------------------------------------------------
  // Constructor (eqvtv7kd)
  //--------------------------------------------------------------------

  template<
      class Key,
      sst::enable_if_t<sst::is_byte_input_iterator<Key>::value> = 0>
  explicit evp_keystream_key_rng(Key key)
      : sst::openssl::evp_keystream(make_ctx(key)) {
  }

  //--------------------------------------------------------------------
  // Constructor (ee0getog)
  //--------------------------------------------------------------------

  template<class Key,
           sst::enable_if_t<sst::is_byte_input_iterable<Key>::value
                            && sst::has_size<Key>::value> = 0>
  explicit evp_keystream_key_rng(Key const & key)
      : evp_keystream_key_rng(
          (SST_ASSERT((sst::unsigned_eq(sst::size(key), key_size()))),
           sst::cbegin(key))) {
  }

  //--------------------------------------------------------------------
  // Constructor (amqse2xf)
  //--------------------------------------------------------------------

  template<class Key,
           sst::enable_if_t<sst::is_byte_input_iterable<Key>::value
                            && !sst::has_size<Key>::value> = 0>
  explicit evp_keystream_key_rng(Key const & key)
      : evp_keystream_key_rng(sst::cbegin(key)) {
  }

  //--------------------------------------------------------------------
};

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_OPENSSL_EVP_KEYSTREAM_KEY_RNG_HPP
