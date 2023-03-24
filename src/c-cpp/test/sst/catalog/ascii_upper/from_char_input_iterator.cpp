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
#include <sst/catalog/ascii_upper.hpp>
// Include twice to test idempotence.
#include <sst/catalog/ascii_upper.hpp>
//

#include <iterator>
#include <string>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/cbegin.hpp>
#include <sst/catalog/cend.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
    ;

    //------------------------------------------------------------------

    {
      std::string src;
      std::string dst;
      SST_TEST_BOOL((src = std::string("Stealth"),
                     dst = std::string(),
                     sst::ascii_upper(sst::cbegin(src),
                                      sst::cend(src),
                                      std::back_inserter(dst)),
                     dst == "STEALTH"),
                    SST_TEST_SHOW((dst)));
    }

    {
      std::string dst;
      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::ascii_upper("Stealth"),
                     dst == "STEALTH"),
                    SST_TEST_SHOW((dst)));
    }

    //------------------------------------------------------------------
  });
}