/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_BITHB_H
#define SRC_SST_BITHB_H

/* begin_includes */

#include <assert.h>
#include <limits.h>
#include <sst/sst_bit.h>
#include <sst/sst_getbit1.h>
#include <sst/sst_setbit1.h>
#include <stddef.h>

/* end_includes */

#define SST_BITHB(sst_bitHb, sst_bitH1) \
  void (sst_bitHb)( \
    void * const s1, \
    size_t const n1, \
    size_t r1, \
    void const * const s2, \
    size_t const n2, \
    size_t r2, \
    void const * const s3, \
    size_t const n3, \
    size_t r3, \
    size_t n, \
    size_t r \
  ) { \
    unsigned char * p1 = s1; \
    unsigned char const * p2 = s2; \
    unsigned char const * p3 = s3; \
    assert(s1 != NULL); \
    assert(s2 != NULL); \
    assert(s3 != NULL); \
    p1 += n1; \
    p2 += n2; \
    p3 += n3; \
    p1 += r1 / CHAR_BIT; \
    p2 += r2 / CHAR_BIT; \
    p3 += r3 / CHAR_BIT; \
    r1 %= CHAR_BIT; \
    r2 %= CHAR_BIT; \
    r3 %= CHAR_BIT; \
    p1 += n; \
    p2 += n; \
    p3 += n; \
    p1 += r / CHAR_BIT; \
    p2 += r / CHAR_BIT; \
    p3 += r / CHAR_BIT; \
    r1 += r % CHAR_BIT; \
    r2 += r % CHAR_BIT; \
    r3 += r % CHAR_BIT; \
    p1 += r1 / CHAR_BIT; \
    p2 += r2 / CHAR_BIT; \
    p3 += r3 / CHAR_BIT; \
    r1 %= CHAR_BIT; \
    r2 %= CHAR_BIT; \
    r3 %= CHAR_BIT; \
    while (n != 0 || r != 0) { \
      if (r1 != 0) { \
        --r1; \
      } else { \
        --p1; \
        r1 = CHAR_BIT - 1; \
      } \
      if (r2 != 0) { \
        --r2; \
      } else { \
        --p2; \
        r2 = CHAR_BIT - 1; \
      } \
      if (r3 != 0) { \
        --r3; \
      } else { \
        --p3; \
        r3 = CHAR_BIT - 1; \
      } \
      { \
        sst_bit const x = sst_getbit1(*p2, r2); \
        sst_bit const y = sst_getbit1(*p3, r3); \
        *p1 = sst_setbit1(*p1, r1, sst_bitH1(x, y)); \
      } \
      if (r != 0) { \
        --r; \
      } else { \
        --n; \
        r = CHAR_BIT - 1; \
      } \
    } \
  }

#endif
