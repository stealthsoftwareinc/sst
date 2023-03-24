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
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <stdexcept>
#include <vector>

int main() {
  return sst::test_main([] {
    //------------------------------------------------------------------
    // Two's complement
    //------------------------------------------------------------------

    SST_TEST_BOOL(
        sst::bignum(0).num_bytes(sst::integer_rep::twos_complement())
        == 1);

    SST_TEST_BOOL(
        sst::bignum(1).num_bytes(sst::integer_rep::twos_complement())
        == 1);

    SST_TEST_BOOL(sst::bignum(sst::uchar_msb_v - 1)
                      .num_bytes(sst::integer_rep::twos_complement())
                  == 1);

    SST_TEST_BOOL(sst::bignum(sst::uchar_msb_v)
                      .num_bytes(sst::integer_rep::twos_complement())
                  == 2);

    SST_TEST_BOOL(sst::bignum(sst::uchar_max_v)
                      .num_bytes(sst::integer_rep::twos_complement())
                  == 2);

    SST_TEST_BOOL(
        sst::bignum(-1).num_bytes(sst::integer_rep::twos_complement())
        == 1);

    SST_TEST_BOOL((-sst::bignum(sst::uchar_msb_v))
                      .num_bytes(sst::integer_rep::twos_complement())
                  == 1);

    SST_TEST_BOOL((-sst::bignum(sst::uchar_msb_v + 1))
                      .num_bytes(sst::integer_rep::twos_complement())
                  == 2);

    SST_TEST_BOOL((-sst::bignum(sst::uchar_max_v))
                      .num_bytes(sst::integer_rep::twos_complement())
                  == 2);

    //------------------------------------------------------------------
    // Pure unsigned
    //------------------------------------------------------------------

    SST_TEST_BOOL(
        sst::bignum(0).num_bytes(sst::integer_rep::pure_unsigned())
        == 1);

    SST_TEST_BOOL(sst::bignum(sst::uchar_msb_v - 1)
                      .num_bytes(sst::integer_rep::pure_unsigned())
                  == 1);

    SST_TEST_BOOL(sst::bignum(sst::uchar_msb_v)
                      .num_bytes(sst::integer_rep::pure_unsigned())
                  == 1);

    SST_TEST_BOOL(sst::bignum(sst::uchar_msb_v + 1)
                      .num_bytes(sst::integer_rep::pure_unsigned())
                  == 1);

    SST_TEST_BOOL(sst::bignum(sst::uchar_max_v)
                      .num_bytes(sst::integer_rep::pure_unsigned())
                  == 1);

    SST_TEST_BOOL((sst::bignum(sst::uchar_max_v) + 1)
                      .num_bytes(sst::integer_rep::pure_unsigned())
                  == 2);

    //------------------------------------------------------------------
  });
}

#else // !SST_WITH_OPENSSL_CRYPTO

#include <sst/catalog/test_skip.hpp>

int main() {
  return sst::test_skip();
}

#endif // !SST_WITH_OPENSSL_CRYPTO
