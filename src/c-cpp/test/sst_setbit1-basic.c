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

#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_randhhu.h>
#include <sst/sst_setbit1.h>
#include <stdio.h>

int main(
  void
) {
  unsigned long int prints = 10;
  unsigned long int trials = 1000;
  int exit_status = 0;
  for (; trials != 0; --trials) {
    unsigned int const s1 = sst_randhhu();
    unsigned int r1;
    for (r1 = 0; r1 != CHAR_BIT; ++r1) {
      sst_bit s2;
      for (s2 = -9; s2 != 10; ++s2) {
        unsigned int const m = 1U << (CHAR_BIT - 1 - r1);
        unsigned int const ex = s2 != 0 ? s1 | m : s1 & ~m;
        {
          unsigned int s1_x = s1;
          unsigned int r1_x = r1;
          sst_bit s2_x = s2;
          unsigned int const re = sst_setbit1(
            0?0:s1_x++, 0?0:r1_x++,
            0?0:s2_x++
          );
          if (s1_x != s1 + 1) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "sst_setbit1(0x%02X, %u, %d):\n"
                "  s1 was not evaluated exactly once\n"
                "\n",
                s1, r1, s2
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
          if (r1_x != r1 + 1) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "sst_setbit1(0x%02X, %u, %d):\n"
                "  r1 was not evaluated exactly once\n"
                "\n",
                s1, r1, s2
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
          if (s2_x != s2 + 1) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "sst_setbit1(0x%02X, %u, %d):\n"
                "  s2 was not evaluated exactly once\n"
                "\n",
                s1, r1, s2
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
          if (re != ex) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "sst_setbit1(0x%02X, %u, %d):\n"
                "  expected: 0x%02X\n"
                "  received: 0x%02X\n"
                "\n",
                s1, r1, s2, ex, re
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
        }
        {
          unsigned int const re = (sst_setbit1)(s1, r1, s2);
          if (re != ex) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "(sst_setbit1)(0x%02X, %u, %d):\n"
                "  expected: 0x%02X\n"
                "  received: 0x%02X\n"
                "\n",
                s1, r1, s2, ex, re
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
        }
      }
    }
  }
  return exit_status;
}
