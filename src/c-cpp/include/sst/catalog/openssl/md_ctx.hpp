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

#ifndef SST_CATALOG_OPENSSL_MD_CTX_HPP
#define SST_CATALOG_OPENSSL_MD_CTX_HPP

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_DEFAULT_NOEXCEPT.hpp>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/hash_state.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_char.hpp>
#include <sst/catalog/is_input_iterator.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_sentinel.hpp>
#include <sst/catalog/is_value_sentinel.hpp>
#include <sst/catalog/is_zero.hpp>
#include <sst/catalog/peek.hpp>
#include <sst/catalog/pos.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/size_max_v.hpp>
#include <sst/catalog/span_t.hpp>
#include <sst/catalog/step.hpp>
#include <sst/catalog/unique_ptr.hpp>
#include <sst/catalog/unsigned_min.hpp>
#include <sst/catalog/value_type_t.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace openssl {

class SST_DLL_EXPORT md_ctx {

  // TODO: state_ only needs to be tracked in debug mode. In other
  //       words, use SST_DEBUG_ABI here.
  sst::hash_state state_ = sst::hash_state::empty();
  sst::basic_ptr<void> md_ = nullptr;
  sst::basic_ptr<void> ctx_ = nullptr;
  sst::unique_ptr<std::vector<unsigned char>> out_ = nullptr;

  void * lazy_ctx();

public:

  template<class T>
  using is_input = sst::is_byte<T>;

  using output_t = std::vector<unsigned char>;

  md_ctx() noexcept;

  md_ctx(md_ctx const & other) {
    *this = other;
  }

  md_ctx & operator=(md_ctx const & other);

  md_ctx(md_ctx && other) noexcept {
    *this = std::move(other);
  }

  md_ctx & operator=(md_ctx && other) noexcept;

  ~md_ctx() SST_DEFAULT_NOEXCEPT(true) = default;

  md_ctx & clear() noexcept {
    return *this = md_ctx();
  }

  md_ctx & attach(void const * md);

  md_ctx & init();

  //--------------------------------------------------------------------
  // update
  //--------------------------------------------------------------------

private:

  std::size_t update_helper(unsigned char const * p,
                            std::size_t k,
                            bool allow_zero = true);

public:

  template<class Src,
           class End,
           sst::enable_if_t<
               sst::is_input_iterator<Src, is_input>::value
               && sst::is_integer_ish<End>::value
               && std::is_pointer<sst::remove_cvref_t<Src>>::value> = 0>
  md_ctx & update(Src src, End const & end) {
    SST_ASSERT((state_ == sst::hash_state::ready()
                || state_ == sst::hash_state::active()));
    SST_ASSERT((src != nullptr || sst::is_zero(end)));
    SST_ASSERT((!sst::is_negative(end)));
    using src_value_t = sst::value_type_t<Src>;
    bool const allow_zero = !sst::is_char<src_value_t>::value;
    std::size_t const k_max = sst::size_max_v >> 2;
    End n = end;
    while (!sst::is_zero(n)) {
      std::size_t const k = sst::unsigned_min<std::size_t>(n, k_max);
      std::size_t const r =
          update_helper(reinterpret_cast<unsigned char const *>(&*src),
                        k,
                        allow_zero);
      // TODO: Use sst::advance?
      src += r;
      if (r < k) {
        ++src;
        break;
      }
      n -= static_cast<End>(k);
    }
    state_ = sst::hash_state::active();
    return *this;
  }

  template<
      class Src,
      class End,
      sst::enable_if_t<sst::is_input_iterator<Src, is_input>::value
                       && (sst::is_sentinel<End, Src>::value
                           || sst::is_value_sentinel<End, Src>::value
                           || (sst::is_integer_ish<End>::value
                               && !std::is_pointer<sst::remove_cvref_t<
                                      Src>>::value))> = 0>
  md_ctx & update(Src src, End const & end) {
    SST_ASSERT((state_ == sst::hash_state::ready()
                || state_ == sst::hash_state::active()));
    using src_value_t = sst::value_type_t<Src>;
    bool const allow_zero = !sst::is_char<src_value_t>::value;
    unsigned char p[16384];
    std::size_t k = 0U;
    sst::pos<Src, End> pos;
    while (true) {
      auto const q = sst::peek(src, end, pos);
      if (q == nullptr) {
        break;
      }
      unsigned char const b = static_cast<unsigned char>(*q);
      if (!allow_zero && b == 0U) {
        break;
      }
      if (k == sizeof(p)) {
        update_helper(p, k);
        k = 0U;
      }
      p[k] = b;
      ++k;
      sst::step(src, end, pos);
    }
    if (k > 0U) {
      update_helper(p, k);
    }
    state_ = sst::hash_state::active();
    return *this;
  }

  //--------------------------------------------------------------------

  md_ctx & finish();

  //--------------------------------------------------------------------

  output_t const & output() const & noexcept {
    SST_ASSERT((state_ == sst::hash_state::finished()));
    SST_ASSERT((out_ != nullptr));
    return *out_;
  }

  output_t && output() && noexcept {
    SST_ASSERT((state_ == sst::hash_state::finished()));
    SST_ASSERT((out_ != nullptr));
    return std::move(*out_.release());
  }

  //--------------------------------------------------------------------
};

} // namespace openssl
} // namespace sst

#endif // #if SST_WITH_OPENSSL_CRYPTO

#endif // #ifndef SST_CATALOG_OPENSSL_MD_CTX_HPP
