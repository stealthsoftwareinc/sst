/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_wall_time_CLOCK_MONOTONIC_ut</code>
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

#ifndef SST_SST_WALL_TIME_CLOCK_MONOTONIC_UT_H
#define SST_SST_WALL_TIME_CLOCK_MONOTONIC_UT_H

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

#include <sst/sst_status.h>
#include <time.h>

/**
 * Holds a value of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock.
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

struct sst_wall_time_CLOCK_MONOTONIC_ut {

  /**
   * Indicates whether this object is probably valid.
   * <p>
   * If undefined behavior checks are disabled, then this variable is
   * ignored and the rest of this paragraph does not apply.
   * Otherwise, this variable is set to
   * <code>::sst_wall_time_CLOCK_MONOTONIC_live</code>
   * by the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function.
   * This allows a probabilistic validity check to be performed: this
   * object is probably valid if this variable has value
   * <code>::sst_wall_time_CLOCK_MONOTONIC_live</code>,
   * or definitely invalid if not.
   * </p>
   *
   * @available
   * if and only if the
   * <code>::SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
   * macro is defined to the integer
   * constant&nbsp;<code>1</code>
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  unsigned int sst_magic;

  /**
   * The error number returned by the call to the
   * <code>clock_gettime</code>
   * function made by the most recent call to the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function for this object, or an indeterminate value if the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function has never been called for this object.
   *
   * @available
   * if and only if the
   * <code>::SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
   * macro is defined to the integer
   * constant&nbsp;<code>1</code>
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  int sst_e;

  /**
   * The status code returned by the most recent call to the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function for this object, or an indeterminate value if the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function has never been called for this object.
   *
   * @available
   * if and only if the
   * <code>::SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
   * macro is defined to the integer
   * constant&nbsp;<code>1</code>
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  sst_status sst_s;

  /**
   * The
   * <code>timespec</code>
   * structure returned by the call to the
   * <code>clock_gettime</code>
   * function made by the most recent call to the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function for this object, or an indeterminate value if the
   * <code>::sst_wall_time_CLOCK_MONOTONIC_get</code>
   * function has never been called for this object.
   * <p>
   * The value of this variable should also be considered to be
   * indeterminate if the aforementioned call to the
   * <code>clock_gettime</code>
   * function failed.
   * </p>
   *
   * @available
   * if and only if the
   * <code>::SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
   * macro is defined to the integer
   * constant&nbsp;<code>1</code>
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  struct timespec sst_t;

};

typedef struct sst_wall_time_CLOCK_MONOTONIC_ut sst_wall_time_CLOCK_MONOTONIC_ut;

#endif

#endif
