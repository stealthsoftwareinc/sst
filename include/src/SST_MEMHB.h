/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_MEMHB_H
#define SRC_SST_MEMHB_H

/* begin_includes */

#include <assert.h>
#include <stddef.h>

/* end_includes */

#define SST_MEMHB(sst_memHb, sst_memH1) \
  void (sst_memHb)( \
    void * const s1, \
    size_t const n1, \
    void const * const s2, \
    size_t const n2, \
    void const * const s3, \
    size_t const n3, \
    size_t n \
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
    p1 += n; \
    p2 += n; \
    p3 += n; \
    while (n != 0) { \
      --p1; \
      --p2; \
      --p3; \
      *p1 = sst_memH1(*p2, *p3); \
      --n; \
    } \
  }

#endif
