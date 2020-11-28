/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
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
