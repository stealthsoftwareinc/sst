/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_MEMH1_BASIC_H
#define SRC_SST_MEMH1_BASIC_H

#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_getbit1.h>
#include <sst/sst_randhhu.h>
#include <sst/sst_setbit1.h>
#include <stdio.h>
#include <TEST_EXIT.h>

#define SST_MEMH1_BASIC_STR2(x) #x

#define SST_MEMH1_BASIC_STR1(x) SST_MEMH1_BASIC_STR2(x)

#define SST_MEMH1_BASIC(sst_memH1, sst_bitH1) \
  static int main2( \
    unsigned long int prints, \
    unsigned long int trials \
  ) { \
    int exit_status = TEST_EXIT_PASS; \
    for (; trials != 0; --trials) { \
      unsigned int const s1 = sst_randhhu(); \
      unsigned int const s2 = sst_randhhu(); \
      unsigned int ex = 0; \
      { \
        unsigned int i; \
        for (i = 0; i != CHAR_BIT; ++i) { \
          sst_bit const x = sst_getbit1(s1, i); \
          sst_bit const y = sst_getbit1(s2, i); \
          ex = sst_setbit1(ex, i, sst_bitH1(x, y)); \
        } \
      } \
      { \
        unsigned int s1_x = s1; \
        unsigned int s2_x = s2; \
        unsigned int const re = sst_memH1(0?0:s1_x++, 0?0:s2_x++); \
        if (s1_x != s1 + 1) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "%s(0x%02X, 0x%02X):\n" \
              "  s1 was not evaluated exactly once\n" \
              "\n", \
              SST_MEMH1_BASIC_STR1(sst_memH1), \
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
              "%s(0x%02X, 0x%02X):\n" \
              "  s2 was not evaluated exactly once\n" \
              "\n", \
              SST_MEMH1_BASIC_STR1(sst_memH1), \
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
              "%s(0x%02X, 0x%02X):\n" \
              "  expected: 0x%02X\n" \
              "  received: 0x%02X\n" \
              "\n", \
              SST_MEMH1_BASIC_STR1(sst_memH1), \
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
        unsigned int const re = (sst_memH1)(s1, s2); \
        if (re != ex) { \
          exit_status = TEST_EXIT_FAIL; \
          if (prints != 0) { \
            (void)printf( \
              "(%s)(0x%02X, 0x%02X):\n" \
              "  expected: 0x%02X\n" \
              "  received: 0x%02X\n" \
              "\n", \
              SST_MEMH1_BASIC_STR1(sst_memH1), \
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
    return exit_status; \
  }

#endif
