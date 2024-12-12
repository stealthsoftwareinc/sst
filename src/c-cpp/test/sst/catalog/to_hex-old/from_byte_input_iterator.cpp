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
#include <sst/catalog/to_hex.hpp>
// Include twice to test idempotence.
#include <sst/catalog/to_hex.hpp>
//

#include <iterator>
#include <string>
#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/to_hex_options.hpp>

int main() {
  return sst::test_main([]() {
    ;

    //------------------------------------------------------------------

    if (sst::char_bit_v == 8) {
      unsigned char src;
      std::string dst;
      SST_TEST_BOOL(
          (src = static_cast<unsigned char>(0x1A),
           dst = std::string(),
           sst::to_hex(&src, &src + 1, std::back_inserter(dst)),
           src == 0x1A && dst == "1A"),
          SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::vector<unsigned char> src;
      std::string dst;
      SST_TEST_BOOL((src = std::vector<unsigned char>{1, 2, 3},
                     dst = std::string(),
                     dst = sst::to_hex(src.begin(), src.end()),
                     dst == "010203"),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string dst;
      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex("Stealth"),
                     dst == "537465616C7468"),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string dst;
      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               "Stealth",
               sst::to_hex_options().prefix(true).uppercase_digits(
                   false)),
           dst == "0x537465616c7468"),
          SST_TEST_SHOW((dst)));
    }

    //------------------------------------------------------------------
  });
}
