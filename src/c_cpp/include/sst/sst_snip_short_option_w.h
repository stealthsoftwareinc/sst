/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_snip_short_option_w</code>
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

#ifndef SST_SST_SNIP_SHORT_OPTION_W_H
#define SST_SST_SNIP_SHORT_OPTION_W_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <stddef.h>

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
 * @see <code>::sst_snip_short_option_a</code>
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

SST_PUBLIC_C_FUNCTION wchar_t * (sst_snip_short_option_w)(
  wchar_t const *,
  wchar_t const *
);

#else

wchar_t * sst_snip_short_option_w(
  wchar_t const * arg,
  wchar_t const * opt
);

#endif

#endif
