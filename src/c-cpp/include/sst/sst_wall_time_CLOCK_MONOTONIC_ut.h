/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
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

#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/sst_status.h>

#if SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC

#include <time.h>

/**
 * Holds a value of the
 * <code>CLOCK_MONOTONIC</code>
 * wall clock.
 *
 * @available
 * if and only if the
 * <code>::SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
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
   * <code>::SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
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
   * <code>::SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
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
   * <code>::SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
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
   * <code>::SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC</code>
   * macro is defined to the integer
   * constant&nbsp;<code>1</code>
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  struct timespec sst_t;

};

typedef struct sst_wall_time_CLOCK_MONOTONIC_ut sst_wall_time_CLOCK_MONOTONIC_ut;

#endif

#endif // #ifndef SST_SST_WALL_TIME_CLOCK_MONOTONIC_UT_H
