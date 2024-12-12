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
#include <sst/catalog/is_sentinel.hpp>
// Include twice to test idempotence.
#include <sst/catalog/is_sentinel.hpp>
//

#include <cstddef>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------
    // Pointer types
    //------------------------------------------------------------------

#define F6(S, I, b)                                                    \
  (SST_TEST_BOOL((sst::is_sentinel<S, I>::value == (b))))

#define F5(S, I, b)                                                    \
  ([] {                                                                \
    F6(S, I, b);                                                       \
    F6(S, I &, b);                                                     \
  }())

#define F4(S, I, b)                                                    \
  ([] {                                                                \
    F5(S, I, b);                                                       \
    F5(S &, I, b);                                                     \
  }())

#define F3(S, I, b)                                                    \
  ([] {                                                                \
    F4(S, I *, b);                                                     \
    F4(S, I const *, b);                                               \
    F4(S, I volatile *, b);                                            \
    F4(S, I const volatile *, b);                                      \
  }())

#define F2(S, I, b)                                                    \
  ([] {                                                                \
    F3(S *, I, b);                                                     \
    F3(S const *, I, b);                                               \
    F3(S volatile *, I, b);                                            \
    F3(S const volatile *, I, b);                                      \
  }())

#define F(I, b)                                                        \
  ([] {                                                                \
    F2(I, I, b);                                                       \
    F5(std::nullptr_t, I *, b);                                        \
    F5(std::nullptr_t, I const *, b);                                  \
    F5(std::nullptr_t, I volatile *, b);                               \
    F5(std::nullptr_t, I const volatile *, b);                         \
  }())
    //

    F(void, false);
    F(char, true);
    F(void *, true);
    F(char *, true);

#undef F
#undef F2
#undef F3
#undef F4
#undef F5
#undef F6

    //------------------------------------------------------------------
  });
}
