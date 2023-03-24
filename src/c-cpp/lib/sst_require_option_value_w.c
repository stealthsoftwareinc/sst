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

#include <sst/sst_require_option_value_w.h>
#include <sst/sst_require_option_value_w.h>

/* begin_includes */

#include <sst/sst_crop_option_w.h>
#include <sst/sst_get_option_value_w.h>
#include <sst/sst_is_valued_short_option_w.h>
#include <sst/sst_option_pair_w.h>
#include <sst/sst_option_pair_w_ut.h>
#include <stddef.h>

/* end_includes */

sst_option_pair_w (sst_require_option_value_w)(
  wchar_t * * * const argv,
  wchar_t const * const opt
) {
  sst_option_pair_w opp = {0};
  if (argv != NULL && *argv != NULL) {
    opp.sst_value = sst_get_option_value_w(*argv, opt);
    if (sst_is_valued_short_option_w((*argv)[0], opt)) {
      opp.sst_name = opp.sst_buffer;
      opp.sst_buffer[0] = (*argv)[0][0];
      opp.sst_buffer[1] = (*argv)[0][1];
    } else {
      opp.sst_name = sst_crop_option_w((*argv)[0], opt);
    }
    if (opp.sst_value != NULL) {
      if (opp.sst_value == (*argv)[1]) {
        ++*argv;
      }
      ++*argv;
    }
  }
  return opp;
}
