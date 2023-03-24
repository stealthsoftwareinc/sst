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

#include <sst/sst_pull_option_a.h>
#include <sst/sst_pull_option_a.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_is_option_a.h>
#include <sst/sst_is_unvalued_option_a.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_pull_option_a)(
  char * * const argv,
  char const * const * const otrv,
  char const * const * const otp
) {
  if (argv == NULL) {
    return SST_FALSE;
  }
  {
    char * * p = argv;
    for (;;) {
      if (*p == NULL) {
        return SST_FALSE;
      }
      if (otp == NULL) {
        if (sst_is_option_a(*p, NULL)) {
          break;
        }
      } else {
        {
          char const * const * q;
          for (q = otp; *q != NULL; ++q) {
            if (sst_is_option_a(*p, *q)) {
              break;
            }
          }
          if (*q != NULL) {
            break;
          }
        }
        if (otrv != NULL) {
          char const * const * q;
          for (q = otrv; *q != NULL; ++q) {
            if (sst_is_unvalued_option_a(*p, *q)) {
              break;
            }
          }
          if (*q != NULL) {
            ++p;
            if (*p == NULL) {
              return SST_FALSE;
            }
          }
        }
      }
      ++p;
    }
    if (p != argv) {
      sst_bool pull_two_arguments = SST_FALSE;
      if (otrv != NULL) {
        char const * const * q;
        for (q = otrv; *q != NULL; ++q) {
          if (sst_is_unvalued_option_a(*p, *q)) {
            pull_two_arguments = SST_TRUE;
            break;
          }
        }
      }
      if (pull_two_arguments) {
        char * const a0 = p[0];
        char * const a1 = p[1];
        while (p != argv) {
          --p;
          p[2] = p[0];
        }
        argv[0] = a0;
        argv[1] = a1;
      } else {
        char * const a0 = p[0];
        while (p != argv) {
          --p;
          p[1] = p[0];
        }
        argv[0] = a0;
      }
    }
  }
  return SST_TRUE;
}
