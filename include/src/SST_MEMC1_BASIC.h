/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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

#ifndef SRC_SST_MEMC1_BASIC_H
#define SRC_SST_MEMC1_BASIC_H

#include <limits.h>
#include <sst/sst_setbit1.h>
#include <stdio.h>
#include <TEST_EXIT.h>

#define SST_MEMC1_BASIC_STR2(x) #x

#define SST_MEMC1_BASIC_STR1(x) SST_MEMC1_BASIC_STR2(x)

#define SST_MEMC1_BASIC(sst_memC1, sst_bitC1) \
  static int main2( \
    void \
  ) { \
    unsigned int ex = 0; \
    { \
      unsigned int i; \
      for (i = 0; i != CHAR_BIT; ++i) { \
        ex = sst_setbit1(ex, i, sst_bitC1()); \
      } \
    } \
    { \
      unsigned int const re = sst_memC1(); \
      if (re != ex) { \
        (void)printf( \
          "%s():\n" \
          "  expected: 0x%02X\n" \
          "  received: 0x%02X\n" \
          "\n", \
          SST_MEMC1_BASIC_STR1(sst_memC1), \
          ex, re \
        ); \
        return TEST_EXIT_FAIL; \
      } \
    } \
    { \
      unsigned int const re = (sst_memC1)(); \
      if (re != ex) { \
        (void)printf( \
          "(%s)():\n" \
          "  expected: 0x%02X\n" \
          "  received: 0x%02X\n" \
          "\n", \
          SST_MEMC1_BASIC_STR1(sst_memC1), \
          ex, re \
        ); \
        return TEST_EXIT_FAIL; \
      } \
    } \
    return TEST_EXIT_PASS; \
  }

#endif
