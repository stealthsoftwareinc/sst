/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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

#ifndef SRC_SST_BITH_DISJOINT_H
#define SRC_SST_BITH_DISJOINT_H

/* begin_includes */

#include <limits.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bit.h>
#include <sst/sst_bool.h>
#include <sst/sst_getbit.h>
#include <sst/sst_randhhu.h>
#include <sst/sst_setbit.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <stdio.h>
#include <string.h>
#include <TEST_EXIT.h>

/* end_includes */

#define SST_BITH_DISJOINT_STR2(x) #x

#define SST_BITH_DISJOINT_STR1(x) SST_BITH_DISJOINT_STR2(x)

#define SST_BITH_DISJOINT(sst_bitH, sst_bitH1, min, max) \
  static void print_array( \
    unsigned char const * const x, \
    unsigned int const n, \
    unsigned int const columns, \
    unsigned int const indent \
  ) { \
    unsigned int i; \
    (void)printf("{"); \
    for (i = 0; i != n; ++i) { \
      if (i != 0) { \
        if (i % columns == 0) { \
          unsigned int j; \
          (void)printf(",\n"); \
          for (j = 0; j != indent; ++j) { \
            (void)printf(" "); \
          } \
        } else { \
          (void)printf(", "); \
        } \
      } \
      (void)printf("0x%02X", (unsigned int)x[i]); \
    } \
    (void)printf("}"); \
  } \
  static void print_bad_evaluation( \
    char const * const func, \
    unsigned int const s1n, \
    unsigned char const * const s1, \
    unsigned int const n1, \
    unsigned int const r1, \
    unsigned char const * const s2, \
    unsigned int const n2, \
    unsigned int const r2, \
    unsigned char const * const s3, \
    unsigned int const n3, \
    unsigned int const r3, \
    unsigned int const n, \
    unsigned int const r, \
    char const * const arg \
  ) { \
    (void)printf("%s(\n", func); \
    (void)printf("  "); \
    print_array(s1, s1n, 4, 3); \
    (void)printf(", %u, %u,\n", n1, r1); \
    (void)printf("  "); \
    print_array(s2, s1n, 4, 3); \
    (void)printf(", %u, %u,\n", n2, r2); \
    (void)printf("  "); \
    print_array(s3, s1n, 4, 3); \
    (void)printf(", %u, %u,\n", n3, r3); \
    (void)printf("  %u, %u\n", n, r); \
    (void)printf("):\n"); \
    (void)printf("  %s was not evaluated exactly once\n", arg); \
    (void)printf("\n"); \
  } \
  static void print_bad_result( \
    char const * const func, \
    unsigned int const s1n, \
    sst_bool const parens, \
    unsigned char const * const s1, \
    unsigned int const n1, \
    unsigned int const r1, \
    unsigned char const * const s2, \
    unsigned int const n2, \
    unsigned int const r2, \
    unsigned char const * const s3, \
    unsigned int const n3, \
    unsigned int const r3, \
    unsigned int const n, \
    unsigned int const r, \
    unsigned char const * const ex, \
    unsigned char const * const re \
  ) { \
    if (parens) { \
      (void)printf("(%s)(\n", func); \
    } else { \
      (void)printf("%s(\n", func); \
    } \
    (void)printf("  "); \
    print_array(s1, s1n, 4, 3); \
    (void)printf(", %u, %u,\n", n1, r1); \
    (void)printf("  "); \
    print_array(s2, s1n, 4, 3); \
    (void)printf(", %u, %u,\n", n2, r2); \
    (void)printf("  "); \
    print_array(s3, s1n, 4, 3); \
    (void)printf(", %u, %u,\n", n3, r3); \
    (void)printf("  %u, %u\n", n, r); \
    (void)printf("):\n"); \
    (void)printf("  expected: "); \
    print_array(ex, s1n, 4, 13); \
    (void)printf("\n"); \
    (void)printf("  received: "); \
    print_array(re, s1n, 4, 13); \
    (void)printf("\n"); \
    (void)printf("\n"); \
  } \
  static int main2( \
    unsigned long int prints, \
    unsigned long int trials \
  ) { \
    int exit_status = TEST_EXIT_PASS; \
    for (; trials != 0; --trials) { \
      unsigned int const cb = CHAR_BIT; \
      unsigned char s1[(max)]; \
      unsigned char s2[(max)]; \
      unsigned char s3[(max)]; \
      unsigned int r; \
      for (r = 0; r != sizeof(s1); ++r) { \
        s1[r] = sst_randhhu(); \
        s2[r] = sst_randhhu(); \
        s3[r] = sst_randhhu(); \
      } \
      for (r = (min) * cb; r != sizeof(s1) * cb + 1; ++r) { \
        unsigned int r1; \
        for (r1 = 0; r1 != sizeof(s1) * cb - r + 1; ++r1) { \
          unsigned int r2; \
          for (r2 = 0; r2 != sizeof(s1) * cb - r + 1; ++r2) { \
            unsigned int r3; \
            for (r3 = 0; r3 != sizeof(s1) * cb - r + 1; ++r3) { \
              unsigned char ex[sizeof(s1)]; \
              unsigned int r1n; \
              (void)memcpy(ex, s1, sizeof(s1)); \
              { \
                unsigned int i; \
                for (i = 0; i != r; ++i) { \
                  sst_bit const x = sst_getbit(s2, 0, r2 + i); \
                  sst_bit const y = sst_getbit(s3, 0, r3 + i); \
                  sst_setbit(ex, 0, r1 + i, sst_bitH1(x, y)); \
                } \
              } \
              for (r1n = 0; r1n != r1 / cb + 1; ++r1n) { \
                unsigned int const r1r = r1 - r1n * cb; \
                unsigned int r2n; \
                for (r2n = 0; r2n != r2 / cb + 1; ++r2n) { \
                  unsigned int const r2r = r2 - r2n * cb; \
                  unsigned int r3n; \
                  for (r3n = 0; r3n != r3 / cb + 1; ++r3n) { \
                    unsigned int const r3r = r3 - r3n * cb; \
                    unsigned int rn; \
                    for (rn = 0; rn != r / cb + 1; ++rn) { \
                      unsigned int const rr = r - rn * cb; \
                      { \
                        unsigned char re[sizeof(s1)]; \
                        unsigned char * s1_x = re; \
                        unsigned int n1_x = r1n; \
                        unsigned int r1_x = r1r; \
                        unsigned char const * s2_x = s2; \
                        unsigned int n2_x = r2n; \
                        unsigned int r2_x = r2r; \
                        unsigned char const * s3_x = s3; \
                        unsigned int n3_x = r3n; \
                        unsigned int r3_x = r3r; \
                        unsigned int n_x = rn; \
                        unsigned int r_x = rr; \
                        (void)memcpy(re, s1, sizeof(s1)); \
                        sst_bitH( \
                          0?0:s1_x++, 0?0:n1_x++, 0?0:r1_x++, \
                          0?0:s2_x++, 0?0:n2_x++, 0?0:r2_x++, \
                          0?0:s3_x++, 0?0:n3_x++, 0?0:r3_x++, \
                          0?0:n_x++, 0?0:r_x++ \
                        ); \
                        if (s1_x != re + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "s1" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (n1_x != r1n + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "n1" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (r1_x != r1r + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "r1" \
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
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "s2" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (n2_x != r2n + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "n2" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (r2_x != r2r + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "r2" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (s3_x != s3 + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "s3" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (n3_x != r3n + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "n3" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (r3_x != r3r + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "r3" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (n_x != rn + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "n" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (r_x != rr + 1) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_evaluation( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              "r" \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                        if (memcmp(re, ex, sizeof(s1)) != 0) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_result( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), SST_FALSE, \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              ex, re \
                            ); \
                            --prints; \
                          } \
                          if (prints == 0) { \
                            return exit_status; \
                          } \
                        } \
                      } \
                      { \
                        unsigned char re[sizeof(s1)]; \
                        (void)memcpy(re, s1, sizeof(s1)); \
                        (sst_bitH)( \
                          re, r1n, r1r, \
                          s2, r2n, r2r, \
                          s3, r3n, r3r, \
                          rn, rr \
                        ); \
                        if (memcmp(re, ex, sizeof(s1)) != 0) { \
                          exit_status = TEST_EXIT_FAIL; \
                          if (prints != 0) { \
                            print_bad_result( \
                              SST_BITH_DISJOINT_STR1(sst_bitH), \
                              sizeof(s1), SST_TRUE, \
                              s1, r1n, r1r, \
                              s2, r2n, r2r, \
                              s3, r3n, r3r, \
                              rn, rr, \
                              ex, re \
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
                } \
              } \
            } \
          } \
        } \
      } \
    } \
    return exit_status; \
  }

#endif
