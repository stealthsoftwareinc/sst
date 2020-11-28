/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
