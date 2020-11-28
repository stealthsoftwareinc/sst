/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 */

/* begin_includes */

#include <sst/sst_forbid_option_value_w.h>
#include <sst/sst_option_pair_w.h>
#include <sst/sst_option_pair_w_ut.h>
#include <stddef.h>
#include <TEST_EXIT.h>

/* end_includes */

#ifndef SST_DOXYGEN

int main(
  void
) {
  sst_option_pair_w const opp =
    sst_forbid_option_value_w(NULL, NULL)
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