/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_MEMGB_OVERLAP_H
#define SRC_SST_MEMGB_OVERLAP_H

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_randhhu.h>
#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <stdio.h>
#include <string.h>
#include <TEST_EXIT.h>

/* end_includes */

#define SST_MEMGB_OVERLAP_STR2(x) #x

#define SST_MEMGB_OVERLAP_STR1(x) SST_MEMGB_OVERLAP_STR2(x)

#define SST_MEMGB_OVERLAP(sst_memGb, sst_memG1, min, max) \
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
    unsigned int const n2, \
    unsigned int const n, \
    char const * const arg \
  ) { \
    (void)printf("%s(\n", func); \
    (void)printf("  "); \
    print_array(s1, s1n, 4, 3); \
    (void)printf(", %u,\n", n1); \
    (void)printf("  itself, %u,\n", n2); \
    (void)printf("  %u\n", n); \
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
    unsigned int const n2, \
    unsigned int const n, \
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
    (void)printf(", %u,\n", n1); \
    (void)printf("  itself, %u,\n", n2); \
    (void)printf("  %u\n", n); \
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
      unsigned char s1[(max)]; \
      unsigned int n; \
      for (n = 0; n != sizeof(s1); ++n) { \
        s1[n] = sst_randhhu(); \
      } \
      for (n = (min); n != sizeof(s1) + 1; ++n) { \
        unsigned int n1; \
        for (n1 = 0; n1 != sizeof(s1) - n + 1; ++n1) { \
          unsigned int n2; \
          for (n2 = 0; n2 != sizeof(s1) - n + 1; ++n2) { \
            unsigned char ex[sizeof(s1)]; \
            if (n1 < n2 && n > n2 - n1) { \
              continue; \
            } \
            (void)memcpy(ex, s1, sizeof(s1)); \
            { \
              unsigned int i; \
              for (i = 0; i != n; ++i) { \
                ex[n1 + i] = sst_memG1(s1[n2 + i]); \
              } \
            } \
            { \
              unsigned char re[sizeof(s1)]; \
              unsigned char * s1_x = re; \
              unsigned int n1_x = n1; \
              unsigned char const * s2_x = re; \
              unsigned int n2_x = n2; \
              unsigned int n_x = n; \
              (void)memcpy(re, s1, sizeof(s1)); \
              sst_memGb( \
                0?0:s1_x++, 0?0:n1_x++, \
                0?0:s2_x++, 0?0:n2_x++, \
                0?0:n_x++ \
              ); \
              if (s1_x != re + 1) { \
                exit_status = TEST_EXIT_FAIL; \
                if (prints != 0) { \
                  print_bad_evaluation( \
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), \
                    s1, n1, \
                    n2, \
                    n, \
                    "s1" \
                  ); \
                  --prints; \
                } \
                if (prints == 0) { \
                  return exit_status; \
                } \
              } \
              if (n1_x != n1 + 1) { \
                exit_status = TEST_EXIT_FAIL; \
                if (prints != 0) { \
                  print_bad_evaluation( \
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), \
                    s1, n1, \
                    n2, \
                    n, \
                    "n1" \
                  ); \
                  --prints; \
                } \
                if (prints == 0) { \
                  return exit_status; \
                } \
              } \
              if (s2_x != re + 1) { \
                exit_status = TEST_EXIT_FAIL; \
                if (prints != 0) { \
                  print_bad_evaluation( \
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), \
                    s1, n1, \
                    n2, \
                    n, \
                    "s2" \
                  ); \
                  --prints; \
                } \
                if (prints == 0) { \
                  return exit_status; \
                } \
              } \
              if (n2_x != n2 + 1) { \
                exit_status = TEST_EXIT_FAIL; \
                if (prints != 0) { \
                  print_bad_evaluation( \
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), \
                    s1, n1, \
                    n2, \
                    n, \
                    "n2" \
                  ); \
                  --prints; \
                } \
                if (prints == 0) { \
                  return exit_status; \
                } \
              } \
              if (n_x != n + 1) { \
                exit_status = TEST_EXIT_FAIL; \
                if (prints != 0) { \
                  print_bad_evaluation( \
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), \
                    s1, n1, \
                    n2, \
                    n, \
                    "n" \
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
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), SST_FALSE, \
                    s1, n1, \
                    n2, \
                    n, \
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
              (sst_memGb)( \
                re, n1, \
                re, n2, \
                n \
              ); \
              if (memcmp(re, ex, sizeof(s1)) != 0) { \
                exit_status = TEST_EXIT_FAIL; \
                if (prints != 0) { \
                  print_bad_result( \
                    SST_MEMGB_OVERLAP_STR1(sst_memGb), \
                    sizeof(s1), SST_TRUE, \
                    s1, n1, \
                    n2, \
                    n, \
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
    return exit_status; \
  }

#endif
