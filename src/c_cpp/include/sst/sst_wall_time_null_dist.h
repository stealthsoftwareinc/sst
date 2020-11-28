/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_null_dist</code>
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

#ifndef SST_SST_WALL_TIME_NULL_DIST_H
#define SST_SST_WALL_TIME_NULL_DIST_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_wall_time_null.h>

/* end_includes */

/**
 * Approximates the distance in seconds between two values of the null
 * wall clock.
 *
 * @param t1
 * a pointer to an object that holds a value of the null wall clock.
 * If
 * <code>t1</code>
 * is not a null pointer and does not point to an object of the
 * referenced type, or if another thread modifies the object while this
 * function is being called, then the behavior is undefined.
 * This function never modifies the object.
 * If the object has never been set by the
 * <code>::sst_wall_time_null_get</code>
 * function, then the behavior is undefined.
 *
 * @param t2
 * a pointer to an object that holds a value of the null wall clock.
 * If
 * <code>t2</code>
 * is not a null pointer and does not point to an object of the
 * referenced type, or if another thread modifies the object while this
 * function is being called, then the behavior is undefined.
 * This function never modifies the object.
 * If the object has never been set by the
 * <code>::sst_wall_time_null_get</code>
 * function, then the behavior is undefined.
 *
 * @return
 * &minus;1, as the null wall clock has only error values
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

SST_PUBLIC_C_FUNCTION double (sst_wall_time_null_dist)(
  sst_wall_time_null const *,
  sst_wall_time_null const *
);

#else

double sst_wall_time_null_dist(
  sst_wall_time_null const * t1,
  sst_wall_time_null const * t2
);

#endif

#endif
