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

#include <sst/SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/sst_status.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC.h>

#if SST_WITH_SST_WALL_CLOCK_CLOCK_MONOTONIC

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

SST_EXTERN_C SST_DLL_EXPORT sst_status (sst_wall_time_CLOCK_MONOTONIC_get)(
  sst_wall_time_CLOCK_MONOTONIC *
);

#else

sst_status sst_wall_time_CLOCK_MONOTONIC_get(
  sst_wall_time_CLOCK_MONOTONIC * t
);

#endif

#endif

#endif // SST_SST_WALL_TIME_CLOCK_MONOTONIC_GET_H
