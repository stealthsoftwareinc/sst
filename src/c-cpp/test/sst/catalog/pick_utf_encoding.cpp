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
#include <sst/catalog/pick_utf_encoding.hpp>
// Include twice to test idempotence.
#include <sst/catalog/pick_utf_encoding.hpp>
//

#include <cstdint>

#include <sst/catalog/SST_CPP20_OR_LATER.h>
#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/ones_mask.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/catalog/text_encoding.hpp>
#include <sst/catalog/type_max.hpp>
#include <sst/catalog/type_min.hpp>

int main() {
  return sst::test_main([&] {
    //------------------------------------------------------------------

    SST_TEST_BOOL(
        (sst::pick_utf_encoding<bool>() == sst::text_encoding::utf_8));

#if SST_CPP20_OR_LATER
    SST_TEST_BOOL((sst::pick_utf_encoding<char8_t>()
                   == sst::text_encoding::utf_8));
#endif

    if (sst::type_max<signed char>::value < sst::ones_mask<long>(15)
        || sst::type_min<signed char>::value
               == -sst::ones_mask<long>(15)) {
      SST_TEST_BOOL((sst::pick_utf_encoding<signed char>()
                     == sst::text_encoding::utf_8));
    }

    if (sst::type_max<unsigned char>::value
        < sst::ones_mask<unsigned long>(16)) {
      SST_TEST_BOOL((sst::pick_utf_encoding<unsigned char>()
                     == sst::text_encoding::utf_8));
    }

#if INT8_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::int8_t>()
                   == sst::text_encoding::utf_8));
#endif

#if UINT8_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::uint8_t>()
                   == sst::text_encoding::utf_8));
#endif

    SST_TEST_BOOL((sst::pick_utf_encoding<char16_t>()
                   == sst::text_encoding::utf_16));

    if (sst::type_max<short>::value < sst::ones_mask<long>(31)
        && sst::type_min<short>::value < -sst::ones_mask<long>(15)) {
      SST_TEST_BOOL((sst::pick_utf_encoding<short>()
                     == sst::text_encoding::utf_16));
    }

    if (sst::type_max<unsigned short>::value
        < sst::ones_mask<unsigned long>(32)) {
      SST_TEST_BOOL((sst::pick_utf_encoding<unsigned short>()
                     == sst::text_encoding::utf_16));
    }

#if INT16_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::int16_t>()
                   == sst::text_encoding::utf_16));
#endif

#if UINT16_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::uint16_t>()
                   == sst::text_encoding::utf_16));
#endif

    SST_TEST_BOOL((sst::pick_utf_encoding<char32_t>()
                   == sst::text_encoding::utf_32));

    if (sst::type_min<long>::value < -sst::ones_mask<long>(31)) {
      SST_TEST_BOOL((sst::pick_utf_encoding<long>()
                     == sst::text_encoding::utf_32));
    }

    SST_TEST_BOOL((sst::pick_utf_encoding<unsigned long>()
                   == sst::text_encoding::utf_32));

#if INT32_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::int32_t>()
                   == sst::text_encoding::utf_32));
#endif

#if UINT32_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::uint32_t>()
                   == sst::text_encoding::utf_32));
#endif

    SST_TEST_BOOL((sst::pick_utf_encoding<long long>()
                   == sst::text_encoding::utf_32));

    SST_TEST_BOOL((sst::pick_utf_encoding<unsigned long long>()
                   == sst::text_encoding::utf_32));

#if INT64_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::int64_t>()
                   == sst::text_encoding::utf_32));
#endif

#if UINT64_MAX
    SST_TEST_BOOL((sst::pick_utf_encoding<std::uint64_t>()
                   == sst::text_encoding::utf_32));
#endif

    //------------------------------------------------------------------
  });
}
