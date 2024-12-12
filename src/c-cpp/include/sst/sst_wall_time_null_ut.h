/*
 * Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
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

#endif // SST_SST_WALL_TIME_NULL_UT_H
