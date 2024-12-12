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
#include <sst/catalog/track_it.hpp>
// Include twice to test idempotence.
#include <sst/catalog/track_it.hpp>
//

#include <algorithm>
#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/count_it.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/wrap_it.hpp>

int main() {
  return sst::test_main([] {
    //------------------------------------------------------------------

    {

      std::vector<int> x;
      std::vector<int> y;
      std::vector<int> z;
      std::vector<int>::iterator src;
      std::vector<int>::iterator dst;
      int n;

      SST_TEST_BOOL(
          (x = {1, 2, 3},
           y = {0, 0, 0},
           z = {1, 2, 3},
           src = x.begin(),
           dst = y.begin(),
           std::copy(sst::track_it(src), sst::wrap_it(x.end()), dst),
           y == z && src == x.end()));

      SST_TEST_BOOL((x = {1, 2, 3},
                     y = {0, 0, 0},
                     z = {1, 2, 3},
                     src = x.begin(),
                     dst = y.begin(),
                     std::copy(sst::track_it(src),
                               sst::wrap_it(x.end()),
                               sst::track_it(dst)),
                     y == z && src == x.end() && dst == y.end()));

      SST_TEST_BOOL(
          (x = {1, 2, 3},
           y = {0, 0, 0},
           z = {1, 2, 0},
           src = x.begin(),
           dst = y.begin(),
           n = 2,
           std::copy(sst::track_it(src, n), sst::count_it(src, n), dst),
           y == z && src == x.begin() + n));

      SST_TEST_BOOL(
          (x = {1, 2, 3},
           y = {0, 0, 0},
           z = {1, 2, 0},
           src = x.begin(),
           dst = y.begin(),
           n = 2,
           std::copy(sst::track_it(src, n),
                     sst::count_it(src, n),
                     sst::track_it(dst)),
           y == z && src == x.begin() + n && dst == y.begin() + n));

    } //

    //------------------------------------------------------------------
  });
}
