/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_randhhu.h>
#include <sst/sst_setbit.h>
#include <sst/sst_setbit1.h>
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
        sst_bit s2;
        for (s2 = -9; s2 != 10; ++s2) {
          unsigned char ex[2];
          ex[0] = s1[0];
          ex[1] = sst_setbit1(s1[1], r1r, s2);
          {
            unsigned char re[2];
            unsigned char * s1_x = re;
            unsigned int n1_x = n1;
            unsigned int r1_x = r1;
            sst_bit s2_x = s2;
            re[0] = s1[0];
            re[1] = s1[1];
            sst_setbit(
              0?0:s1_x++, 0?0:n1_x++, 0?0:r1_x++,
              0?0:s2_x++
            );
            if (s1_x != re + 1) {
              exit_status = 1;
              if (prints != 0) {
                (void)printf(
                  "sst_setbit({0x%02X, 0x%02X}, %u, %u, %d):\n"
                  "  s1 was not evaluated exactly once\n"
                  "\n",
                  (unsigned int)s1[0], (unsigned int)s1[1],
                  n1, r1, s2
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
                  "sst_setbit({0x%02X, 0x%02X}, %u, %u, %d):\n"
                  "  n1 was not evaluated exactly once\n"
                  "\n",
                  (unsigned int)s1[0], (unsigned int)s1[1],
                  n1, r1, s2
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
                  "sst_setbit({0x%02X, 0x%02X}, %u, %u, %d):\n"
                  "  r1 was not evaluated exactly once\n"
                  "\n",
                  (unsigned int)s1[0], (unsigned int)s1[1],
                  n1, r1, s2
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
                  "sst_setbit({0x%02X, 0x%02X}, %u, %u, %d):\n"
                  "  s2 was not evaluated exactly once\n"
                  "\n",
                  (unsigned int)s1[0], (unsigned int)s1[1],
                  n1, r1, s2
                );
                --prints;
              }
              if (prints == 0) {
                return exit_status;
              }
            }
            if (re[0] != ex[0] || re[1] != ex[1]) {
              exit_status = 1;
              if (prints != 0) {
                (void)printf(
                  "sst_setbit({0x%02X, 0x%02X}, %u, %u, %d):\n"
                  "  expected: {0x%02X, 0x%02X}\n"
                  "  received: {0x%02X, 0x%02X}\n"
                  "\n",
                  (unsigned int)s1[0], (unsigned int)s1[1],
                  n1, r1, s2,
                  (unsigned int)ex[0], (unsigned int)ex[1],
                  (unsigned int)re[0], (unsigned int)re[1]
                );
                --prints;
              }
              if (prints == 0) {
                return exit_status;
              }
            }
          }
          {
            unsigned char re[2];
            re[0] = s1[0];
            re[1] = s1[1];
            (sst_setbit)(re, n1, r1, s2);
            if (re[0] != ex[0] || re[1] != ex[1]) {
              exit_status = 1;
              if (prints != 0) {
                (void)printf(
                  "(sst_setbit)({0x%02X, 0x%02X}, %u, %u, %d):\n"
                  "  expected: {0x%02X, 0x%02X}\n"
                  "  received: {0x%02X, 0x%02X}\n"
                  "\n",
                  (unsigned int)s1[0], (unsigned int)s1[1],
                  n1, r1, s2,
                  (unsigned int)ex[0], (unsigned int)ex[1],
                  (unsigned int)re[0], (unsigned int)re[1]
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
  }
  return exit_status;
}
