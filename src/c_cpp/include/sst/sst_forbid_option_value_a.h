/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_forbid_option_value_a</code>
 * function.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_FORBID_OPTION_VALUE_A_H
#define SST_SST_FORBID_OPTION_VALUE_A_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_option_pair_a.h>

/* end_includes */

/**
 *
 * @param argv
 *
 * @param opt
 *
 * @return
 *
 * @available
 * always
 *
 * @see <code>::sst_forbid_option_value_w</code>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION sst_option_pair_a (sst_forbid_option_value_a)(
  char * * *,
  char const *
);

#else

sst_option_pair_a sst_forbid_option_value_a(
  char * * * argv,
  char const * opt
);

#endif

#endif
