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
#include <sst/catalog/old/to_bytes.hpp>
// Include twice to test idempotence.
#include <sst/catalog/old/to_bytes.hpp>
//

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/buffer_overrun.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>
#include <vector>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    std::vector<unsigned char> dst;

    SST_TEST_BOOL((dst = std::vector<unsigned char>(1),
                   sst::old::to_bytes(0,
                                 dst.begin(),
                                 dst.size(),
                                 sst::integer_rep::twos_complement())
                           == dst.end()
                       && dst == std::vector<unsigned char>{0}));

    SST_TEST_BOOL((dst = std::vector<unsigned char>(1),
                   sst::old::to_bytes(1,
                                 dst.begin(),
                                 dst.size(),
                                 sst::integer_rep::twos_complement())
                           == dst.end()
                       && dst == std::vector<unsigned char>{1}));

    SST_TEST_BOOL(
        (dst = std::vector<unsigned char>(1),
         sst::old::to_bytes(-1,
                       dst.begin(),
                       dst.size(),
                       sst::integer_rep::twos_complement())
                 == dst.end()
             && dst == std::vector<unsigned char>{sst::uchar_max_v}));

    SST_TEST_THROW((dst = std::vector<unsigned char>(1),
                    sst::old::to_bytes(sst::uchar_msb_v,
                                  dst.begin(),
                                  dst.size(),
                                  sst::integer_rep::twos_complement())),
                   sst::buffer_overrun);

    SST_TEST_BOOL((dst = std::vector<unsigned char>(1),
                   sst::old::to_bytes((unsigned char)1,
                                 dst.begin(),
                                 dst.size(),
                                 sst::integer_rep::twos_complement())
                           == dst.end()
                       && dst == std::vector<unsigned char>{1}));

    SST_TEST_BOOL((dst = std::vector<unsigned char>(8),
                   sst::old::to_bytes(-4110874102405263360,
                                 dst.begin(),
                                 dst.size(),
                                 sst::integer_rep::twos_complement())
                           == dst.end()
                       && dst
                              == std::vector<unsigned char>{0x00,
                                                            0x10,
                                                            0xC8,
                                                            0xC1,
                                                            0xC8,
                                                            0x3D,
                                                            0xF3,
                                                            0xC6}));

    SST_TEST_BOOL((dst = std::vector<unsigned char>(8),
                   sst::old::to_bytes(1620536092634699,
                                 dst.begin(),
                                 dst.size(),
                                 sst::integer_rep::twos_complement())
                           == dst.end()
                       && dst
                              == std::vector<unsigned char>{0x4B,
                                                            0xAE,
                                                            0x25,
                                                            0x76,
                                                            0xDE,
                                                            0xC1,
                                                            0x05,
                                                            0x00}));

    //------------------------------------------------------------------
  });
}
