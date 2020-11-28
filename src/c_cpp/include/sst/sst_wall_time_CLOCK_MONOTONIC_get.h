/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
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

#ifndef SST_SST_WALL_TIME_CLOCK_MONOTONIC_GET_H
#define SST_SST_WALL_TIME_CLOCK_MONOTONIC_GET_H

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>

/* end_includes */

/**
 * Gets the current value of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock.
 *
 * @param t
 * a pointer to an object that will be set to the current value of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock if this function succeeds, or to an error value if not.
 * If
 * <code>t</code>
 * is not a null pointer and does not point to an object of the
 * referenced type, or if another thread accesses the object while this
 * function is being called, then the behavior is undefined.
 *
 * @return
 * <ul>
 * <li>
 * a status code that implies
 * <code>::SST_FAILURE</code>
 * if and only if the operation failed
 * </li>
 * <li>
 * <code>::SST_NULL_POINTER</code>
 * if and only if
 * <code>t</code>
 * is a null pointer
 * </li>
 * <li>
 * <code>::SST_SUCCESS</code>
 * if and only if the operation succeeded
 * </li>
 * </ul>
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

SST_PUBLIC_C_FUNCTION sst_status (sst_wall_time_CLOCK_MONOTONIC_get)(
  sst_wall_time_CLOCK_MONOTONIC *
);

#else

sst_status sst_wall_time_CLOCK_MONOTONIC_get(
  sst_wall_time_CLOCK_MONOTONIC * t
);

#endif

#endif

#endif
