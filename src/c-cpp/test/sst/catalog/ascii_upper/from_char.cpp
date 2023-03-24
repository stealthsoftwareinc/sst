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
#include <sst/catalog/ascii_upper.hpp>
// Include twice to test idempotence.
#include <sst/catalog/ascii_upper.hpp>
//

#include <type_traits>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([]() {
    ;

    //------------------------------------------------------------------

#define F2(x, y)                                                       \
  ([] {                                                                \
    SST_TEST_BOOL((sst::ascii_upper((x)) == (y)),                      \
                  SST_TEST_SHOW((sst::ascii_upper((x)))));             \
    SST_TEST_BOOL((std::is_same<decltype(sst::ascii_upper((x))),       \
                                decltype((x))>::value));               \
  }())

#define F(x, y)                                                        \
  ([] {                                                                \
    F2(x, y);                                                          \
    F2(static_cast<unsigned char>(x), static_cast<unsigned char>(y));  \
    F2(u##x, u##y);                                                    \
    F2(U##x, U##y);                                                    \
    F2(L##x, L##y);                                                    \
  }())

    F('\0', '\0');
    F('\1', '\1');

    F(' ', ' ');
    F('!', '!');
    F('"', '"');

    F('0', '0');
    F('1', '1');
    F('2', '2');
    F('3', '3');
    F('4', '4');
    F('5', '5');
    F('6', '6');
    F('7', '7');
    F('8', '8');
    F('9', '9');

    F('A', 'A');
    F('B', 'B');
    F('C', 'C');
    F('D', 'D');
    F('E', 'E');
    F('F', 'F');
    F('G', 'G');
    F('H', 'H');
    F('I', 'I');
    F('J', 'J');
    F('K', 'K');
    F('L', 'L');
    F('M', 'M');
    F('N', 'N');
    F('O', 'O');
    F('P', 'P');
    F('Q', 'Q');
    F('R', 'R');
    F('S', 'S');
    F('T', 'T');
    F('U', 'U');
    F('V', 'V');
    F('W', 'W');
    F('X', 'X');
    F('Y', 'Y');
    F('Z', 'Z');

    F('a', 'A');
    F('b', 'B');
    F('c', 'C');
    F('d', 'D');
    F('e', 'E');
    F('f', 'F');
    F('g', 'G');
    F('h', 'H');
    F('i', 'I');
    F('j', 'J');
    F('k', 'K');
    F('l', 'L');
    F('m', 'M');
    F('n', 'N');
    F('o', 'O');
    F('p', 'P');
    F('q', 'Q');
    F('r', 'R');
    F('s', 'S');
    F('t', 'T');
    F('u', 'U');
    F('v', 'V');
    F('w', 'W');
    F('x', 'X');
    F('y', 'Y');
    F('z', 'Z');

#undef F
#undef F2

    //------------------------------------------------------------------
  });
}
