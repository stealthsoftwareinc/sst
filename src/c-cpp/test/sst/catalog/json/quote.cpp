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
#include <sst/catalog/json/quote.hpp>
// Include twice to test idempotence.
#include <sst/catalog/json/quote.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/json/quote_options.hpp>
#include <sst/catalog/malformed_code_point.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/text_encoding.hpp>

int main() {
  return sst::test_main([&] {
    ;

    //------------------------------------------------------------------

#define F(A, B)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL((sst::json::quote(                                   \
                       A,                                              \
                       sst::json::quote_options()                      \
                           .src_encoding<sst::text_encoding::utf_8>()) \
                   == B));                                             \
  }())

    F("", "\"\"");
    F("/", "\"\\/\"");
    F("\"", "\"\\\"\"");
    F("\\", "\"\\\\\"");
    F("\b", "\"\\b\"");
    F("\f", "\"\\f\"");
    F("\n", "\"\\n\"");
    F("\r", "\"\\r\"");
    F("\t", "\"\\t\"");
    F("x", "\"x\"");

#undef F

    // A partial code point at the end of an iterable with no sentinel
    // should be rejected with the default malformed_code_point_action.
    {
      std::vector<unsigned char> v;
      SST_TEST_THROW(
          (v = std::vector<unsigned char>({0xC0}),
           sst::json::quote(
               v,
               sst::json::quote_options()
                   .src_encoding<sst::text_encoding::utf_8>())),
          sst::malformed_code_point);
    }

    // A partial code point at the end of an iterable with a sentinel
    // should be rejected with the default malformed_code_point_action.
    {
      std::vector<unsigned char> v;
      SST_TEST_THROW(
          (v = std::vector<unsigned char>({0xC0, 0x00}),
           sst::json::quote(
               v,
               sst::json::quote_options()
                   .allow_zero<false>()
                   .src_encoding<sst::text_encoding::utf_8>())),
          sst::malformed_code_point);
    }

    //------------------------------------------------------------------
  });
}
