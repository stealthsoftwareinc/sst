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

#include <sst/sst_is_long_option_a.h>
#include <sst/sst_is_long_option_a.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_is_long_option_a)(
  char const * const arg,
  char const * const opt
) {
  if (arg == NULL) {
    return SST_FALSE;
  }
  if (arg[0] != '-') {
    return SST_FALSE;
  }
  if (arg[1] != '-') {
    return SST_FALSE;
  }
  if (opt == NULL) {
    return SST_TRUE;
  }
  if (opt[0] != '-') {
    return SST_FALSE;
  }
  if (opt[1] != '-') {
    return SST_FALSE;
  }
  {
    char const * a = arg + 2;
    char const * o = opt + 2;
    while (*a != '\0' && *a != '=') {
      if (*a != *o) {
        return SST_FALSE;
      }
      ++a;
      ++o;
    }
    if (*o != '\0' && *o != '=') {
      return SST_FALSE;
    }
  }
  return SST_TRUE;
}
