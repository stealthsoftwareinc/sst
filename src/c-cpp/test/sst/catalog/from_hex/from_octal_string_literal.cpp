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
#include <sst/catalog/from_hex.hpp>
// Include twice to test idempotence.
#include <sst/catalog/from_hex.hpp>
//

#include <iterator>
#include <string>
#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/from_hex_exception.hpp>
#include <sst/catalog/from_hex_options.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/to_hex.hpp>
#include <sst/catalog/value_sentinel.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

#define F2(src, options, expected_dst)                                 \
  ([] {                                                                \
    std::vector<unsigned char> dst;                                    \
    SST_TEST_BOOL(                                                     \
        (dst = sst::from_hex(src, sst::from_hex_options() options),    \
         dst == std::vector<unsigned char> expected_dst),              \
        SST_TEST_SHOW((sst::to_hex(dst))));                            \
    SST_TEST_BOOL(                                                     \
        (dst =                                                         \
             sst::from_hex(&src[0], sst::from_hex_options() options),  \
         dst == std::vector<unsigned char> expected_dst),              \
        SST_TEST_SHOW((sst::to_hex(dst))));                            \
    SST_TEST_BOOL(                                                     \
        (dst = sst::from_hex(std::string(src),                         \
                             sst::from_hex_options() options),         \
         dst == std::vector<unsigned char> expected_dst),              \
        SST_TEST_SHOW((sst::to_hex(dst))));                            \
    SST_TEST_BOOL((dst = std::vector<unsigned char>(),                 \
                   sst::from_hex(src,                                  \
                                 std::back_inserter(dst),              \
                                 sst::from_hex_options() options),     \
                   dst == std::vector<unsigned char> expected_dst),    \
                  SST_TEST_SHOW((sst::to_hex(dst))));                  \
    SST_TEST_BOOL((dst = std::vector<unsigned char>(),                 \
                   sst::from_hex(&src[0],                              \
                                 sst::value_sentinel('\0'),            \
                                 std::back_inserter(dst),              \
                                 sst::from_hex_options() options),     \
                   dst == std::vector<unsigned char> expected_dst),    \
                  SST_TEST_SHOW((sst::to_hex(dst))));                  \
    SST_TEST_BOOL((dst = std::vector<unsigned char>(),                 \
                   sst::from_hex(std::string(src),                     \
                                 std::back_inserter(dst),              \
                                 sst::from_hex_options() options),     \
                   dst == std::vector<unsigned char> expected_dst),    \
                  SST_TEST_SHOW((sst::to_hex(dst))));                  \
  }())

#define F(src, options, expected_dst)                                  \
  ([] {                                                                \
    F2(src, options.base(8), expected_dst);                            \
    F2("0o" src, options.base(8), expected_dst);                       \
    F2("0O" src, options.base(8), expected_dst);                       \
  }())

#define G2(src, options)                                               \
  ([] {                                                                \
    std::vector<unsigned char> dst;                                    \
    SST_TEST_THROW(                                                    \
        (sst::from_hex((src), sst::from_hex_options() options)),       \
        sst::from_hex_exception);                                      \
    SST_TEST_THROW((dst = std::vector<unsigned char>(),                \
                    sst::from_hex((src),                               \
                                  std::back_inserter(dst),             \
                                  sst::from_hex_options() options)),   \
                   sst::from_hex_exception);                           \
  }())

#define G(src, options)                                                \
  ([] {                                                                \
    G2(src, options.base(8));                                          \
    G2("0o" src, options.base(8));                                     \
    G2("0O" src, options.base(8));                                     \
  }())

    F("", , ({}));
    F("0", , ({}));
    F("7", , ({}));
    F("04", , ({}));
    F("74", , ({}));
    F("74", , ({}));

    G("8", );

    if (sst::char_bit_v == 8) {

      F("01234567", , ({0x05, 0x39, 0x77}));
      F("76543210", , ({0xFA, 0xC6, 0x88}));
      F("0'1'2'3'4'5'6'7", , ({0x05, 0x39, 0x77}));
      F("7'6'5'4'3'2'1'0", , ({0xFA, 0xC6, 0x88}));

      F("526", , ({0xAB}));
      G("526=", );
      G("526==", );
      G("526===", );
      G("526====", );
      F("526=====", , ({0xAB}));
      F("5'2'6'='='='='=", , ({0xAB}));
      G("526======", );

      F("527", , ({0xAB}));
      G("527=", );
      G("527==", );
      G("527===", );
      G("527====", );
      F("527=====", , ({0xAB}));
      F("5'2'7'='='='='=", , ({0xAB}));
      G("527======", );

      G("528", );

      F("526=====324=====", , ({0xAB, 0x6A}));
      F("5'2'6'='='='='='3'2'4'='='='='=", , ({0xAB, 0x6A}));

      F("527=====325=====", , ({0xAB, 0x6A}));
      F("5'2'7'='='='='='3'2'5'='='='='=", , ({0xAB, 0x6A}));

    } //

#undef G
#undef G2
#undef F
#undef F2

    //------------------------------------------------------------------
  });
}
