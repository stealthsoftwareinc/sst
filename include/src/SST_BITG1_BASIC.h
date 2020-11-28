/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_BITG1_BASIC_H
#define SRC_SST_BITG1_BASIC_H

#include <sst/sst_bit.h>
#include <stdio.h>
#include <TEST_EXIT.h>

#define SST_BITG1_BASIC_STR2(x) #x

#define SST_BITG1_BASIC_STR1(x) SST_BITG1_BASIC_STR2(x)

#define SST_BITG1_BASIC(sst_bitG1) \
  static int main2( \
    sst_bit const * const truth, \
    unsigned long int prints \
  ) { \
    int exit_status = TEST_EXIT_PASS; \
    sst_bit s1; \
    for (s1 = -9; s1 != 10; ++s1) { \
      sst_bit const ex = !!truth[!!s1]; \
      { \
        sst_bit s1_x = s1; \
        sst_bit const re = sst_bitG1(0?0:s1_x++); \
        if (s1_x != s1 + 1) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "%s(%d):\n" \
              "  s1 was not evaluated exactly once\n" \
              "\n", \
              SST_BITG1_BASIC_STR1(sst_bitG1), \
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
              "%s(%d):\n" \
              "  expected: %d\n" \
              "  received: %d\n" \
              "\n", \
              SST_BITG1_BASIC_STR1(sst_bitG1), \
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
        sst_bit const re = (sst_bitG1)(s1); \
        if (re != ex) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "(%s)(%d):\n" \
              "  expected: %d\n" \
              "  received: %d\n" \
              "\n", \
              SST_BITG1_BASIC_STR1(sst_bitG1), \
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
