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
#include <sst/catalog/min_rep_bits.hpp>
// Include twice to test idempotence.
#include <sst/catalog/min_rep_bits.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/is_same_mod_cvref.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>
#include <sst/catalog/width_bits.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define F(x, r)                                                        \
  ([] {                                                                \
    SST_TEST_BOOL((sst::min_rep_bits((x)) == (r)),                         \
                  SST_TEST_SHOW((sst::min_rep_bits((x)))));                \
    SST_TEST_BOOL(                                                     \
        (sst::is_same_mod_cvref<decltype(sst::min_rep_bits((x))),          \
                                decltype((r))>::value));               \
  }())

    F(false, true); // ...000000
    F(true, true); // ...111111

    F(-1, 1); // ...111111
    F(-2, 2); // ...111110
    F(-3, 3); // ...111101
    F(-4, 3); // ...111100
    F(-5, 4); // ...111011
    F(-6, 4); // ...111010
    F(-7, 4); // ...111001
    F(-8, 4); // ...111000
    F(-9, 5); // ...110111
    F(0, 1); // ...000000
    F(1, 2); // ...000001
    F(2, 3); // ...000010
    F(3, 3); // ...000011
    F(4, 4); // ...000100
    F(5, 4); // ...000101
    F(6, 4); // ...000110
    F(7, 4); // ...000111
    F(8, 5); // ...001000
    F(9, 5); // ...001001

    F(sst::type_max<int>::value / 1, sst::width_bits<int>::value - 0);
    F(sst::type_max<int>::value / 2, sst::width_bits<int>::value - 1);
    F(sst::type_max<int>::value / 4, sst::width_bits<int>::value - 2);
    F(sst::type_min<int>::value / 1, sst::width_bits<int>::value - 0);
    F(sst::type_min<int>::value / 2, sst::width_bits<int>::value - 1);
    F(sst::type_min<int>::value / 4, sst::width_bits<int>::value - 2);

#undef F

    //------------------------------------------------------------------
  });
}
