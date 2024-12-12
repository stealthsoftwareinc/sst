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
#include <sst/catalog/is_input_iterator.hpp>
// Include twice to test idempotence.
#include <sst/catalog/is_input_iterator.hpp>
//

#include <deque>
#include <list>
#include <set>
#include <type_traits>
#include <vector>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
  //------------------------------------------------------------------

#define TEST_1_HELPER(I, b)                                            \
  ([] {                                                                \
    SST_TEST_BOOL((sst::is_input_iterator<I>::value == (b)));          \
    SST_TEST_BOOL((sst::is_input_iterator<I &>::value == (b)));        \
  }())

#define TEST_1(I, b)                                                   \
  ([] {                                                                \
    TEST_1_HELPER(I, b);                                               \
    TEST_1_HELPER(I const, b);                                         \
    TEST_1_HELPER(I volatile, b);                                      \
    TEST_1_HELPER(I const volatile, b);                                \
  }())

#define TEST_2_HELPER(I, T, b)                                         \
  ([] {                                                                \
    SST_TEST_BOOL(                                                     \
        (sst::is_input_iterator<I, std::is_same, T>::value == (b)));   \
  }())

#define TEST_2(I, T, b)                                                \
  ([] {                                                                \
    TEST_2_HELPER(I, T, b);                                            \
    TEST_2_HELPER(I const, T, b);                                      \
    TEST_2_HELPER(I volatile, T, b);                                   \
    TEST_2_HELPER(I const volatile, T, b);                             \
    TEST_2_HELPER(I &, T, b);                                          \
    TEST_2_HELPER(I const &, T, b);                                    \
    TEST_2_HELPER(I volatile &, T, b);                                 \
    TEST_2_HELPER(I const volatile &, T, b);                           \
  }())

#define TEST_3(C)                                                      \
  ([] {                                                                \
    TEST_1(C, false);                                                  \
    TEST_1(C::iterator, true);                                         \
    TEST_2(C::iterator, C, false);                                     \
    TEST_2(C::iterator, C::value_type, true);                          \
    TEST_1(C::const_iterator, true);                                   \
    TEST_2(C::const_iterator, C, false);                               \
    TEST_2(C::const_iterator, C::value_type, true);                    \
  }())
    //

    int int_array[1];

    TEST_1(int, false);

    TEST_1(int *, true);
    TEST_1(int const *, true);
    TEST_1(int volatile *, true);
    TEST_1(int const volatile *, true);

    TEST_2(int *, int, true);
    TEST_2(int const *, int, true);
    TEST_2(int volatile *, int, true);
    TEST_2(int const volatile *, int, true);

    TEST_2(int *, long, false);
    TEST_2(int const *, long, false);
    TEST_2(int volatile *, long, false);
    TEST_2(int const volatile *, long, false);

    TEST_2(int *, short, false);
    TEST_2(int const *, short, false);
    TEST_2(int volatile *, short, false);
    TEST_2(int const volatile *, short, false);

    TEST_1(void *, false);
    TEST_1(void const *, false);
    TEST_1(void volatile *, false);
    TEST_1(void const volatile *, false);

    TEST_2(decltype(&int_array), decltype(int_array), true);
    TEST_2(decltype(&int_array), int *, false);

    TEST_3(std::deque<int>);
    TEST_3(std::list<int>);
    TEST_3(std::set<int>);
    TEST_3(std::vector<int>);

#undef TEST_3
#undef TEST_2
#undef TEST_2_HELPER
#undef TEST_1
#undef TEST_1_HELPER

    //------------------------------------------------------------------
  });
}
