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
#include <sst/catalog/str_cmp.hpp>
// Include twice to test idempotence.
#include <sst/catalog/str_cmp.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    int r;

#define F(x, op) SST_TEST_BOOL((r = x) op 0, SST_TEST_SHOW(r))

    F(sst::str_cmp("", ""), ==);
    F(sst::str_cmp("", "x"), <);
    F(sst::str_cmp("x", ""), >);
    F(sst::str_cmp("x", "x"), ==);
    F(sst::str_cmp("x", "y"), <);
    F(sst::str_cmp("y", "x"), >);

    F(sst::str_cmp(L"", L""), ==);
    F(sst::str_cmp(L"", L"x"), <);
    F(sst::str_cmp(L"x", L""), >);
    F(sst::str_cmp(L"x", L"x"), ==);
    F(sst::str_cmp(L"x", L"y"), <);
    F(sst::str_cmp(L"y", L"x"), >);

    {
      std::vector<int> x;
      std::vector<int> y;
      F((x = std::vector<int>{1, 2, 3, 4, 5, 6},
         y = std::vector<int>{1, 2, 3, 6, 5},
         sst::str_cmp(x.begin(), y.begin(), 3)),
        ==);
      F((x = std::vector<int>{1, 2, 3, 4, 5, 6},
         y = std::vector<int>{1, 2, 3, 6, 5},
         sst::str_cmp(x.begin(), y.begin(), 5)),
        <);
      F((x = std::vector<int>{1, 2, 3, 4, 5, 6},
         y = std::vector<int>{1, 2, 3, 6, 5},
         sst::str_cmp(x.begin(), y.begin(), 6)),
        >);
    }

#undef F

    //------------------------------------------------------------------
  });
}
