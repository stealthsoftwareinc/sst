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
#include <sst/catalog/c_quote.hpp>
// Include twice to test idempotence.
#include <sst/catalog/c_quote.hpp>
//

#include <string>
#include <vector>

#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define SST_F2(X)                                                      \
  ([] {                                                                \
    std::string dst;                                                   \
    SST_TEST_BOOL((dst = sst::c_quote(X), dst == #X),                  \
                  SST_TEST_SHOW(dst));                                 \
  }())

#define SST_F1(X)                                                      \
  ([] {                                                                \
    SST_F2(X);                                                         \
    SST_F2(L##X);                                                      \
    SST_F2(u##X);                                                      \
    SST_F2(U##X);                                                      \
    if (SST_CPP20_OR_LATER) {                                          \
      SST_F2(u8##X);                                                   \
    }                                                                  \
  }())

    SST_F1("");
    SST_F1("foo");
    SST_F1("\a\b\f\n\r\t\v\x1");

#undef SST_F1
#undef SST_F2

    //------------------------------------------------------------------

    {
      std::string dst;
      SST_TEST_BOOL((dst = sst::c_quote('\0'), dst == "\"\\x0\""),
                    SST_TEST_SHOW((dst)));
    }

    {
      std::vector<unsigned char> src;
      std::string dst;
      SST_TEST_BOOL((src = std::vector<unsigned char>{0},
                     dst = sst::c_quote(src),
                     dst == "\"\\x0\""),
                    SST_TEST_SHOW((dst)));
    }

    {
      std::string src;
      std::string dst;
      SST_TEST_BOOL((src = std::string(1, '\0'),
                     dst = sst::c_quote(src),
                     dst == "\"\""),
                    SST_TEST_SHOW((dst)));
    }

    //------------------------------------------------------------------
  });
}
