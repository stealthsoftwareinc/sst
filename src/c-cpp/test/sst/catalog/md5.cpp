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
#include <sst/catalog/md5.hpp>
// Include twice to test idempotence.
#include <sst/catalog/md5.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/test_skip.hpp>
#include <sst/catalog/to_hex.hpp>

int main() {
  return sst::test_main([] {
    ;

#if SST_FT_cpp_sst_md5

    //------------------------------------------------------------------
    //
    // MD5 test vectors from IETF RFC 1321 Section A.5
    // (<https://www.ietf.org/rfc/rfc1321.txt>).
    //

#define SST_F(a, b)                                                    \
  ([] {                                                                \
    std::string y;                                                     \
    SST_TEST_BOOL((y = sst::to_hex(sst::md5(a)), y == b),              \
                  SST_TEST_SHOW(y));                                   \
  }())

    SST_F("", "D41D8CD98F00B204E9800998ECF8427E");
    SST_F("a", "0CC175B9C0F1B6A831C399E269772661");
    SST_F("abc", "900150983CD24FB0D6963F7D28E17F72");
    SST_F("message digest", "F96B697D7CB7938D525A2F31AAF161D0");
    SST_F("abcdefghijklmnopqrstuvwxyz",
          "C3FCD3D76192E4007DFB496CCA67E13B");
    SST_F("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567"
          "89",
          "D174AB98D277D9F5A5611C2C9F419D9F");
    SST_F("123456789012345678901234567890123456789012345678901234567890"
          "12345678901234567890",
          "57EDF4A22BE3C955AC49DA2E2107B67A");

#undef SST_F

    //------------------------------------------------------------------

#else
    throw sst::test_skip();
#endif

    //------------------------------------------------------------------
  });
}
