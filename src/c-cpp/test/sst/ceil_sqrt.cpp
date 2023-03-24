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

#undef SST_COMPILE_TIME_TESTS
#define SST_COMPILE_TIME_TESTS 1

// Include first to test independence.
#include <sst/catalog/ceil_sqrt.hpp>
// Include twice to test idempotence.
#include <sst/catalog/ceil_sqrt.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/config.h>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    SST_TEST_BOOL((sst::ceil_sqrt(false) == false));
    SST_TEST_BOOL((sst::ceil_sqrt(true) == true));

    //------------------------------------------------------------------

#define F(T)                                                           \
  ([&]() {                                                             \
    SST_TEST_BOOL((sst::ceil_sqrt(T(0)) == T(0)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(1)) == T(1)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(2)) == T(2)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(3)) == T(2)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(4)) == T(2)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(5)) == T(3)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(6)) == T(3)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(7)) == T(3)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(8)) == T(3)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(9)) == T(3)));                     \
    SST_TEST_BOOL((sst::ceil_sqrt(T(10)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(11)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(12)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(13)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(14)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(15)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(16)) == T(4)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(17)) == T(5)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(18)) == T(5)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(19)) == T(5)));                    \
    SST_TEST_BOOL((sst::ceil_sqrt(T(20)) == T(5)));                    \
  }())

    F((signed char));
    F((short));
    F((int));
    F((long));
    F((long long));
    F((unsigned char));
    F((unsigned short));
    F((unsigned int));
    F((unsigned long));
    F((unsigned long long));

#if SST_WITH_OPENSSL_CRYPTO
    F(sst::bignum);
#endif

    F((float));
    F((double));
    F((long double));

#undef F

    //------------------------------------------------------------------

#define F(T)                                                           \
  ([&]() {                                                             \
    SST_TEST_BOOL((sst::ceil_sqrt(T(1928894012)) == T(43920)));        \
    SST_TEST_BOOL((sst::ceil_sqrt(T(445115245)) == T(21098)));         \
  }())

    F((long));
    F((long long));
    F((unsigned long));
    F((unsigned long long));

#if SST_WITH_OPENSSL_CRYPTO
    F(sst::bignum);
#endif

    F((float));
    F((double));
    F((long double));

#undef F

    //------------------------------------------------------------------

    {
      auto const n = (sst::value_bits<int>::value - 1) / 2 * 2;
      SST_TEST_BOOL(
          (sst::ceil_sqrt((1 << n) - 1) == (1 << (n / 2)) + 0));
      SST_TEST_BOOL(
          (sst::ceil_sqrt((1 << n) + 0) == (1 << (n / 2)) + 0));
      SST_TEST_BOOL(
          (sst::ceil_sqrt((1 << n) + 1) == (1 << (n / 2)) + 1));
    }

    //------------------------------------------------------------------
  });
}
