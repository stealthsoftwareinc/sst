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

#ifndef SST_CATALOG_UNSIGNED_MOD_HPP
#define SST_CATALOG_UNSIGNED_MOD_HPP

#include <type_traits>

#include <sst/catalog/SST_CONSTEXPR_ASSERT.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/if_chain_t.hpp>
#include <sst/catalog/is_integer_ish.hpp>
#include <sst/catalog/is_integer_like.hpp>
#include <sst/catalog/is_negative.hpp>
#include <sst/catalog/is_positive.hpp>
#include <sst/catalog/to_unsigned.hpp>

namespace sst {

#define SST_r (R(sst::to_unsigned(x) % sst::to_unsigned(m)))

template<class R_ = void,
         class X,
         class M,
         sst::enable_if_t<sst::is_integer_like<X>::value
                          && sst::is_integer_like<M>::value> = 0,
         class R = sst::if_chain_t<std::is_void<R_>, M, R_>>
constexpr R unsigned_mod(X const x, M const m)
    SST_NOEXCEPT(noexcept(SST_r)) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(x)));
  SST_CONSTEXPR_ASSERT((sst::is_positive(m)));
  return SST_r;
}

#undef SST_r

template<class R_ = void,
         class X,
         class M,
         sst::enable_if_t<sst::is_integer_ish<X>::value
                          && !sst::is_integer_like<X>::value
                          && sst::is_integer_like<M>::value> = 0,
         class R = sst::if_chain_t<std::is_void<R_>, M, R_>>
R unsigned_mod(X const & x, M const m) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(x)));
  SST_CONSTEXPR_ASSERT((sst::is_positive(m)));
  return R(x % m);
}

template<class R_ = void,
         class X,
         class M,
         sst::enable_if_t<sst::is_integer_like<X>::value
                          && sst::is_integer_ish<M>::value
                          && !sst::is_integer_like<M>::value> = 0,
         class R = sst::if_chain_t<std::is_void<R_>, M, R_>>
R unsigned_mod(X const x, M const & m) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(x)));
  SST_CONSTEXPR_ASSERT((sst::is_positive(m)));
  return R(x % m);
}

template<class R_ = void,
         class X,
         class M,
         sst::enable_if_t<sst::is_integer_ish<X>::value
                          && !sst::is_integer_like<X>::value
                          && sst::is_integer_ish<M>::value
                          && !sst::is_integer_like<M>::value> = 0,
         class R = sst::if_chain_t<std::is_void<R_>, M, R_>>
R unsigned_mod(X const & x, M const & m) {
  SST_CONSTEXPR_ASSERT((!sst::is_negative(x)));
  SST_CONSTEXPR_ASSERT((sst::is_positive(m)));
  return R(x % m);
}

} // namespace sst

//----------------------------------------------------------------------
// Compile-time tests
//----------------------------------------------------------------------

#include <sst/catalog/SST_COMPILE_TIME_TESTS.h>

#if SST_COMPILE_TIME_TESTS

#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/strict_eq.hpp>

#define SST_F(x, y) SST_STATIC_ASSERT((sst::strict_eq(x, y)))

SST_F(sst::unsigned_mod(false, true), false);
SST_F(sst::unsigned_mod(true, true), false);

SST_F(sst::unsigned_mod(0, true), false);

SST_F(sst::unsigned_mod(0, 1), 0);
SST_F(sst::unsigned_mod(1, 1), 0);
SST_F(sst::unsigned_mod(2, 1), 0);
SST_F(sst::unsigned_mod(3, 1), 0);

SST_F(sst::unsigned_mod(0, 1L), 0L);
SST_F(sst::unsigned_mod(1, 1L), 0L);
SST_F(sst::unsigned_mod(2, 1L), 0L);
SST_F(sst::unsigned_mod(3, 1L), 0L);

SST_F(sst::unsigned_mod(5678, 1234), 742);
SST_F(sst::unsigned_mod(5678, 1234L), 742L);
SST_F(sst::unsigned_mod(5678L, 1234), 742);
SST_F(sst::unsigned_mod(5678L, 1234L), 742L);

#undef SST_F

#endif // SST_COMPILE_TIME_TESTS

//----------------------------------------------------------------------

#endif // SST_CATALOG_UNSIGNED_MOD_HPP
