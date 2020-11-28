/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_require_option_value_w</code>
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

#ifndef SST_SST_REQUIRE_OPTION_VALUE_W_H
#define SST_SST_REQUIRE_OPTION_VALUE_W_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_option_pair_w.h>
#include <stddef.h>

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
 * @see <code>::sst_require_option_value_a</code>
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

SST_PUBLIC_C_FUNCTION sst_option_pair_w (sst_require_option_value_w)(
  wchar_t * * *,
  wchar_t const *
);

#else

sst_option_pair_w sst_require_option_value_w(
  wchar_t * * * argv,
  wchar_t const * opt
);

#endif

#endif
