/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
