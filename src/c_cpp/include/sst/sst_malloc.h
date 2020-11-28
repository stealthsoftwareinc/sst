/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_malloc</code>
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

#ifndef SST_SST_MALLOC_H
#define SST_SST_MALLOC_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

/* end_includes */

/**
 * Allocates an object.
 *
 * @param s
 * the size of the object to allocate.
 * If
 * <code>s</code>
 * is zero, then the behavior is as if it were some nonzero value so
 * that a unique pointer is still produced, but the resulting object
 * should never be accessed.
 *
 * @return
 * a pointer to the allocated object if the allocation succeeds, or a
 * null pointer if not
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
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

SST_PUBLIC_C_FUNCTION void * (sst_malloc)(
  size_t
);

#else

void * sst_malloc(
  size_t s
);

#endif

#endif
