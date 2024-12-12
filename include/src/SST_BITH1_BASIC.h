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

#ifndef SRC_SST_BITH1_BASIC_H
#define SRC_SST_BITH1_BASIC_H

#include <sst/sst_bit.h>
#include <stdio.h>
#include <TEST_EXIT.h>

#define SST_BITH1_BASIC_STR2(x) #x

#define SST_BITH1_BASIC_STR1(x) SST_BITH1_BASIC_STR2(x)

#define SST_BITH1_BASIC(sst_bitH1) \
  static int main2( \
    sst_bit const (* const truth)[2], \
    unsigned long int prints \
  ) { \
    int exit_status = TEST_EXIT_PASS; \
    sst_bit s1; \
    for (s1 = -9; s1 != 10; ++s1) { \
      sst_bit s2; \
      for (s2 = -9; s2 != 10; ++s2) { \
        sst_bit const ex = !!truth[!!s1][!!s2]; \
        { \
          sst_bit s1_x = s1; \
          sst_bit s2_x = s2; \
          sst_bit const re = sst_bitH1(0?0:s1_x++, 0?0:s2_x++); \
          if (s1_x != s1 + 1) { \
            exit_status = TEST_EXIT_FAIL; \
            if (prints != 0) { \
              (void)printf( \
                "%s(%d, %d):\n" \
                "  s1 was not evaluated exactly once\n" \
                "\n", \
                SST_BITH1_BASIC_STR1(sst_bitH1), \
                s1, s2 \
              ); \
              --prints; \
            } \
            if (prints == 0) { \
              return exit_status; \
            } \
          } \
          if (s2_x != s2 + 1) { \
            exit_status = TEST_EXIT_FAIL; \
            if (prints != 0) { \
              (void)printf( \
                "%s(%d, %d):\n" \
                "  s2 was not evaluated exactly once\n" \
                "\n", \
                SST_BITH1_BASIC_STR1(sst_bitH1), \
                s1, s2 \
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
                "%s(%d, %d):\n" \
                "  expected: %d\n" \
                "  received: %d\n" \
                "\n", \
                SST_BITH1_BASIC_STR1(sst_bitH1), \
                s1, s2, ex, re \
              ); \
              --prints; \
            } \
            if (prints == 0) { \
              return exit_status; \
            } \
          } \
        } \
        { \
          sst_bit const re = (sst_bitH1)(s1, s2); \
          if (re != ex) { \
            exit_status = TEST_EXIT_FAIL; \
            if (prints != 0) { \
              (void)printf( \
                "(%s)(%d, %d):\n" \
                "  expected: %d\n" \
                "  received: %d\n" \
                "\n", \
                SST_BITH1_BASIC_STR1(sst_bitH1), \
                s1, s2, ex, re \
              ); \
              --prints; \
            } \
            if (prints == 0) { \
              return exit_status; \
            } \
          } \
        } \
      } \
    } \
    return exit_status; \
  }

#endif
