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
 * <code>::sst_option_pair_w_ut</code>
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

#ifndef SST_SST_OPTION_PAIR_W_UT_H
#define SST_SST_OPTION_PAIR_W_UT_H

/* begin_includes */

#include <stddef.h>

/* end_includes */

/**
 * Represents an option that has been (attempted to be) parsed by the
 * <code>::sst_require_option_value_w</code>
 * function, the
 * <code>::sst_permit_option_value_w</code>
 * function, or the
 * <code>::sst_forbid_option_value_w</code>
 * function.
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

struct sst_option_pair_w_ut {

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  wchar_t const * sst_name;

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  wchar_t const * sst_value;

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  wchar_t sst_buffer[3];

};

typedef struct sst_option_pair_w_ut sst_option_pair_w_ut;

#endif // SST_SST_OPTION_PAIR_W_UT_H
