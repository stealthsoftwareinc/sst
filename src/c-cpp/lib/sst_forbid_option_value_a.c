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

#include <sst/sst_forbid_option_value_a.h>
#include <sst/sst_forbid_option_value_a.h>

/* begin_includes */

#include <sst/sst_crop_long_option_a.h>
#include <sst/sst_get_long_option_value_a.h>
#include <sst/sst_is_unvalued_option_a.h>
#include <sst/sst_is_valued_long_option_a.h>
#include <sst/sst_is_valued_short_option_a.h>
#include <sst/sst_option_pair_a.h>
#include <sst/sst_option_pair_a_ut.h>
#include <stddef.h>

/* end_includes */

sst_option_pair_a (sst_forbid_option_value_a)(
  char * * * const argv,
  char const * const opt
) {
  sst_option_pair_a opp = {0};
  if (argv != NULL && *argv != NULL) {
    if (sst_is_unvalued_option_a((*argv)[0], opt)) {
      opp.sst_name = (*argv)[0];
      ++*argv;
    } else if (sst_is_valued_long_option_a((*argv)[0], opt)) {
      opp.sst_value = sst_get_long_option_value_a(*argv, opt);
      opp.sst_name = sst_crop_long_option_a((*argv)[0], opt);
    } else if (sst_is_valued_short_option_a((*argv)[0], opt)) {
      opp.sst_name = opp.sst_buffer;
      opp.sst_buffer[0] = (*argv)[0][0];
      opp.sst_buffer[1] = (*argv)[0][1];
      (*argv)[0][1] = (*argv)[0][0];
      ++(*argv)[0];
    }
  }
  return opp;
}
