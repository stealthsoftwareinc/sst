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

#include <string>
#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/to_hex_options.hpp>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    {
      std::string dst;
      SST_TEST_BOOL((dst = sst::to_hex(""), dst == ""),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string dst;
      SST_TEST_BOOL((dst = sst::to_hex('\0'), dst == "00"),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string dst;
      SST_TEST_BOOL((dst = sst::to_hex("x"), dst == "78"),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::vector<unsigned char> src;
      std::string dst;
      SST_TEST_BOOL((src = std::vector<unsigned char>{0},
                     dst = sst::to_hex(src),
                     dst == "00"),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string src;
      std::string dst;
      SST_TEST_BOOL((src = std::string(1, '\0'),
                     dst = sst::to_hex(src),
                     dst == ""),
                    SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string dst;
      SST_TEST_BOOL(
          (dst = sst::to_hex("hello",
                             sst::to_hex_options().base(64).pad(true)),
           dst == "aGVsbG8="),
          SST_TEST_SHOW((dst)));
    }

    if (sst::char_bit_v == 8) {
      std::string dst;
      SST_TEST_BOOL(
          (dst = sst::to_hex(std::vector<unsigned char>{0, 0, 0},
                             sst::to_hex_options().base(64).pad(true)),
           dst == "AAAA"),
          SST_TEST_SHOW((dst)));
    }

    //------------------------------------------------------------------
  });
}
