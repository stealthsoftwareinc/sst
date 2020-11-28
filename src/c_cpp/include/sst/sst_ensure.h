/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_ensure</code>
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

#ifndef SST_SST_ENSURE_H
#define SST_SST_ENSURE_H

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
 * @param s
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

SST_PUBLIC_C_FUNCTION void * (sst_ensure)(
  void *,
  size_t *,
  size_t,
  size_t
);

#else

void * sst_ensure(
  void * p,
  size_t * n,
  size_t k,
  size_t s
);

#endif

#endif
