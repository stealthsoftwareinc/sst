/*
 * Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef SRC_SST_BITC1_BASIC_H
#define SRC_SST_BITC1_BASIC_H

#include <sst/sst_bit.h>
#include <stdio.h>
#include <TEST_EXIT.h>

#define SST_BITC1_BASIC_STR2(x) #x

#define SST_BITC1_BASIC_STR1(x) SST_BITC1_BASIC_STR2(x)

#define SST_BITC1_BASIC(sst_bitC1) \
  static int main2( \
    sst_bit const truth \
  ) { \
    sst_bit const ex = !!truth; \
    { \
      sst_bit const re = sst_bitC1(); \
      if (re != ex) { \
        (void)printf( \
          "%s():\n" \
          "  expected: %d\n" \
          "  received: %d\n" \
          "\n", \
          SST_BITC1_BASIC_STR1(sst_bitC1), \
          ex, re \
        ); \
        return TEST_EXIT_FAIL; \
      } \
    } \
    { \
      sst_bit const re = (sst_bitC1)(); \
      if (re != ex) { \
        (void)printf( \
          "(%s)():\n" \
          "  expected: %d\n" \
          "  received: %d\n" \
          "\n", \
          SST_BITC1_BASIC_STR1(sst_bitC1), \
          ex, re \
        ); \
        return TEST_EXIT_FAIL; \
      } \
    } \
    return TEST_EXIT_PASS; \
  }

#endif
