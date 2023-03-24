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
#include <sst/catalog/to_string.hpp>
// Include twice to test idempotence.
#include <sst/catalog/to_string.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/integer_to_string_options.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    {
      std::string s;
      SST_TEST_BOOL((s = sst::to_string([] {
                       enum { a, b, c };
                       return a;
                     }()),
                     s == "0"),
                    SST_TEST_SHOW((s)));
    }

    {
      std::string s;
      SST_TEST_BOOL((s = sst::to_string([] {
                       enum { a, b, c };
                       return b;
                     }()),
                     s == "1"),
                    SST_TEST_SHOW((s)));
    }

    {
      std::string s;
      SST_TEST_BOOL((s = sst::to_string([] {
                       enum { a, b, c };
                       return c;
                     }()),
                     s == "2"),
                    SST_TEST_SHOW((s)));
    }

    {
      std::string s;
      SST_TEST_BOOL(
          (s = sst::to_string(
               [] {
                 enum { a, b, c };
                 return a;
               }(),
               sst::integer_to_string_options().base(16).prefix(true)),
           s == "0x0"),
          SST_TEST_SHOW((s)));
    }

    {
      std::string s;
      SST_TEST_BOOL(
          (s = sst::to_string(
               [] {
                 enum { a, b, c };
                 return b;
               }(),
               sst::integer_to_string_options().base(16).prefix(true)),
           s == "0x1"),
          SST_TEST_SHOW((s)));
    }

    {
      std::string s;
      SST_TEST_BOOL(
          (s = sst::to_string(
               [] {
                 enum { a, b, c };
                 return c;
               }(),
               sst::integer_to_string_options().base(16).prefix(true)),
           s == "0x2"),
          SST_TEST_SHOW((s)));
    }

    //------------------------------------------------------------------
  });
}
