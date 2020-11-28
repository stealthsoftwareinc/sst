/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_permit_option_value_w.h>
#include <sst/sst_permit_option_value_w.h>

/* begin_includes */

#include <sst/sst_crop_option_w.h>
#include <sst/sst_get_option_value_w.h>
#include <sst/sst_is_valued_short_option_w.h>
#include <sst/sst_option_pair_w.h>
#include <sst/sst_option_pair_w_ut.h>
#include <stddef.h>

/* end_includes */

sst_option_pair_w (sst_permit_option_value_w)(
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
    if (opp.sst_name != NULL) {
      if (opp.sst_value == (*argv)[1]) {
        opp.sst_value = NULL;
      }
      ++*argv;
    }
  }
  return opp;
}
