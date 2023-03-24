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
#include <sst/catalog/bit_scan_reverse.hpp>
// Include twice to test idempotence.
#include <sst/catalog/bit_scan_reverse.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/value_bits.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define F(a, b)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::bit_scan_reverse(a) == (b)),                   \
                  SST_TEST_SHOW((sst::bit_scan_reverse(a))));          \
    SST_TEST_BOOL((std::is_same<decltype(sst::bit_scan_reverse(a)),    \
                                decltype(b)>::value));                 \
    SST_TEST_BOOL(                                                     \
        (sst::guts::bit_scan_reverse::fundamental_fallback(a) == (b)), \
        SST_TEST_SHOW(                                                 \
            (sst::guts::bit_scan_reverse::fundamental_fallback(a))));  \
    SST_TEST_BOOL((std::is_same<decltype(sst::guts::bit_scan_reverse:: \
                                             fundamental_fallback(a)), \
                                decltype(b)>::value));                 \
  }())

    F(true, false);
    F(static_cast<unsigned char>(2), static_cast<unsigned char>(1));
    F(static_cast<unsigned char>(3), static_cast<unsigned char>(1));
    F(static_cast<unsigned char>(4), static_cast<unsigned char>(2));
    F(-1, static_cast<int>(sst::value_bits<int>::value));

#undef F

    //------------------------------------------------------------------
  });
}
