/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_snip_long_option_a</code>
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

#ifndef SST_SST_SNIP_LONG_OPTION_A_H
#define SST_SST_SNIP_LONG_OPTION_A_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>

/* end_includes */

/**
 *
 * @param arg
 *
 * @param opt
 *
 * @return
 *
 * @available
 * always
 *
 * @see <code>::sst_snip_long_option_w</code>
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

SST_PUBLIC_C_FUNCTION char * (sst_snip_long_option_a)(
  char const *,
  char const *
);

#else

char * sst_snip_long_option_a(
  char const * arg,
  char const * opt
);

#endif

#endif
