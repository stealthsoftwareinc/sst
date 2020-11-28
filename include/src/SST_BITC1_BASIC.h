/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
