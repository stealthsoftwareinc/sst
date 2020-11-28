/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_wall_time_any_ut</code>
 * type.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_WALL_TIME_ANY_UT_H
#define SST_SST_WALL_TIME_ANY_UT_H

/* begin_includes */

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_clock.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_ut.h>
#include <sst/sst_wall_time_null.h>
#include <sst/sst_wall_time_null_ut.h>

/* end_includes */

/**
 * Holds a value of any wall clock.
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

struct sst_wall_time_any_ut {

  /**
   * Indicates whether this object is probably valid.
   * <p>
   * If undefined behavior checks are disabled, then this variable is
   * ignored and the rest of this paragraph does not apply.
   * Otherwise, this variable is set to
   * <code>::sst_wall_time_any_live</code>
   * by the
   * <code>::sst_wall_time_any_get</code>
   * function.
   * This allows a probabilistic validity check to be performed: this
   * object is probably valid if this variable has value
   * <code>::sst_wall_time_any_live</code>,
   * or definitely invalid if not.
   * </p>
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  unsigned int sst_magic;

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  sst_status sst_s;

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  sst_wall_clock sst_c;

  union {

    sst_wall_time_null sst_null;

    #if (SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC)
      sst_wall_time_CLOCK_MONOTONIC sst_CLOCK_MONOTONIC;
    #endif

  } sst_t;

};

typedef struct sst_wall_time_any_ut sst_wall_time_any_ut;

#endif
