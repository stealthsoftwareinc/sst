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
 * <code>::SST_STATUS_NAME_MAXSTR</code>
 * macro.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_STATUS_NAME_MAXSTR_H
#define SST_SST_STATUS_NAME_MAXSTR_H

/**
 * A character string literal whose length (excluding the null
 * terminator) is
 * <code>::SST_STATUS_NAME_MAXLEN</code>.
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
 * This string was changed from
 * length&nbsp;31
 * to
 * length&nbsp;63.
 * </li>
 * <li>
 * This string was changed from a sequence of digits counting its length
 * to a visual placeholder.
 * </li>
 * </ul>
 *
 * @showinitializer
 */

#define SST_STATUS_NAME_MAXSTR "[-------------------SST_STATUS_NAME_MAXSTR--------------------]"

#endif // SST_SST_STATUS_NAME_MAXSTR_H
