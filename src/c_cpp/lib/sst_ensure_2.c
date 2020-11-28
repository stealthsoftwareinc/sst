/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
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

#include <sst/sst_ensure_2.h>
#include <sst/sst_ensure_2.h>

/* begin_includes */

#include <sst/sst_ensure.h>
#include <stddef.h>

/* end_includes */

void * (sst_ensure_2)(
  void * const p,
  size_t * const n,
  size_t const k,
  size_t const s1,
  size_t const s2
) {
  size_t const size_max = (size_t)(-1);
  if (s1 > size_max - s2) {
    return NULL;
  }
  return sst_ensure(p, n, k, s1 + s2);
}
