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

#ifndef SRC_SST_MEMG1_BASIC_H
#define SRC_SST_MEMG1_BASIC_H

#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_getbit1.h>
#include <sst/sst_randhhu.h>
#include <sst/sst_setbit1.h>
#include <stdio.h>
#include <TEST_EXIT.h>

#define SST_MEMG1_BASIC_STR2(x) #x

#define SST_MEMG1_BASIC_STR1(x) SST_MEMG1_BASIC_STR2(x)

#define SST_MEMG1_BASIC(sst_memG1, sst_bitG1) \
  static int main2( \
    unsigned long int prints, \
    unsigned long int trials \
  ) { \
    int exit_status = TEST_EXIT_PASS; \
    for (; trials != 0; --trials) { \
      unsigned int const s1 = sst_randhhu(); \
      unsigned int ex = 0; \
      { \
        unsigned int i; \
        for (i = 0; i != CHAR_BIT; ++i) { \
          sst_bit const x = sst_getbit1(s1, i); \
          ex = sst_setbit1(ex, i, sst_bitG1(x)); \
        } \
      } \
      { \
        unsigned int s1_x = s1; \
        unsigned int const re = sst_memG1(0?0:s1_x++); \
        if (s1_x != s1 + 1) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "%s(0x%02X):\n" \
              "  s1 was not evaluated exactly once\n" \
              "\n", \
              SST_MEMG1_BASIC_STR1(sst_memG1), \
              s1 \
            ); \
            --prints; \
          } \
          if (prints == 0) { \
            return exit_status; \
          } \
        } \
        if (re != ex) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "%s(0x%02X):\n" \
              "  expected: 0x%02X\n" \
              "  received: 0x%02X\n" \
              "\n", \
              SST_MEMG1_BASIC_STR1(sst_memG1), \
              s1, ex, re \
            ); \
            --prints; \
          } \
          if (prints == 0) { \
            return exit_status; \
          } \
        } \
      } \
      { \
        unsigned int const re = (sst_memG1)(s1); \
        if (re != ex) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "(%s)(0x%02X):\n" \
              "  expected: 0x%02X\n" \
              "  received: 0x%02X\n" \
              "\n", \
              SST_MEMG1_BASIC_STR1(sst_memG1), \
              s1, ex, re \
            ); \
            --prints; \
          } \
          if (prints == 0) { \
            return exit_status; \
          } \
        } \
      } \
    } \
    return exit_status; \
  }

#endif
