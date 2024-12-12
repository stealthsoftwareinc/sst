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

/**
 * @file
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 */

/* begin_includes */

#include <sst/sst_forbid_option_value_a.h>
#include <sst/sst_option_pair_a.h>
#include <sst/sst_option_pair_a_ut.h>
#include <stddef.h>
#include <TEST_EXIT.h>

/* end_includes */

#ifndef SST_DOXYGEN

int main(
  void
) {
  sst_option_pair_a const opp =
    sst_forbid_option_value_a(NULL, NULL)
  ;
  if (opp.sst_name != NULL) {
    return TEST_EXIT_FAIL;
  }
  if (opp.sst_value != NULL) {
    return TEST_EXIT_FAIL;
  }
  if (opp.sst_buffer[0] != '\0') {
    return TEST_EXIT_FAIL;
  }
  if (opp.sst_buffer[1] != '\0') {
    return TEST_EXIT_FAIL;
  }
  if (opp.sst_buffer[2] != '\0') {
    return TEST_EXIT_FAIL;
  }
  return TEST_EXIT_PASS;
}

#endif
