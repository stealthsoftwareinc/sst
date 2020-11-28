/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_pull_short_option_a</code>
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

#ifndef SST_SST_PULL_SHORT_OPTION_A_H
#define SST_SST_PULL_SHORT_OPTION_A_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>

/* end_includes */

/**
 *
 * @available
 * always
 *
 * @see <code>::sst_pull_short_option_w</code>
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

SST_PUBLIC_C_FUNCTION sst_bool (sst_pull_short_option_a)(
  char * *,
  char const * const *,
  char const * const *
);

#else

sst_bool sst_pull_short_option_a(
  char * * argv,
  char const * const * otrv,
  char const * const * otp
);

#endif

#endif
