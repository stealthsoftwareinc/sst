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
#include <sst/catalog/code_point_decoder_t.hpp>
// Include twice to test idempotence.
#include <sst/catalog/code_point_decoder_t.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/malformed_code_point.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/text_encoding.hpp>

namespace {

template<class Decoder, class Sequence>
void put(Decoder & d, Sequence const & xs) {
  for (auto const & x : xs) {
    d.put(x);
  }
}

} // namespace

int main() {
  return sst::test_main([&] {
    //------------------------------------------------------------------

    {

      sst::code_point_decoder_t<sst::text_encoding::utf_8> d;

      SST_TEST_BOOL(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           !d.ready() && d.index() == 0 && d.size() == 0),
          SST_TEST_SHOW((d.ready())),
          SST_TEST_SHOW((d.index())),
          SST_TEST_SHOW((d.size())),
          SST_TEST_SHOW((d.get())));

      SST_TEST_THROW(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           d.put(0x80)),
          sst::malformed_code_point);

      SST_TEST_THROW(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           d.put(0x81)),
          sst::malformed_code_point);

      SST_TEST_THROW(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           d.put(0xBE)),
          sst::malformed_code_point);

      SST_TEST_THROW(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           d.put(0xBF)),
          sst::malformed_code_point);

      SST_TEST_BOOL(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           d.put(0xC0),
           !d.ready() && d.index() == 1 && d.size() == 2),
          SST_TEST_SHOW((d.ready())),
          SST_TEST_SHOW((d.index())),
          SST_TEST_SHOW((d.size())),
          SST_TEST_SHOW((d.get())));

      SST_TEST_THROW(
          (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),
           d.put(0xC0),
           d.put(0x00)),
          sst::malformed_code_point);

    } //

    //------------------------------------------------------------------
    // Well-formed code points
    //------------------------------------------------------------------

#define F(code_units, code_point)                                      \
  ([&] {                                                               \
    SST_TEST_BOOL(                                                     \
        (d = sst::code_point_decoder_t<sst::text_encoding::utf_8>(),   \
         xs = std::vector<int> code_units,                             \
         put(d, xs),                                                   \
         d.ready() && d.index() == 0 && d.size() == (int)xs.size()     \
             && d.get() == code_point##U),                             \
        SST_TEST_SHOW((d.ready())),                                    \
        SST_TEST_SHOW((d.index())),                                    \
        SST_TEST_SHOW((d.size())),                                     \
        SST_TEST_SHOW((d.get())));                                     \
  }())

    {

      sst::code_point_decoder_t<sst::text_encoding::utf_8> d;
      std::vector<int> xs;

      F(({0x00}), 0x0000);
      F(({0x01}), 0x0001);
      F(({0x7E}), 0x007E);
      F(({0x7F}), 0x007F);
      F(({0xC0, 0x80}), 0x0000);
      F(({0xC0, 0x81}), 0x0001);
      F(({0xDF, 0xBE}), 0x07FE);
      F(({0xDF, 0xBF}), 0x07FF);
      F(({0xE0, 0x80, 0x80}), 0x0000);
      F(({0xE0, 0x80, 0x81}), 0x0001);
      F(({0xE0, 0x81, 0x80}), 0x0040);
      F(({0xE0, 0x81, 0x81}), 0x0041);
      F(({0xEF, 0xBE, 0xBE}), 0xFFBE);
      F(({0xEF, 0xBF, 0xBE}), 0xFFFE);
      F(({0xEF, 0xBF, 0xBF}), 0xFFFF);
      F(({0xF0, 0x80, 0x80, 0x80}), 0x0000);
      F(({0xF0, 0x80, 0x80, 0x81}), 0x0001);
      F(({0xF0, 0x80, 0x81, 0x80}), 0x0040);
      F(({0xF0, 0x80, 0x81, 0x81}), 0x0041);
      F(({0xF0, 0x8F, 0xBF, 0xBF}), 0x0000FFFF);
      F(({0xF0, 0x90, 0x80, 0x80}), 0x00010000);
      F(({0xF7, 0xBF, 0xBF, 0xBF}), 0x001FFFFF);
      F(({0xF8, 0x80, 0x80, 0x80, 0x80}), 0x00000000);
      F(({0xF8, 0x80, 0x80, 0x80, 0x81}), 0x00000001);
      F(({0xFB, 0xBF, 0xBF, 0xBF, 0xBE}), 0x03FFFFFE);
      F(({0xFB, 0xBF, 0xBF, 0xBF, 0xBF}), 0x03FFFFFF);
      F(({0xFC, 0x80, 0x80, 0x80, 0x80, 0x80}), 0x00000000);
      F(({0xFC, 0x80, 0x80, 0x80, 0x80, 0x81}), 0x00000001);
      F(({0xFC, 0x80, 0x80, 0x80, 0x81, 0x80}), 0x00000040);
      F(({0xFC, 0x80, 0x80, 0x80, 0x81, 0x81}), 0x00000041);
      F(({0xFD, 0xBF, 0xBF, 0xBF, 0xBF, 0xBE}), 0x7FFFFFFE);
      F(({0xFD, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF}), 0x7FFFFFFF);

    } //

#undef F

    //------------------------------------------------------------------
  });
}
