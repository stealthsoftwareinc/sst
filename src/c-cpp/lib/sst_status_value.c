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

#include <sst/sst_status_value.h>
#include <sst/sst_status_value.h>

/* begin_includes */

#include <assert.h>
#include <src/sst_status_item.h>
#include <src/sst_status_item_ut.h>
#include <src/sst_status_list.h>
#include <sst/SST_ENABLE_INTERNAL_ERROR_CHECKS.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/SST_NULL_POINTER.h>
#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/SST_UNKNOWN.h>
#include <sst/sst_status.h>
#include <sst/sst_strchr.h>
#include <stdlib.h>

/* end_includes */

static int (compare_status_items_by_name)(
  void const * const status_item_1,
  void const * const status_item_2
) {
  #if (SST_ENABLE_INTERNAL_ERROR_CHECKS)
  {
    if (status_item_1 == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
    if (status_item_2 == NULL) {
      assert(!SST_NULL_POINTER);
      abort();
    }
  }
  #endif
  {
    char const * s1 = ((sst_status_item const *)status_item_1)->name;
    char const * s2 = ((sst_status_item const *)status_item_2)->name;
    #if (SST_ENABLE_INTERNAL_ERROR_CHECKS)
    {
      if (s1 == NULL) {
        assert(!SST_NULL_POINTER);
        abort();
      }
      if (s2 == NULL) {
        assert(!SST_NULL_POINTER);
        abort();
      }
    }
    #endif
    while (*s1 != '\0' && *s2 != '\0') {
      char const * const alphabet =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "_"
        "abcdefghijklmnopqrstuvwxyz"
      ;
      char const * const c1 = sst_strchr(alphabet, *s1);
      char const * const c2 = sst_strchr(alphabet, *s2);
      #if (SST_ENABLE_INTERNAL_ERROR_CHECKS)
      {
        if (c1 == NULL) {
          assert(!SST_INVALID_ARGUMENT);
          abort();
        }
        if (c2 == NULL) {
          assert(!SST_INVALID_ARGUMENT);
          abort();
        }
      }
      #endif
      if (c1 < c2) {
        return -1;
      }
      if (c1 > c2) {
        return 1;
      }
      ++s1;
      ++s2;
    }
    if (*s1 == '\0') {
      if (*s2 == '\0') {
        return 0;
      }
      return -1;
    }
    return 1;
  }
}

sst_status (sst_status_value)(
  char const * const s
) {
  if (s != NULL) {
    sst_status_item key;
    key.name = s;
    {
      sst_status_item const * const item = bsearch(
        &key,
        sst_status_list,
        SST_STATUS_MAXVAL + 1,
        sizeof(sst_status_item),
        compare_status_items_by_name
      );
      if (item != NULL) {
        return item->value;
      }
    }
  }
  return SST_UNKNOWN;
}
