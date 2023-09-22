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

#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>

#if SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC

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

#ifndef SST_DOXYGEN

SST_EXTERN_C SST_DLL_EXPORT double (sst_wall_time_CLOCK_MONOTONIC_dist)(
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

#endif // SST_SST_WALL_TIME_CLOCK_MONOTONIC_DIST_H
