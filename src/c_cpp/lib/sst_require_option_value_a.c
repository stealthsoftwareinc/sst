/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_require_option_value_a.h>
#include <sst/sst_require_option_value_a.h>

/* begin_includes */

#include <sst/sst_crop_option_a.h>
#include <sst/sst_get_option_value_a.h>
#include <sst/sst_is_valued_short_option_a.h>
#include <sst/sst_option_pair_a.h>
#include <sst/sst_option_pair_a_ut.h>
#include <stddef.h>

/* end_includes */

sst_option_pair_a (sst_require_option_value_a)(
  char * * * const argv,
  char const * const opt
) {
  sst_option_pair_a opp = {0};
  if (argv != NULL && *argv != NULL) {
    opp.sst_value = sst_get_option_value_a(*argv, opt);
    if (sst_is_valued_short_option_a((*argv)[0], opt)) {
      opp.sst_name = opp.sst_buffer;
      opp.sst_buffer[0] = (*argv)[0][0];
      opp.sst_buffer[1] = (*argv)[0][1];
    } else {
      opp.sst_name = sst_crop_option_a((*argv)[0], opt);
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
