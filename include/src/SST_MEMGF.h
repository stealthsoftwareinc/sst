/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_MEMGF_H
#define SRC_SST_MEMGF_H

/* begin_includes */

#include <assert.h>
#include <stddef.h>

/* end_includes */

#define SST_MEMGF(sst_memGf, sst_memG1) \
  void (sst_memGf)( \
    void * const s1, \
    size_t const n1, \
    void const * const s2, \
    size_t const n2, \
    size_t n \
  ) { \
    unsigned char * p1 = s1; \
    unsigned char const * p2 = s2; \
    assert(s1 != NULL); \
    assert(s2 != NULL); \
    p1 += n1; \
    p2 += n2; \
    while (n != 0) { \
      *p1 = sst_memG1(*p2); \
      ++p1; \
      ++p2; \
      --n; \
    } \
  }

#endif
