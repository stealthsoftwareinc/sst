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
#include <sst/catalog/varint_size.hpp>
// Include twice to test idempotence.
#include <sst/catalog/varint_size.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

    if (sst::char_bit_v == 8) {

#define F(a, b)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::varint_size(a) == (b)),                        \
                  SST_TEST_SHOW((sst::varint_size(a))));               \
    SST_TEST_BOOL((std::is_same<decltype(sst::varint_size(a)),         \
                                decltype(b)>::value));                 \
  }())

      F(0, 1);
      F(1, 1);
      F(2, 1);
      F(3, 1);
      F(61, 1);
      F(62, 1);
      F(63, 1);
      F(64, 2);
      F(65, 2);
      F(66, 2);
      F(67, 2);
      F(125, 2);
      F(126, 2);
      F(127, 2);
      F(128, 2);
      F(129, 2);
      F(130, 2);
      F(131, 2);
      F(-1, 1);
      F(-2, 1);
      F(-3, 1);
      F(-62, 1);
      F(-63, 1);
      F(-64, 1);
      F(-65, 2);
      F(-66, 2);
      F(-67, 2);
      F(-68, 2);
      F(-126, 2);
      F(-127, 2);
      F(-128, 2);
      F(-129, 2);
      F(-130, 2);
      F(-131, 2);
      F(-132, 2);

#undef F

    } //

    //------------------------------------------------------------------
  });
}
