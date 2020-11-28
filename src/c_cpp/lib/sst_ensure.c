/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
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

#include <sst/sst_ensure.h>
#include <sst/sst_ensure.h>

/* begin_includes */

#include <sst/sst_realloc.h>
#include <stddef.h>

/* end_includes */

void * (sst_ensure)(
  void * const p,
  size_t * const n,
  size_t const k,
  size_t const s
) {
  size_t const size_max = (size_t)(-1);
  size_t const smooth_n = (p != NULL && n != NULL) ? *n : 0;
  size_t nn = smooth_n;
  if (nn >= s) {
    return p;
  }
  if (k == 0) {
    if (n != NULL) {
      *n = s;
    }
    return p;
  }
  do {
    if (nn == 0) {
      nn = 1;
    } else if (nn == 1) {
      nn = 2;
    } else if (nn <= size_max - nn / 2) {
      nn = nn + nn / 2;
    } else {
      nn = size_max;
    }
  } while (nn < s);
  for (;;) {
    if (nn <= size_max / k) {
      void * const pp = sst_realloc(p, smooth_n * k, nn * k);
      if (pp != NULL) {
        if (n != NULL) {
          *n = nn;
        }
        return pp;
      }
    }
    if (nn == s) {
      return NULL;
    }
    nn = s + (nn - s) / 2;
  }
}
