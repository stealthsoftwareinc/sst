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
          sst::code_point_encoder_t<sst::text_encoding::utf_8>;
      using code_unit_t = encoder_t::code_unit_t;

      encoder_t encoder;
      std::vector<code_unit_t> xs;

#define F(code_point, code_units)                                      \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (encoder =                                                     \
             sst::code_point_encoder_t<sst::text_encoding::utf_8>(),   \
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

      F(0x00000000, ({0x00}));
      F(0x00000001, ({0x01}));
      F(0x0000007E, ({0x7E}));
      F(0x0000007F, ({0x7F}));
      F(0x00000080, ({0xC2, 0x80}));
      F(0x00000081, ({0xC2, 0x81}));
      F(0x000007FE, ({0xDF, 0xBE}));
      F(0x000007FF, ({0xDF, 0xBF}));
      F(0x00000800, ({0xE0, 0xA0, 0x80}));
      F(0x00000801, ({0xE0, 0xA0, 0x81}));
      F(0x0000FFFE, ({0xEF, 0xBF, 0xBE}));
      F(0x0000FFFF, ({0xEF, 0xBF, 0xBF}));
      F(0x00010000, ({0xF0, 0x90, 0x80, 0x80}));
      F(0x00010001, ({0xF0, 0x90, 0x80, 0x81}));
      F(0x001FFFFE, ({0xF7, 0xBF, 0xBF, 0xBE}));
      F(0x001FFFFF, ({0xF7, 0xBF, 0xBF, 0xBF}));
      F(0x00200000, ({0xF8, 0x88, 0x80, 0x80, 0x80}));
      F(0x00200001, ({0xF8, 0x88, 0x80, 0x80, 0x81}));
      F(0x03FFFFFE, ({0xFB, 0xBF, 0xBF, 0xBF, 0xBE}));
      F(0x03FFFFFF, ({0xFB, 0xBF, 0xBF, 0xBF, 0xBF}));
      F(0x04000000, ({0xFC, 0x84, 0x80, 0x80, 0x80, 0x80}));
      F(0x04000001, ({0xFC, 0x84, 0x80, 0x80, 0x80, 0x81}));
      F(0x7FFFFFFE, ({0xFD, 0xBF, 0xBF, 0xBF, 0xBF, 0xBE}));
      F(0x7FFFFFFF, ({0xFD, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF}));

#undef F

    } //

    //------------------------------------------------------------------
  });
}
