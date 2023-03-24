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
#include <sst/catalog/code_point_encoder_t.hpp>
// Include twice to test idempotence.
#include <sst/catalog/code_point_encoder_t.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/text_encoding.hpp>

int main() {
  return sst::test_main([&] {
    ;

    //------------------------------------------------------------------

    {

      using encoder_t =
          sst::code_point_encoder_t<sst::text_encoding::utf_16>;
      using code_unit_t = encoder_t::code_unit_t;

      encoder_t encoder;
      std::vector<code_unit_t> xs;

#define F(code_point, code_units)                                      \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (encoder =                                                     \
             sst::code_point_encoder_t<sst::text_encoding::utf_16>(),  \
         encoder.put(code_point),                                      \
         xs = std::vector<code_unit_t> code_units,                     \
         encoder.ready() && encoder.size() == (int)xs.size()           \
             && std::vector<code_unit_t>(encoder.get(),                \
                                         encoder.get()                 \
                                             + encoder.size())         \
                    == xs),                                            \
        SST_TEST_SHOW((encoder.ready())),                              \
        SST_TEST_SHOW((encoder.size())));                              \
  }())

      F(0x000000, ({0x0000}));
      F(0x000001, ({0x0001}));
      F(0x00D7FF, ({0xD7FF}));
      F(0x00D800, ({0xD800}));
      F(0x00D801, ({0xD801}));
      F(0x00DBFF, ({0xDBFF}));
      F(0x00DC00, ({0xDC00}));
      F(0x00DC01, ({0xDC01}));
      F(0x00FFFF, ({0xFFFF}));
      F(0x010000, ({0xD800, 0xDC00}));
      F(0x010001, ({0xD800, 0xDC01}));
      F(0x10FFFE, ({0xDBFF, 0xDFFE}));
      F(0x10FFFF, ({0xDBFF, 0xDFFF}));

#undef F

    } //

    //------------------------------------------------------------------
  });
}
