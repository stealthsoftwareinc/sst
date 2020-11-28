/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
