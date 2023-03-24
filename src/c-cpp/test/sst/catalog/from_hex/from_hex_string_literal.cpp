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
#include <sst/catalog/from_hex.hpp>
// Include twice to test idempotence.
#include <sst/catalog/from_hex.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/to_hex.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

    {

      std::vector<unsigned char> dst;

      SST_TEST_BOOL((dst = sst::from_hex(""),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("0"),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("A"),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("a"),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("0x0"),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("0xA"),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("0xa"),
                     dst == std::vector<unsigned char>{}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

    } //

    //------------------------------------------------------------------

    if (sst::char_bit_v == 8) {

      std::vector<unsigned char> dst;

      SST_TEST_BOOL((dst = sst::from_hex("0123456789ABCDEF"),
                     dst
                         == std::vector<unsigned char>{0x01,
                                                       0x23,
                                                       0x45,
                                                       0x67,
                                                       0x89,
                                                       0xAB,
                                                       0xCD,
                                                       0xEF}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL((dst = sst::from_hex("0123456789abcdef"),
                     dst
                         == std::vector<unsigned char>{0x01,
                                                       0x23,
                                                       0x45,
                                                       0x67,
                                                       0x89,
                                                       0xAB,
                                                       0xCD,
                                                       0xEF}),
                    SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL(
          (dst = sst::from_hex("0'1'2'3'4'5'6'7'8'9'A'B'C'D'E'F"),
           dst
               == std::vector<unsigned char>{0x01,
                                             0x23,
                                             0x45,
                                             0x67,
                                             0x89,
                                             0xAB,
                                             0xCD,
                                             0xEF}),
          SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL(
          (dst = sst::from_hex("0x0'1'2'3'4'5'6'7'8'9'A'B'C'D'E'F"),
           dst
               == std::vector<unsigned char>{0x01,
                                             0x23,
                                             0x45,
                                             0x67,
                                             0x89,
                                             0xAB,
                                             0xCD,
                                             0xEF}),
          SST_TEST_SHOW((sst::to_hex(dst))));

      SST_TEST_BOOL(
          (dst = sst::from_hex("0X0'1'2'3'4'5'6'7'8'9'A'B'C'D'E'F"),
           dst
               == std::vector<unsigned char>{0x01,
                                             0x23,
                                             0x45,
                                             0x67,
                                             0x89,
                                             0xAB,
                                             0xCD,
                                             0xEF}),
          SST_TEST_SHOW((sst::to_hex(dst))));

    } //

    //------------------------------------------------------------------
  });
}
