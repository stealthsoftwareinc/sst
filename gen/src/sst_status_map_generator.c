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

/* begin_includes */

#include <src/sst_status_item.h>
#include <src/sst_status_item_ut.h>
#include <src/sst_status_list.h>
#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/sst_status.h>
#include <stdio.h>
#include <stdlib.h>

/* end_includes */

int (main)(
  void
) {
  {
    sst_status i;
    for (i = 0; i != SST_STATUS_MAXVAL + 1; ++i) {
      sst_status j;
      for (j = 0; j != SST_STATUS_MAXVAL + 1; ++j) {
        if (sst_status_list[j].value == i) {
          if (printf("%lu,\n", j) < 0) {
            (void)fprintf(stderr,
              "sst_status_map_generator! "
              "error writing to standard output\n"
            );
            return EXIT_FAILURE;
          }
          break;
        }
      }
    }
  }
  if (fflush(stdout) != 0) {
    (void)fprintf(stderr,
      "sst_status_map_generator! "
      "error writing to standard output\n"
    );
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
