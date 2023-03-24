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
#include <sst/catalog/old/from_bytes.hpp>
// Include twice to test idempotence.
#include <sst/catalog/old/from_bytes.hpp>
//

#include <stdexcept>
#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/buffer_underrun.hpp>
#include <sst/catalog/checked_overflow.hpp>
#include <sst/catalog/integer_rep.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/uchar_max_v.hpp>
#include <sst/catalog/uchar_msb_v.hpp>

int main() {
  return sst::test_main([]() {
    //------------------------------------------------------------------

    std::vector<unsigned char> buf;
    decltype(buf)::iterator src;
    decltype(buf)::size_type avail;

#define F3(SRC, T, REP, DST)                                           \
  ([&]() {                                                             \
    T dst;                                                             \
    SST_TEST_BOOL(                                                     \
        (buf = std::vector<unsigned char> SRC,                         \
         src = buf.begin(),                                            \
         avail = buf.size(),                                           \
         dst = sst::old::from_bytes<T>(&src, buf.size(), avail, REP),  \
         dst == static_cast<T>(DST) && src == buf.end()                \
             && avail == 0),                                           \
        SST_TEST_SHOW(dst),                                            \
        SST_TEST_SHOW(dst == static_cast<T>(DST)),                     \
        SST_TEST_SHOW(src == buf.end()),                               \
        SST_TEST_SHOW(avail),                                          \
        SST_TEST_SHOW(avail == 0));                                    \
  }())

#define F2(SRC, T, DST)                                                \
  ([&]() {                                                             \
    F3(SRC, T, sst::integer_rep::twos_complement(), DST);                \
    F3(SRC, T, sst::integer_rep::pure_unsigned(), DST);                  \
  }())

#define F(SRC, DST)                                                    \
  ([&]() {                                                             \
    F2(SRC, bool, DST);                                                \
    F2(SRC, signed char, DST);                                         \
    F2(SRC, short, DST);                                               \
    F2(SRC, int, DST);                                                 \
    F2(SRC, long, DST);                                                \
    F2(SRC, long long, DST);                                           \
    F2(SRC, unsigned char, DST);                                       \
    F2(SRC, unsigned short, DST);                                      \
    F2(SRC, unsigned int, DST);                                        \
    F2(SRC, unsigned long, DST);                                       \
    F2(SRC, unsigned long long, DST);                                  \
  }())

    F(({0}), 0);
    F(({0, 0}), 0);
    F(({0, 0, 0}), 0);
    F(({0, 0, 0, 0}), 0);
    F(({0, 0, 0, 0, 0}), 0);
    F(({0, 0, 0, 0, 0, 0}), 0);
    F(({0, 0, 0, 0, 0, 0, 0}), 0);
    F(({0, 0, 0, 0, 0, 0, 0, 0}), 0);
    F(({0, 0, 0, 0, 0, 0, 0, 0, 0}), 0);
    F(({0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 0);

    F(({1}), 1);
    F(({1, 0}), 1);
    F(({1, 0, 0}), 1);
    F(({1, 0, 0, 0}), 1);
    F(({1, 0, 0, 0, 0}), 1);
    F(({1, 0, 0, 0, 0, 0}), 1);
    F(({1, 0, 0, 0, 0, 0, 0}), 1);
    F(({1, 0, 0, 0, 0, 0, 0, 0}), 1);
    F(({1, 0, 0, 0, 0, 0, 0, 0, 0}), 1);
    F(({1, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 1);

#undef F
#define F(SRC, DST)                                                    \
  ([&]() {                                                             \
    F2(SRC, signed char, DST);                                         \
    F2(SRC, short, DST);                                               \
    F2(SRC, int, DST);                                                 \
    F2(SRC, long, DST);                                                \
    F2(SRC, long long, DST);                                           \
    F2(SRC, unsigned char, DST);                                       \
    F2(SRC, unsigned short, DST);                                      \
    F2(SRC, unsigned int, DST);                                        \
    F2(SRC, unsigned long, DST);                                       \
    F2(SRC, unsigned long long, DST);                                  \
  }())

    F(({2}), 2);
    F(({2, 0}), 2);
    F(({2, 0, 0}), 2);
    F(({2, 0, 0, 0}), 2);
    F(({2, 0, 0, 0, 0}), 2);
    F(({2, 0, 0, 0, 0, 0}), 2);
    F(({2, 0, 0, 0, 0, 0, 0}), 2);
    F(({2, 0, 0, 0, 0, 0, 0, 0}), 2);
    F(({2, 0, 0, 0, 0, 0, 0, 0, 0}), 2);
    F(({2, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 2);

    auto const schar_max = sst::type_max<signed char>::value;
    F(({schar_max}), schar_max);
    F(({schar_max, 0}), schar_max);
    F(({schar_max, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0, 0, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0, 0, 0, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0, 0, 0, 0, 0, 0}), schar_max);
    F(({schar_max, 0, 0, 0, 0, 0, 0, 0, 0, 0}), schar_max);

#undef F
#undef F2
#undef F3

    SST_TEST_BOOL((buf = std::vector<unsigned char>{1},
                   src = buf.begin(),
                   sst::old::from_bytes<unsigned char>(
                       &src,
                       buf.size(),
                       sst::integer_rep::pure_unsigned())
                           == 1
                       && src == buf.end()));

    SST_TEST_BOOL((buf = std::vector<unsigned char>{1, 0},
                   src = buf.begin(),
                   sst::old::from_bytes<unsigned char>(
                       &src,
                       buf.size(),
                       sst::integer_rep::pure_unsigned())
                           == 1
                       && src == buf.end()));

    SST_TEST_THROW((buf = std::vector<unsigned char>{1, 0},
                    src = buf.begin(),
                    avail = 1,
                    sst::old::from_bytes<unsigned char>(
                        src,
                        buf.size(),
                        avail,
                        sst::integer_rep::pure_unsigned())),
                   sst::buffer_underrun);

    SST_TEST_THROW((buf = std::vector<unsigned char>{sst::uchar_msb_v},
                    src = buf.begin(),
                    sst::old::from_bytes<signed char>(
                        &src,
                        buf.size(),
                        sst::integer_rep::pure_unsigned())),
                   sst::checked_overflow);

    SST_TEST_THROW((buf = std::vector<unsigned char>{1, 1},
                    src = buf.begin(),
                    sst::old::from_bytes<unsigned char>(
                        src,
                        buf.size(),
                        sst::integer_rep::pure_unsigned())),
                   sst::checked_overflow);

    SST_TEST_BOOL((buf = std::vector<unsigned char>{1},
                   src = buf.begin(),
                   avail = buf.size(),
                   sst::old::from_bytes<signed char>(
                       &src,
                       buf.size(),
                       avail,
                       sst::integer_rep::twos_complement())
                           == 1
                       && src == buf.end() && avail == 0));

    SST_TEST_BOOL((buf = std::vector<unsigned char>{sst::uchar_max_v},
                   src = buf.begin(),
                   avail = buf.size(),
                   sst::old::from_bytes<signed char>(
                       &src,
                       buf.size(),
                       avail,
                       sst::integer_rep::twos_complement())
                           == -1
                       && src == buf.end() && avail == 0));

    SST_TEST_BOOL(
        (buf = std::vector<unsigned char>{sst::uchar_max_v - 1},
         src = buf.begin(),
         avail = buf.size(),
         sst::old::from_bytes<signed char>(
             &src,
             buf.size(),
             avail,
             sst::integer_rep::twos_complement())
                 == -2
             && src == buf.end() && avail == 0));

    SST_TEST_BOOL((buf = std::vector<unsigned char>{sst::uchar_max_v,
                                                    sst::uchar_max_v},
                   src = buf.begin(),
                   avail = buf.size(),
                   sst::old::from_bytes<signed char>(
                       &src,
                       buf.size(),
                       avail,
                       sst::integer_rep::twos_complement())
                           == -1
                       && src == buf.end() && avail == 0));

    SST_TEST_BOOL(
        (buf = std::vector<unsigned char>{sst::uchar_max_v - 1,
                                          sst::uchar_max_v},
         src = buf.begin(),
         avail = buf.size(),
         sst::old::from_bytes<signed char>(
             &src,
             buf.size(),
             avail,
             sst::integer_rep::twos_complement())
                 == -2
             && src == buf.end() && avail == 0));

    SST_TEST_THROW(
        (buf = std::vector<unsigned char>{sst::uchar_max_v,
                                          sst::uchar_max_v - 1},
         src = buf.begin(),
         avail = buf.size(),
         sst::old::from_bytes<signed char>(
             &src,
             buf.size(),
             avail,
             sst::integer_rep::twos_complement())),
        sst::checked_overflow);

    SST_TEST_THROW(
        (buf = std::vector<unsigned char>{0, sst::uchar_msb_v},
         src = buf.begin(),
         avail = buf.size(),
         sst::old::from_bytes<signed char>(
             &src,
             buf.size(),
             avail,
             sst::integer_rep::twos_complement())),
        sst::checked_overflow);

    SST_TEST_BOOL((buf = std::vector<unsigned char>{0x4B,
                                                    0xAE,
                                                    0x25,
                                                    0x76,
                                                    0xDE,
                                                    0xC1,
                                                    0x05,
                                                    0x00},
                   src = buf.begin(),
                   avail = buf.size(),
                   sst::old::from_bytes<long long>(
                       &src,
                       buf.size(),
                       avail,
                       sst::integer_rep::twos_complement())
                           == 1620536092634699
                       && src == buf.end() && avail == 0));

    //------------------------------------------------------------------
  });
}
