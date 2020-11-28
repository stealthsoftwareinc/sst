/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_ensure_2</code>
 * function.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_ENSURE_2_H
#define SST_SST_ENSURE_2_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

/**
 *
 * @param p
 *
 * @param n
 *
 * @param k
 *
 * @param s1
 *
 * @param s2
 *
 * @return
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION void * (sst_ensure_2)(
  void *,
  size_t *,
  size_t,
  size_t,
  size_t
);

#else

void * sst_ensure_2(
  void * p,
  size_t * n,
  size_t k,
  size_t s1,
  size_t s2
);

#endif

#endif
