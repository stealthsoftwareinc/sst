/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_wall_time_any_get</code>
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

#ifndef SST_SST_WALL_TIME_ANY_GET_H
#define SST_SST_WALL_TIME_ANY_GET_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_clock.h>
#include <sst/sst_wall_time_any.h>

/* end_includes */

/**
 * Gets the current value of any wall clock.
 *
 * @param t
 *
 * @param c
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

SST_PUBLIC_C_FUNCTION sst_status (sst_wall_time_any_get)(
  sst_wall_time_any *,
  sst_wall_clock
);

#else

sst_status sst_wall_time_any_get(
  sst_wall_time_any * t,
  sst_wall_clock c
);

#endif

#endif
