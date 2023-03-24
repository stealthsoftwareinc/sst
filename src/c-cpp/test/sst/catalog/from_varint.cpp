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
#include <sst/catalog/from_varint.hpp>
// Include twice to test idempotence.
#include <sst/catalog/from_varint.hpp>
//

#include <stdexcept>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/from_hex.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

    if (sst::char_bit_v == 8) {

      //----------------------------------------------------------------

      {

        bool x;

        SST_TEST_BOOL(
            (x = sst::from_varint<bool>(sst::from_hex("0y00000000")),
             x == false),
            SST_TEST_SHOW((x)));

        SST_TEST_BOOL(
            (x = sst::from_varint<bool>(sst::from_hex("0y00000001")),
             x == true),
            SST_TEST_SHOW((x)));

        SST_TEST_THROW(
            (sst::from_varint<bool>(sst::from_hex("0y00000010"))),
            std::overflow_error);

      } //

      //----------------------------------------------------------------

#define F(aa, bb)                                                      \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (sst::from_varint<decltype(aa)>(sst::from_hex(bb)) == aa),     \
        SST_TEST_SHOW(                                                 \
            (sst::from_varint<decltype(aa)>(sst::from_hex(bb)))));     \
  }())

      F(0, "0y00000000");
      F(1, "0y00000001");
      F(2, "0y00000010");
      F(3, "0y00000011");
      F(61, "0y00111101");
      F(62, "0y00111110");
      F(63, "0y00111111");
      F(64, "0y11000000'00000000");
      F(65, "0y11000001'00000000");
      F(66, "0y11000010'00000000");
      F(67, "0y11000011'00000000");
      F(125, "0y11111101'00000000");
      F(126, "0y11111110'00000000");
      F(127, "0y11111111'00000000");
      F(128, "0y10000000'00000001");
      F(129, "0y10000001'00000001");
      F(130, "0y10000010'00000001");
      F(131, "0y10000011'00000001");
      F(-1, "0y01111111");
      F(-2, "0y01111110");
      F(-3, "0y01111101");
      F(-62, "0y01000010");
      F(-63, "0y01000001");
      F(-64, "0y01000000");
      F(-65, "0y10111111'01111111");
      F(-66, "0y10111110'01111111");
      F(-67, "0y10111101'01111111");
      F(-68, "0y10111100'01111111");
      F(-126, "0y10000010'01111111");
      F(-127, "0y10000001'01111111");
      F(-128, "0y10000000'01111111");
      F(-129, "0y11111111'01111110");
      F(-130, "0y11111110'01111110");
      F(-131, "0y11111101'01111110");
      F(-132, "0y11111100'01111110");

#undef F

    } //

    //------------------------------------------------------------------
  });
}
