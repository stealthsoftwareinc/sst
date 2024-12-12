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
#include <sst/catalog/checked_t.hpp>
// Include twice to test idempotence.
#include <sst/catalog/checked_t.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_THROW.hpp>
#include <sst/catalog/checked_overflow.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>

int main() {
  return sst::test_main([&] {
    ;

    constexpr auto int_min = sst::type_min<int>::value;
    constexpr auto int_max = sst::type_max<int>::value;

    using uint = unsigned int;
    constexpr auto uint_max = sst::type_max<uint>::value;

    //------------------------------------------------------------------

#define F(x, y)                                                        \
  ([&] {                                                               \
    SST_TEST_BOOL((x).value() == (y));                                 \
    SST_TEST_BOOL(                                                     \
        (std::is_same<sst::remove_cvref_t<decltype((x).value())>,      \
                      sst::remove_cvref_t<decltype((y))>>::value));    \
  }())

#define G(x, y) ([&] { SST_TEST_THROW((x), y); }())

    F(sst::checked_t<bool>(), false);
    G(sst::checked_t<bool>(-1), sst::checked_overflow);
    F(sst::checked_t<bool>(0), false);
    F(sst::checked_t<bool>(1), true);
    G(sst::checked_t<bool>(2), sst::checked_overflow);
    F(sst::checked_t<int>(), 0);
    F(sst::checked_t<int>(int_min), int_min);
    F(sst::checked_t<int>(int_min + 1), int_min + 1);
    F(sst::checked_t<int>(-2), -2);
    F(sst::checked_t<int>(-1), -1);
    F(sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(1), 1);
    F(sst::checked_t<int>(2), 2);
    F(sst::checked_t<int>(int_max - 1), int_max - 1);
    F(sst::checked_t<int>(int_max), int_max);
    G(sst::checked_t<uint>(-1), sst::checked_overflow);
    F(sst::checked_t<uint>(0), 0U);
    F(sst::checked_t<uint>(1), 1U);

    F(!sst::checked_t<bool>(), true);
    F(!sst::checked_t<bool>(0), true);
    F(!sst::checked_t<bool>(1), false);
    F(!sst::checked_t<int>(), true);
    F(!sst::checked_t<int>(-1), false);
    F(!sst::checked_t<int>(0), true);
    F(!sst::checked_t<int>(1), false);

    F(+sst::checked_t<int>(int_min), int_min);
    F(+sst::checked_t<int>(int_min + 1), int_min + 1);
    F(+sst::checked_t<int>(-2), -2);
    F(+sst::checked_t<int>(-1), -1);
    F(+sst::checked_t<int>(0), 0);
    F(+sst::checked_t<int>(1), 1);
    F(+sst::checked_t<int>(2), 2);
    F(+sst::checked_t<int>(int_max - 1), int_max - 1);
    F(+sst::checked_t<int>(int_max), int_max);

    F(-sst::checked_t<int>(int_min + 1), -(int_min + 1));
    F(-sst::checked_t<int>(-2), 2);
    F(-sst::checked_t<int>(-1), 1);
    F(-sst::checked_t<int>(0), 0);
    F(-sst::checked_t<int>(1), -1);
    F(-sst::checked_t<int>(2), -2);
    F(-sst::checked_t<int>(int_max - 1), -int_max + 1);
    F(-sst::checked_t<int>(int_max), -int_max);
    F(-sst::checked_t<uint>(0), 0U);
    G(-sst::checked_t<uint>(1), sst::checked_overflow);

    F(sst::checked_t<int>(2) * sst::checked_t<int>(3), 6);
    F(sst::checked_t<int>(2) * sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(0) * sst::checked_t<int>(3), 0);
    F(sst::checked_t<int>(0) * sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(-2) * sst::checked_t<int>(-3), 6);
    G(sst::checked_t<int>(int_max) * sst::checked_t<int>(-2),
      sst::checked_overflow);
    F(sst::checked_t<int>(int_max) * sst::checked_t<int>(-1), -int_max);
    F(sst::checked_t<int>(int_max) * sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(int_max) * sst::checked_t<int>(1), int_max);
    G(sst::checked_t<int>(int_max) * sst::checked_t<int>(2),
      sst::checked_overflow);
    G(sst::checked_t<int>(int_min) * sst::checked_t<int>(-2),
      sst::checked_overflow);
    F(sst::checked_t<int>(int_min) * sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(int_min) * sst::checked_t<int>(1), int_min);
    G(sst::checked_t<int>(int_min) * sst::checked_t<int>(2),
      sst::checked_overflow);
    F(sst::checked_t<uint>(2) * sst::checked_t<int>(3), 6U);
    G(sst::checked_t<uint>(1) * sst::checked_t<int>(-1),
      sst::checked_overflow);

    F(sst::checked_t<int>(0) / sst::checked_t<int>(-2), 0);
    F(sst::checked_t<int>(0) / sst::checked_t<int>(-1), 0);
    F(sst::checked_t<int>(0) / sst::checked_t<int>(1), 0);
    F(sst::checked_t<int>(0) / sst::checked_t<int>(2), 0);
    F(sst::checked_t<int>(1) / sst::checked_t<int>(1), 1);
    F(sst::checked_t<int>(1) / sst::checked_t<int>(2), 0);
    F(sst::checked_t<int>(3) / sst::checked_t<int>(1), 3);
    F(sst::checked_t<int>(3) / sst::checked_t<int>(2), 1);
    F(sst::checked_t<int>(3) / sst::checked_t<int>(3), 1);
    F(sst::checked_t<int>(3) / sst::checked_t<int>(4), 0);
    F(sst::checked_t<int>(int_min) / sst::checked_t<int>(1), int_min);

    F(sst::checked_t<int>(0) % sst::checked_t<int>(-2), 0);
    F(sst::checked_t<int>(0) % sst::checked_t<int>(-1), 0);
    F(sst::checked_t<int>(0) % sst::checked_t<int>(1), 0);
    F(sst::checked_t<int>(0) % sst::checked_t<int>(2), 0);
    F(sst::checked_t<int>(1) % sst::checked_t<int>(1), 0);
    F(sst::checked_t<int>(1) % sst::checked_t<int>(2), 1);
    F(sst::checked_t<int>(3) % sst::checked_t<int>(1), 0);
    F(sst::checked_t<int>(3) % sst::checked_t<int>(2), 1);
    F(sst::checked_t<int>(3) % sst::checked_t<int>(3), 0);
    F(sst::checked_t<int>(3) % sst::checked_t<int>(4), 3);
    F(sst::checked_t<int>(12) % sst::checked_t<int>(5), 2);
    F(sst::checked_t<int>(12) % sst::checked_t<int>(-5), 2);
    F(sst::checked_t<int>(-12) % sst::checked_t<int>(5), -2);
    F(sst::checked_t<int>(-12) % sst::checked_t<int>(-5), -2);
    F(sst::checked_t<int>(int_min) % sst::checked_t<int>(1), 0);

    F(sst::checked_t<int>(2) + sst::checked_t<int>(3), 5);
    F(sst::checked_t<int>(2) + sst::checked_t<int>(0), 2);
    F(sst::checked_t<int>(0) + sst::checked_t<int>(3), 3);
    F(sst::checked_t<int>(0) + sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(-2) + sst::checked_t<int>(-3), -5);
    F(sst::checked_t<int>(int_max) + sst::checked_t<int>(-2),
      int_max - 2);
    F(sst::checked_t<int>(int_max) + sst::checked_t<int>(-1),
      int_max - 1);
    F(sst::checked_t<int>(int_max) + sst::checked_t<int>(0), int_max);
    G(sst::checked_t<int>(int_max) + sst::checked_t<int>(1),
      sst::checked_overflow);
    G(sst::checked_t<int>(int_max) + sst::checked_t<int>(2),
      sst::checked_overflow);
    G(sst::checked_t<int>(int_min) + sst::checked_t<int>(-2),
      sst::checked_overflow);
    F(sst::checked_t<int>(int_min) + sst::checked_t<int>(0), int_min);
    F(sst::checked_t<int>(int_min) + sst::checked_t<int>(1),
      int_min + 1);
    F(sst::checked_t<int>(int_min) + sst::checked_t<int>(2),
      int_min + 2);
    F(sst::checked_t<uint>(2) + sst::checked_t<int>(3), 5U);
    G(sst::checked_t<uint>(1) + sst::checked_t<int>(-1),
      sst::checked_overflow);

    F(sst::checked_t<int>(2) - sst::checked_t<int>(3), -1);
    F(sst::checked_t<int>(2) - sst::checked_t<int>(0), 2);
    F(sst::checked_t<int>(0) - sst::checked_t<int>(3), -3);
    F(sst::checked_t<int>(0) - sst::checked_t<int>(0), 0);
    F(sst::checked_t<int>(-2) - sst::checked_t<int>(-3), 1);
    G(sst::checked_t<int>(int_max) - sst::checked_t<int>(-2),
      sst::checked_overflow);
    G(sst::checked_t<int>(int_max) - sst::checked_t<int>(-1),
      sst::checked_overflow);
    F(sst::checked_t<int>(int_max) - sst::checked_t<int>(0), int_max);
    F(sst::checked_t<int>(int_max) - sst::checked_t<int>(1),
      int_max - 1);
    F(sst::checked_t<int>(int_max) - sst::checked_t<int>(2),
      int_max - 2);
    F(sst::checked_t<int>(int_min) - sst::checked_t<int>(-2),
      int_min + 2);
    F(sst::checked_t<int>(int_min) - sst::checked_t<int>(0), int_min);
    G(sst::checked_t<int>(int_min) - sst::checked_t<int>(1),
      sst::checked_overflow);
    G(sst::checked_t<int>(int_min) - sst::checked_t<int>(2),
      sst::checked_overflow);
    G(sst::checked_t<uint>(2) - sst::checked_t<int>(3),
      sst::checked_overflow);
    G(sst::checked_t<uint>(1) - sst::checked_t<int>(-1),
      sst::checked_overflow);

    F(~sst::checked_t<uint>(0U), uint_max);
    F(~sst::checked_t<uint>(1U), uint_max - 1U);
    F(~sst::checked_t<uint>(2U), uint_max - 2U);
    F(~sst::checked_t<uint>(uint_max - 2U), 2U);
    F(~sst::checked_t<uint>(uint_max - 1U), 1U);
    F(~sst::checked_t<uint>(uint_max), 0U);

    F(sst::checked_t<uint>(0U) & sst::checked_t<uint>(1U), 0U);
    F(sst::checked_t<uint>(1U) & sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(2U) & sst::checked_t<uint>(1U), 0U);
    F(sst::checked_t<uint>(3U) & sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(3U) & sst::checked_t<uint>(2U), 2U);
    F(sst::checked_t<uint>(uint_max) & sst::checked_t<uint>(2U), 2U);
    F(sst::checked_t<uint>(uint_max) & sst::checked_t<uint>(3U), 3U);

    F(sst::checked_t<uint>(0U) | sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(1U) | sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(2U) | sst::checked_t<uint>(1U), 3U);
    F(sst::checked_t<uint>(3U) | sst::checked_t<uint>(1U), 3U);
    F(sst::checked_t<uint>(3U) | sst::checked_t<uint>(2U), 3U);
    F(sst::checked_t<uint>(uint_max) | sst::checked_t<uint>(2U),
      uint_max);
    F(sst::checked_t<uint>(uint_max) | sst::checked_t<uint>(3U),
      uint_max);

    F(sst::checked_t<uint>(0U) ^ sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(1U) ^ sst::checked_t<uint>(1U), 0U);
    F(sst::checked_t<uint>(2U) ^ sst::checked_t<uint>(1U), 3U);
    F(sst::checked_t<uint>(3U) ^ sst::checked_t<uint>(1U), 2U);
    F(sst::checked_t<uint>(3U) ^ sst::checked_t<uint>(2U), 1U);
    F(sst::checked_t<uint>(uint_max) ^ sst::checked_t<uint>(2U),
      uint_max - 2);
    F(sst::checked_t<uint>(uint_max) ^ sst::checked_t<uint>(3U),
      uint_max - 3);

    F(sst::checked_t<uint>(0U) >> sst::checked_t<uint>(1U), 0U);
    F(sst::checked_t<uint>(1U) >> sst::checked_t<uint>(1U), 0U);
    F(sst::checked_t<uint>(2U) >> sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(3U) >> sst::checked_t<uint>(1U), 1U);
    F(sst::checked_t<uint>(3U) >> sst::checked_t<uint>(2U), 0U);
    F(sst::checked_t<uint>(uint_max) >> sst::checked_t<uint>(2U),
      uint_max >> 2);
    F(sst::checked_t<uint>(uint_max) >> sst::checked_t<uint>(3U),
      uint_max >> 3);

    F(sst::checked_t<uint>(0U) << sst::checked_t<uint>(1U), 0U);
    F(sst::checked_t<uint>(1U) << sst::checked_t<uint>(1U), 2U);
    F(sst::checked_t<uint>(2U) << sst::checked_t<uint>(1U), 4U);
    F(sst::checked_t<uint>(3U) << sst::checked_t<uint>(1U), 6U);
    F(sst::checked_t<uint>(3U) << sst::checked_t<uint>(2U), 12U);
    F(sst::checked_t<uint>(uint_max) << sst::checked_t<uint>(0U),
      uint_max);
    G(sst::checked_t<uint>(uint_max) << sst::checked_t<uint>(1U),
      sst::checked_overflow);
    G(sst::checked_t<uint>(uint_max) << sst::checked_t<uint>(2U),
      sst::checked_overflow);
    G(sst::checked_t<uint>(uint_max) << sst::checked_t<uint>(3U),
      sst::checked_overflow);

#undef G
#undef F

    //------------------------------------------------------------------

    SST_TEST_THROW((sst::checked_t<int>(int_max) * 2),
                   sst::checked_overflow);
    SST_TEST_THROW((int_max * sst::checked_t<int>(2)),
                   sst::checked_overflow);
    SST_TEST_THROW((sst::checked_t<int>(int_max) + 1),
                   sst::checked_overflow);
    SST_TEST_THROW((int_max + sst::checked_t<int>(1)),
                   sst::checked_overflow);
    SST_TEST_THROW((sst::checked_t<int>(int_min) - 1),
                   sst::checked_overflow);
    SST_TEST_THROW((int_min - sst::checked_t<int>(1)),
                   sst::checked_overflow);

    SST_TEST_THROW((sst::checked_t<int>(int_max) << 1),
                   sst::checked_overflow);

    SST_TEST_THROW((sst::checked_t<unsigned int>(uint_max) * 2),
                   sst::checked_overflow);
    SST_TEST_THROW((uint_max * sst::checked_t<unsigned int>(2)),
                   sst::checked_overflow);
    SST_TEST_THROW((sst::checked_t<unsigned int>(uint_max) + 1),
                   sst::checked_overflow);
    SST_TEST_THROW((uint_max + sst::checked_t<unsigned int>(1)),
                   sst::checked_overflow);
    SST_TEST_THROW((sst::checked_t<unsigned int>(0) - 1),
                   sst::checked_overflow);
    SST_TEST_THROW((0 - sst::checked_t<unsigned int>(1)),
                   sst::checked_overflow);

    SST_TEST_THROW((sst::checked_t<unsigned int>(uint_max) << 1),
                   sst::checked_overflow);

    SST_TEST_THROW((sst::checked_t<unsigned int>(-1) >> 0),
                   sst::checked_overflow);

    SST_TEST_THROW((static_cast<bool>(sst::checked_t<int>(2))),
                   sst::checked_overflow);

    //------------------------------------------------------------------
  });
}
