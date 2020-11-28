/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <limits.h>
#include <sst/sst_bit.h>
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
    unsigned int const s1 = sst_randhhu();
    unsigned int r1;
    for (r1 = 0; r1 != CHAR_BIT; ++r1) {
      unsigned int const m = 1U << (CHAR_BIT - 1 - r1);
      sst_bit const ex = (s1 & m) != 0;
      {
        unsigned int s1_x = s1;
        unsigned int r1_x = r1;
        sst_bit const re = sst_getbit1(
          0?0:s1_x++, 0?0:r1_x++
        );
        if (s1_x != s1 + 1) {
          exit_status = 1;
          if (prints != 0) {
            (void)printf(
              "sst_getbit1(0x%02X, %u):\n"
              "  s1 was not evaluated exactly once\n"
              "\n",
              s1, r1
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
              "sst_getbit1(0x%02X, %u):\n"
              "  r1 was not evaluated exactly once\n"
              "\n",
              s1, r1
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
              "sst_getbit1(0x%02X, %u):\n"
              "  expected: %d\n"
              "  received: %d\n"
              "\n",
              s1, r1, ex, re
            );
            --prints;
          }
          if (prints == 0) {
            return exit_status;
          }
        }
      }
      {
        sst_bit const re = (sst_getbit1)(s1, r1);
        if (re != ex) {
          exit_status = 1;
          if (prints != 0) {
            (void)printf(
              "(sst_getbit1)(0x%02X, %u):\n"
              "  expected: %d\n"
              "  received: %d\n"
              "\n",
              s1, r1, ex, re
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
  return exit_status;
}
