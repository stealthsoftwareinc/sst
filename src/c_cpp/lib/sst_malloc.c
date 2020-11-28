/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
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

#include <sst/sst_malloc.h>
#include <sst/sst_malloc.h>

/* begin_includes */

#include <sst/sst_realloc.h>
#include <stddef.h>

/* end_includes */

void * (sst_malloc)(
  size_t const s
) {
  return sst_realloc(NULL, 0, s);
}
