/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_pull_long_option_w</code>
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

#ifndef SST_SST_PULL_LONG_OPTION_W_H
#define SST_SST_PULL_LONG_OPTION_W_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

/**
 *
 * @available
 * always
 *
 * @see <code>::sst_pull_long_option_a</code>
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

SST_PUBLIC_C_FUNCTION sst_bool (sst_pull_long_option_w)(
  wchar_t * *,
  wchar_t const * const *,
  wchar_t const * const *
);

#else

sst_bool sst_pull_long_option_w(
  wchar_t * * argv,
  wchar_t const * const * otrv,
  wchar_t const * const * otp
);

#endif

#endif
