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

#ifndef SST_CATALOG_OPENSSL_EVP_CIPHER_CTX_HPP
#define SST_CATALOG_OPENSSL_EVP_CIPHER_CTX_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/int_max_v.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/openssl/evp_cipher_type.hpp>
#include <sst/catalog/overlap.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace openssl {

class SST_DLL_EXPORT evp_cipher_ctx {

public:

  enum class state_t {
    empty,
    active,
    finished,
  };

private:

  //--------------------------------------------------------------------

  state_t state_ = state_t::empty;

  //--------------------------------------------------------------------
  //
  // This is the pointer to the underlying EVP_CIPHER_CTX object. We use
  // void * instead of EVP_CIPHER_CTX * so that this header file doesn't
  // need to #include <openssl/evp.h>.
  //

  sst::basic_ptr<void> ctx_;

  //--------------------------------------------------------------------

  int block_size_ = 0;

  //--------------------------------------------------------------------
  //
  // This is the current number of bytes that have been fed into
  // update() that have not yet been ciphered and written out. This
  // happens when the total number of bytes that have been fed into
  // update() is not a multiple of the block size. For example, if 17
  // bytes have been fed into AES-128, only 16 will have been written
  // out, and 1 byte of slop will be sitting in the block accumulator.
  //

  int slop_ = 0;

  //--------------------------------------------------------------------

  void allocate();

  //--------------------------------------------------------------------

  void assert_invariants() const;

  //--------------------------------------------------------------------

  void clear() noexcept;

  //--------------------------------------------------------------------
  // finish_helper-fn5fgis0
  //--------------------------------------------------------------------

  void finish_helper(void * dst, int * dst_size);

  //--------------------------------------------------------------------
  // finish_helper-q75vfiwn
  //--------------------------------------------------------------------

  void finish_helper();

  //--------------------------------------------------------------------
  // update_helper
  //--------------------------------------------------------------------

  void update_helper(void const * src,
                     int src_size,
                     void * dst,
                     int * dst_size);

  //--------------------------------------------------------------------

public:

  evp_cipher_ctx() noexcept;

  evp_cipher_ctx(evp_cipher_ctx const & other) {
    *this = other;
  }

  evp_cipher_ctx & operator=(evp_cipher_ctx const & other);

  evp_cipher_ctx(evp_cipher_ctx && other) noexcept {
    *this = std::move(other);
  }

  evp_cipher_ctx & operator=(evp_cipher_ctx && other) noexcept;

  ~evp_cipher_ctx() SST_NOEXCEPT(true) = default;

  //--------------------------------------------------------------------
  // block_size-dgf9cx6r
  //--------------------------------------------------------------------

  int block_size() const;

  //--------------------------------------------------------------------
  // finish-mt7ozywx
  //--------------------------------------------------------------------

  template<class DstSize = int>
  evp_cipher_ctx & finish(void * dst,
                          DstSize * const dst_size = nullptr) {
    assert_invariants();
    SST_ASSERT((state_ == state_t::active));
    SST_ASSERT((dst != nullptr));
    int n;
    finish_helper(dst, &n);
    if (dst_size != nullptr) {
      SST_ASSERT((!sst::overlap(dst, n, dst_size)));
      *dst_size = static_cast<DstSize>(n);
    }
    return *this;
  }

  //--------------------------------------------------------------------
  // finish-gu56oixm
  //--------------------------------------------------------------------

  evp_cipher_ctx & finish() {
    assert_invariants();
    SST_ASSERT((state_ == state_t::active));
    finish_helper();
    return *this;
  }

  //--------------------------------------------------------------------
  // init-igs44chk
  //--------------------------------------------------------------------

  evp_cipher_ctx & init(sst::openssl::evp_cipher_type type,
                        void const * key,
                        void const * iv,
                        bool encrypt = true);

  //--------------------------------------------------------------------
  // slop-gznnt3qj
  //--------------------------------------------------------------------

  int slop() const;

  //--------------------------------------------------------------------
  // state-os63u8bb
  //--------------------------------------------------------------------

  state_t state() const;

  //--------------------------------------------------------------------
  // update-ydjzjqrw
  //--------------------------------------------------------------------

  template<class SrcSize, class DstSize = SrcSize>
  evp_cipher_ctx & update(void const * src,
                          SrcSize src_size,
                          void * dst,
                          DstSize * const dst_size = nullptr) {
    assert_invariants();
    SST_ASSERT((state_ == state_t::active));
    SST_ASSERT((src != nullptr));
    SST_ASSERT((!sst::is_negative(src_size)));
    SST_ASSERT((dst != nullptr));
    DstSize n = 0;
    while (src_size > 0) {
      int const src_step = sst::unsigned_lt(src_size, sst::int_max_v) ?
                               static_cast<int>(src_size) :
                               sst::int_max_v;
      int dst_step;
      update_helper(src, src_step, dst, &dst_step);
      src = static_cast<unsigned char const *>(src) + src_step;
      src_size -= static_cast<SrcSize>(src_step);
      dst = static_cast<unsigned char *>(dst) + dst_step;
      n += static_cast<DstSize>(dst_step);
    }
    if (dst_size != nullptr) {
      *dst_size = n;
    }
    return *this;
  }

  //--------------------------------------------------------------------
};

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // SST_CATALOG_OPENSSL_EVP_CIPHER_CTX_HPP
