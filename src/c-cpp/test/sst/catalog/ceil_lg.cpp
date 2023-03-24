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
#include <sst/catalog/ceil_lg.hpp>
// Include twice to test idempotence.
#include <sst/catalog/ceil_lg.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/value_bits.hpp>
#include <sst/config.h>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    SST_TEST_BOOL((sst::ceil_lg(true) == false));

    //------------------------------------------------------------------

#define F(T)                                                           \
  ([&]() {                                                             \
    SST_TEST_BOOL((sst::ceil_lg(T(1)) == T(0)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(1))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(2)) == T(1)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(2))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(3)) == T(2)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(3))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(4)) == T(2)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(4))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(5)) == T(3)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(5))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(6)) == T(3)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(6))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(7)) == T(3)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(7))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(8)) == T(3)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(8))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(9)) == T(4)),                        \
                  SST_TEST_SHOW(sst::ceil_lg(T(9))));                  \
    SST_TEST_BOOL((sst::ceil_lg(T(10)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(10))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(11)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(11))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(12)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(12))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(13)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(13))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(14)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(14))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(15)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(15))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(16)) == T(4)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(16))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(17)) == T(5)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(17))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(18)) == T(5)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(18))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(19)) == T(5)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(19))));                 \
    SST_TEST_BOOL((sst::ceil_lg(T(20)) == T(5)),                       \
                  SST_TEST_SHOW(sst::ceil_lg(T(20))));                 \
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
    SST_TEST_BOOL((sst::ceil_lg(T(1928894012)) == T(31)),              \
                  SST_TEST_SHOW(sst::ceil_lg(T(1928894012))));         \
    SST_TEST_BOOL((sst::ceil_lg(T(445115245)) == T(29)),               \
                  SST_TEST_SHOW(sst::ceil_lg(T(445115245))));          \
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
  });
}
