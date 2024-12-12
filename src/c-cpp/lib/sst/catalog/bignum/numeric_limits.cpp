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
#include <sst/catalog/bignum.hpp>
// Include twice to test idempotence.
#include <sst/catalog/bignum.hpp>
//

#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <limits>

namespace std {

constexpr bool numeric_limits<sst::bignum>::is_specialized;

constexpr int numeric_limits<sst::bignum>::digits;

constexpr int numeric_limits<sst::bignum>::digits10;

constexpr int numeric_limits<sst::bignum>::max_digits10;

constexpr bool numeric_limits<sst::bignum>::is_signed;

constexpr bool numeric_limits<sst::bignum>::is_integer;

constexpr bool numeric_limits<sst::bignum>::is_exact;

constexpr int numeric_limits<sst::bignum>::radix;

constexpr int numeric_limits<sst::bignum>::min_exponent;

constexpr int numeric_limits<sst::bignum>::min_exponent10;

constexpr int numeric_limits<sst::bignum>::max_exponent;

constexpr int numeric_limits<sst::bignum>::max_exponent10;

constexpr bool numeric_limits<sst::bignum>::has_infinity;

constexpr bool numeric_limits<sst::bignum>::has_quiet_NaN;

constexpr bool numeric_limits<sst::bignum>::has_signaling_NaN;

constexpr std::float_denorm_style
    numeric_limits<sst::bignum>::has_denorm;

constexpr bool numeric_limits<sst::bignum>::has_denorm_loss;

constexpr bool numeric_limits<sst::bignum>::is_iec559;

constexpr bool numeric_limits<sst::bignum>::is_bounded;

constexpr bool numeric_limits<sst::bignum>::is_modulo;

constexpr bool numeric_limits<sst::bignum>::traps;

constexpr bool numeric_limits<sst::bignum>::tinyness_before;

constexpr std::float_round_style
    numeric_limits<sst::bignum>::round_style;

} // namespace std

#endif // #if SST_WITH_OPENSSL_CRYPTO
