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
#include <sst/catalog/os2ip.hpp>
// Include twice to test idempotence.
#include <sst/catalog/os2ip.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    SST_TEST_BOOL((sst::os2ip<int>(std::vector<unsigned char>{}) == 0));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{0}) == 0));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{1}) == 1));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{2}) == 2));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{254}) == 254));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{255}) == 255));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{0, 0}) == 0));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{1, 0}) == 256));
    SST_TEST_BOOL(
        (sst::os2ip<int>(std::vector<unsigned char>{1, 1}) == 257));

    //------------------------------------------------------------------
  });
}
