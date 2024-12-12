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

#undef SST_COMPILE_TIME_TESTS
#define SST_COMPILE_TIME_TESTS 1

// Include first to test independence.
#include <sst/catalog/overlap.hpp>
// Include twice to test idempotence.
#include <sst/catalog/overlap.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
    ;

    //------------------------------------------------------------------

#define F(p1, n1, p2, n2, b)                                           \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::overlap(p1, n1, p2, n2) == b));                \
    SST_TEST_BOOL((sst::overlap(p2, n2, p1, n1) == b));                \
  }())

    {
      unsigned char x[100];
      F(&x[0], 5, &x[0], 3, true);
      F(&x[0], 5, &x[2], 3, true);
      F(&x[0], 5, &x[4], 3, true);
      F(&x[0], 5, &x[5], 3, false);
      F(&x[0], 5, &x[0], 0, false);
      F(&x[0], 5, &x[1], 0, false);
      F(&x[0], 0, &x[0], 0, false);
      F(&x[0], 0, &x[0], 1, false);
    }

#undef F

    //------------------------------------------------------------------
  });
}
