/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_overlap</code>
 * function.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_OVERLAP_H
#define SST_SST_OVERLAP_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

/**
 * Determines whether two objects overlap.
 *
 * @param p
 * a pointer that points to an object or one past the end of an object.
 * If
 * <code>p</code>
 * does not point to an object nor one past the end of an object, then
 * the behavior is undefined.
 * If
 * <code>p</code>
 * points to an object and the object does not contain at least
 * <code>pn</code>
 * bytes, then the behavior is undefined.
 * If
 * <code>p</code>
 * points one past the end of a maximal object and
 * <code>pn</code>
 * is not zero, then the behavior is undefined.
 *
 * @param pn
 * the number of bytes to consider from the object pointed to by
 * <code>p</code>,
 * or zero if
 * <code>p</code>
 * points one past the end of a maximal object
 *
 * @param q
 * a pointer that points to an object or one past the end of an object.
 * If
 * <code>q</code>
 * does not point to an object nor one past the end of an object, then
 * the behavior is undefined.
 * If
 * <code>q</code>
 * points to an object and the object does not contain at least
 * <code>qn</code>
 * bytes, then the behavior is undefined.
 * If
 * <code>q</code>
 * points one past the end of a maximal object and
 * <code>qn</code>
 * is not zero, then the behavior is undefined.
 *
 * @param qn
 * the number of bytes to consider from the object pointed to by
 * <code>q</code>,
 * or zero if
 * <code>q</code>
 * points one past the end of a maximal object
 *
 * @return
 * <code>::SST_TRUE</code>
 * if
 * <code>pn</code>
 * and
 * <code>qn</code>
 * are not zero and the first
 * <code>pn</code>
 * bytes of the object pointed to by
 * <code>p</code>
 * overlap the first
 * <code>qn</code>
 * bytes of the object pointed to by
 * <code>q</code>,
 * or
 * <code>::SST_FALSE</code>
 * if not
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION sst_bool (sst_overlap)(
  void const *,
  size_t,
  void const *,
  size_t
);

#else

sst_bool sst_overlap(
  void const * p,
  size_t pn,
  void const * q,
  size_t qn
);

#endif

#endif
