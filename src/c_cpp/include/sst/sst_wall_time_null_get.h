/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_null_get</code>
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

#ifndef SST_SST_WALL_TIME_NULL_GET_H
#define SST_SST_WALL_TIME_NULL_GET_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_null.h>

/* end_includes */

/**
 * Gets the current value of the null wall clock.
 *
 * @param t
 * a pointer to an object that will be set to an error value, as the
 * null wall clock has only error values.
 * If
 * <code>t</code>
 * is not a null pointer and does not point to an object of the
 * referenced type, or if another thread accesses the object while this
 * function is being called, then the behavior is undefined.
 *
 * @return
 * <ul>
 * <li>
 * <code>::SST_ALWAYS_FAILS</code>
 * if and only if
 * <code>t</code>
 * is not a null pointer
 * </li>
 * <li>
 * <code>::SST_NULL_POINTER</code>
 * if and only if
 * <code>t</code>
 * is a null pointer
 * </li>
 * </ul>
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

SST_PUBLIC_C_FUNCTION sst_status (sst_wall_time_null_get)(
  sst_wall_time_null *
);

#else

sst_status sst_wall_time_null_get(
  sst_wall_time_null * t
);

#endif

#endif
