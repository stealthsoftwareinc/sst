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
#include <sst/catalog/bignum.hpp>
// Include twice to test idempotence.
#include <sst/catalog/bignum.hpp>
//

#include <sst/config.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    //------------------------------------------------------------------

    ; // clang-format may behave weirdly without a statement here.

#define F(a, r)                                                        \
  ([&]() {                                                             \
    SST_TEST_BOOL(sst::bignum::abs((a)) == (r));                       \
    SST_TEST_BOOL(abs(sst::bignum((a))) == (r));                       \
    SST_TEST_BOOL(sst::bignum((a)).abs() == (r));                      \
  }())

    F(-5984652419019262415, 5984652419019262415);
    F(-1050715244575221994, 1050715244575221994);
    F(-1, 1);
    F(0, 0);
    F(1, 1);
    F(6528331063378222182, 6528331063378222182);
    F(7701431137861336424, 7701431137861336424);

#undef F

    //------------------------------------------------------------------
  });
}

#else // !SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/test_skip.hpp>

int main() {
  return sst::test_skip();
}

#endif // !SST_WITH_OPENSSL_CRYPTO
