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
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
// Include twice to test idempotence.
#include <sst/catalog/openssl/evp_cipher_ctx.hpp>
//

#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/openssl/evp_cipher_type.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/to_hex.hpp>

int main() {
  return sst::test_main([]() {
    ;

    //------------------------------------------------------------------

    // TODO: Use sst::from_hex once it exists.

    {
      std::vector<unsigned char> key;
      std::vector<unsigned char> iv;
      std::vector<unsigned char> src;
      std::vector<unsigned char> ct;
      std::vector<unsigned char> dst;
      sst::openssl::evp_cipher_ctx ctx;
      SST_TEST_BOOL(
          (key = std::vector<unsigned char>{0x2B,
                                            0x7E,
                                            0x15,
                                            0x16,
                                            0x28,
                                            0xAE,
                                            0xD2,
                                            0xA6,
                                            0xAB,
                                            0xF7,
                                            0x15,
                                            0x88,
                                            0x09,
                                            0xCF,
                                            0x4F,
                                            0x3C},
           iv = std::vector<unsigned char>{0xF0,
                                           0xF1,
                                           0xF2,
                                           0xF3,
                                           0xF4,
                                           0xF5,
                                           0xF6,
                                           0xF7,
                                           0xF8,
                                           0xF9,
                                           0xFA,
                                           0xFB,
                                           0xFC,
                                           0xFD,
                                           0xFE,
                                           0xFF},
           src = std::vector<unsigned char>{0x6B,
                                            0xC1,
                                            0xBE,
                                            0xE2,
                                            0x2E,
                                            0x40,
                                            0x9F,
                                            0x96,
                                            0xE9,
                                            0x3D,
                                            0x7E,
                                            0x11,
                                            0x73,
                                            0x93,
                                            0x17,
                                            0x2A},
           ct = std::vector<unsigned char>{0x87,
                                           0x4D,
                                           0x61,
                                           0x91,
                                           0xB6,
                                           0x20,
                                           0xE3,
                                           0x26,
                                           0x1B,
                                           0xEF,
                                           0x68,
                                           0x64,
                                           0x99,
                                           0x0D,
                                           0xB6,
                                           0xCE},
           dst = std::vector<unsigned char>(16),
           ctx = sst::openssl::evp_cipher_ctx(),
           ctx.init(sst::openssl::evp_cipher_type::aes_128_ctr,
                    key.data(),
                    iv.data()),
           ctx.update(src.data(), src.size(), dst.data()),
           ctx.finish(),
           dst == ct),
          SST_TEST_SHOW((sst::to_hex(dst))));
    }

    //------------------------------------------------------------------
  });
}
