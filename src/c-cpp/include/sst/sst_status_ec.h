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
 * <code>::sst_status_ec</code>
 * function.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_STATUS_EC_H
#define SST_SST_STATUS_EC_H

/* begin_includes */

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/SST_EXTERN_C.h>
#include <sst/sst_status.h>

/* end_includes */

/**
 * Maps a status code that implies
 * <code>::SST_FAILURE</code>
 * to the slash-delimited fully qualified name of the corresponding Java
 * exception class.
 *
 * @param s
 * a status code.
 * If
 * <code>s</code>
 * is larger than
 * <code>::SST_STATUS_MAXVAL</code>
 * or does not imply
 * <code>::SST_FAILURE</code>,
 * then it is implicitly adjusted to
 * <code>::SST_FAILURE</code>.
 *
 * @return
 * a pointer to a string with static storage duration that holds the
 * slash-delimited fully qualified name of the Java exception class that
 * corresponds
 * to&nbsp;<code>s</code>.
 * If the program attempts to modify the string, then the behavior is
 * undefined.
 *
 * @available
 * always
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ul>
 * <li>
 * This function was updated to actually return the appropriate Java
 * exception class names.
 * Prior to this version, this function would simply return
 * <code>"java/lang/RuntimeException"</code>
 * as a placeholder.
 * </li>
 * </ul>
 */

#ifndef SST_DOXYGEN

SST_EXTERN_C SST_DLL_EXPORT char const * (sst_status_ec)(
  sst_status
);

#else

char const * sst_status_ec(
  sst_status s
);

#endif

#endif // #ifndef SST_SST_STATUS_EC_H
