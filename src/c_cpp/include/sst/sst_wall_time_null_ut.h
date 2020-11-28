/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_wall_time_null_ut</code>
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

#ifndef SST_SST_WALL_TIME_NULL_UT_H
#define SST_SST_WALL_TIME_NULL_UT_H

/**
 * Holds a value of the null wall clock.
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

struct sst_wall_time_null_ut {

  /**
   * Indicates whether this object is probably valid.
   * <p>
   * If undefined behavior checks are disabled, then this variable is
   * ignored and the rest of this paragraph does not apply.
   * Otherwise, this variable is set to
   * <code>::sst_wall_time_null_live</code>
   * by the
   * <code>::sst_wall_time_null_get</code>
   * function.
   * This allows a probabilistic validity check to be performed: this
   * object is probably valid if this variable has value
   * <code>::sst_wall_time_null_live</code>,
   * or definitely invalid if not.
   * </p>
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  unsigned int sst_magic;

};

typedef struct sst_wall_time_null_ut sst_wall_time_null_ut;

#endif
