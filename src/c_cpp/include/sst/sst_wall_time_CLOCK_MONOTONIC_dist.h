/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_dist</code>
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

#ifndef SST_SST_WALL_TIME_CLOCK_MONOTONIC_DIST_H
#define SST_SST_WALL_TIME_CLOCK_MONOTONIC_DIST_H

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>

/* end_includes */

/**
 * Approximates the distance in seconds between two values of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock.
 *
 * @param t1
 * a pointer to an object that holds a value of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock.
 * If
 * <code>t1</code>
 * is not a null pointer and does not point to an object of the
 * referenced type, or if another thread modifies the object while this
 * function is being called, then the behavior is undefined.
 * This function never modifies the object.
 * If the object has never been set by the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
 * function, then the behavior is undefined.
 *
 * @param t2
 * a pointer to an object that holds a value of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock.
 * If
 * <code>t2</code>
 * is not a null pointer and does not point to an object of the
 * referenced type, or if another thread modifies the object while this
 * function is being called, then the behavior is undefined.
 * This function never modifies the object.
 * If the object has never been set by the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
 * function, then the behavior is undefined.
 *
 * @return
 * &minus;1 if
 * <code>t1</code>
 * or
 * <code>t2</code>
 * is a null pointer or points to an object that holds an error value,
 * or an approximate distance in seconds between the two values if not
 *
 * @available
 * if and only if the
 * <code>::SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
 * macro is defined to the integer
 * constant&nbsp;<code>1</code>
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

SST_PUBLIC_C_FUNCTION double (sst_wall_time_CLOCK_MONOTONIC_dist)(
  sst_wall_time_CLOCK_MONOTONIC const *,
  sst_wall_time_CLOCK_MONOTONIC const *
);

#else

double sst_wall_time_CLOCK_MONOTONIC_dist(
  sst_wall_time_CLOCK_MONOTONIC const * t1,
  sst_wall_time_CLOCK_MONOTONIC const * t2
);

#endif

#endif

#endif
