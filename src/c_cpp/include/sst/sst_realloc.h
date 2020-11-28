/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_realloc</code>
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

#ifndef SST_SST_REALLOC_H
#define SST_SST_REALLOC_H

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

SST_PUBLIC_C_FUNCTION void * (sst_realloc)(
  void *,
  size_t,
  size_t
);

#else

void * sst_realloc(
  void * p,
  size_t n,
  size_t s
);

#endif

#endif
