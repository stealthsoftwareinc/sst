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
#include <sst/catalog/ascii_lower.hpp>
// Include twice to test idempotence.
#include <sst/catalog/ascii_lower.hpp>
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
    SST_TEST_BOOL((sst::ascii_lower((x)) == (y)),                      \
                  SST_TEST_SHOW((sst::ascii_lower((x)))));             \
    SST_TEST_BOOL((std::is_same<decltype(sst::ascii_lower((x))),       \
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

    F('A', 'a');
    F('B', 'b');
    F('C', 'c');
    F('D', 'd');
    F('E', 'e');
    F('F', 'f');
    F('G', 'g');
    F('H', 'h');
    F('I', 'i');
    F('J', 'j');
    F('K', 'k');
    F('L', 'l');
    F('M', 'm');
    F('N', 'n');
    F('O', 'o');
    F('P', 'p');
    F('Q', 'q');
    F('R', 'r');
    F('S', 's');
    F('T', 't');
    F('U', 'u');
    F('V', 'v');
    F('W', 'w');
    F('X', 'x');
    F('Y', 'y');
    F('Z', 'z');

    F('a', 'a');
    F('b', 'b');
    F('c', 'c');
    F('d', 'd');
    F('e', 'e');
    F('f', 'f');
    F('g', 'g');
    F('h', 'h');
    F('i', 'i');
    F('j', 'j');
    F('k', 'k');
    F('l', 'l');
    F('m', 'm');
    F('n', 'n');
    F('o', 'o');
    F('p', 'p');
    F('q', 'q');
    F('r', 'r');
    F('s', 's');
    F('t', 't');
    F('u', 'u');
    F('v', 'v');
    F('w', 'w');
    F('x', 'x');
    F('y', 'y');
    F('z', 'z');

#undef F
#undef F2

    //------------------------------------------------------------------
  });
}
