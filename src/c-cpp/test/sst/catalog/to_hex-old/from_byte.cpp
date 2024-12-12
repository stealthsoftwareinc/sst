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

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/ascii_lower.hpp>
#include <sst/catalog/char_bit_v.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/to_hex_options.hpp>

int main() {
  return sst::test_main([]() {
    ;

    //------------------------------------------------------------------

#define F(xx)                                                          \
  ([] {                                                                \
    std::string dst;                                                   \
    SST_TEST_BOOL(                                                     \
        (dst = std::string(),                                          \
         dst = sst::to_hex(static_cast<unsigned char>(0x##xx)),        \
         dst == #xx),                                                  \
        SST_TEST_SHOW((dst)));                                         \
    SST_TEST_BOOL(                                                     \
        (dst = std::string(),                                          \
         dst = sst::to_hex(static_cast<unsigned char>(0x##xx),         \
                           sst::to_hex_options()),                     \
         dst == #xx),                                                  \
        SST_TEST_SHOW((dst)));                                         \
    SST_TEST_BOOL((dst = std::string(),                                \
                   dst = sst::to_hex(                                  \
                       static_cast<unsigned char>(0x##xx),             \
                       sst::to_hex_options().uppercase_digits(false)), \
                   dst == sst::ascii_lower(#xx)),                      \
                  SST_TEST_SHOW((dst)));                               \
  }())
    //

    F(12);
    F(1A);

#undef F

    if (sst::char_bit_v == 8) {

      std::string dst;

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(static_cast<unsigned char>(0x00)),
           dst == "00"),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(static_cast<unsigned char>(0xA1)),
           dst == "A1"),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(static_cast<unsigned char>(0xAB),
                                       sst::to_hex_options().base(2)),
                     dst == "10101011"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(
                         static_cast<unsigned char>(0xAB),
                         sst::to_hex_options().base(2).prefix(true)),
                     dst == "0y10101011"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(static_cast<unsigned char>(0xAB),
                                       sst::to_hex_options()
                                           .base(2)
                                           .prefix(true)
                                           .uppercase_prefix(true)),
                     dst == "0Y10101011"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(2).prefix(true).prefix_char(
                   'b')),
           dst == "0b10101011"),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(2).prefix(true).prefix_char(
                   'B')),
           dst == "0B10101011"),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(static_cast<unsigned char>(0xAB),
                                       sst::to_hex_options().base(8)),
                     dst == "526"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(
                         static_cast<unsigned char>(0xAB),
                         sst::to_hex_options().base(8).prefix(true)),
                     dst == "0o526"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(static_cast<unsigned char>(0xAB),
                                       sst::to_hex_options()
                                           .base(8)
                                           .prefix(true)
                                           .uppercase_prefix(true)),
                     dst == "0O526"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(8).prefix(true).pad(true)),
           dst == "0o526====="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(8).prefix(true).pad(true).sep(
                   1)),
           dst == "0o5'2'6'='='='='="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(8).prefix(true).pad(true).sep(
                   2)),
           dst == "0o52'6='=='=="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(8).prefix(true).pad(true).sep(
                   3)),
           dst == "0o526'==='=="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(8).prefix(true).pad(true).sep(
                   4)),
           dst == "0o526='===="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(8).prefix(true).pad(true).sep(
                   5)),
           dst == "0o526=='==="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(static_cast<unsigned char>(0xAB),
                                       sst::to_hex_options().base(64)),
                     dst == "qw"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL((dst = std::string(),
                     dst = sst::to_hex(
                         static_cast<unsigned char>(0xAB),
                         sst::to_hex_options().base(64).prefix(true)),
                     dst == "0=qw"),
                    SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(64).prefix(true).prefix_char(
                   's')),
           dst == "0sqw"),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(64).prefix(true).prefix_char(
                   'S')),
           dst == "0Sqw"),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(static_cast<unsigned char>(0xAB),
                             sst::to_hex_options().base(64).pad(true)),
           dst == "qw=="),
          SST_TEST_SHOW((dst)));

      SST_TEST_BOOL(
          (dst = std::string(),
           dst = sst::to_hex(
               static_cast<unsigned char>(0xAB),
               sst::to_hex_options().base(64).prefix(true).pad(true)),
           dst == "0=qw=="),
          SST_TEST_SHOW((dst)));

    } //

    //------------------------------------------------------------------
  });
}
