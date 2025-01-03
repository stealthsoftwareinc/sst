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
#include <sst/sst_getbit.h>
#include <sst/sst_getbit1.h>
#include <sst/sst_randhhu.h>
#include <stdio.h>

int main(
  void
) {
  unsigned long int prints = 10;
  unsigned long int trials = 1000;
  int exit_status = 0;
  for (; trials != 0; --trials) {
    unsigned char s1[2];
    unsigned int n1;
    s1[0] = sst_randhhu();
    s1[1] = sst_randhhu();
    for (n1 = 0; n1 != 2; ++n1) {
      unsigned int r1r;
      for (r1r = 0; r1r != CHAR_BIT; ++r1r) {
        unsigned int const r1 = (1 - n1) * CHAR_BIT + r1r;
        sst_bit const ex = sst_getbit1(s1[1], r1r);
        {
          unsigned char * s1_x = s1;
          unsigned int n1_x = n1;
          unsigned int r1_x = r1;
          sst_bit const re = sst_getbit(
            0?0:s1_x++, 0?0:n1_x++, 0?0:r1_x++
          );
          if (s1_x != s1 + 1) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "sst_getbit({0x%02X, 0x%02X}, %u, %u):\n"
                "  s1 was not evaluated exactly once\n"
                "\n",
                (unsigned int)s1[0], (unsigned int)s1[1],
                n1, r1
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
          if (n1_x != n1 + 1) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "sst_getbit({0x%02X, 0x%02X}, %u, %u):\n"
                "  n1 was not evaluated exactly once\n"
                "\n",
                (unsigned int)s1[0], (unsigned int)s1[1],
                n1, r1
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
                "sst_getbit({0x%02X, 0x%02X}, %u, %u):\n"
                "  r1 was not evaluated exactly once\n"
                "\n",
                (unsigned int)s1[0], (unsigned int)s1[1],
                n1, r1
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
                "sst_getbit({0x%02X, 0x%02X}, %u, %u):\n"
                "  expected: %d\n"
                "  received: %d\n"
                "\n",
                (unsigned int)s1[0], (unsigned int)s1[1],
                n1, r1, ex, re
              );
              --prints;
            }
            if (prints == 0) {
              return exit_status;
            }
          }
        }
        {
          sst_bit const re = (sst_getbit)(s1, n1, r1);
          if (re != ex) {
            exit_status = 1;
            if (prints != 0) {
              (void)printf(
                "(sst_getbit)({0x%02X, 0x%02X}, %u, %u):\n"
                "  expected: %d\n"
                "  received: %d\n"
                "\n",
                (unsigned int)s1[0], (unsigned int)s1[1],
                n1, r1, ex, re
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
