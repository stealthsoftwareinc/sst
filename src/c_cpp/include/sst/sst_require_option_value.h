/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_require_option_value</code>
 * macro.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_REQUIRE_OPTION_VALUE_H
#define SST_SST_REQUIRE_OPTION_VALUE_H

#include <sst/sst_require_option_value_a.h>
#include <sst/sst_require_option_value_w.h>

/**
 * Expands to
 * <code>::sst_require_option_value_w</code>
 * if the
 * <code>SST_UNICODE</code>
 * macro is defined, or to
 * <code>::sst_require_option_value_a</code>
 * if not.
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 *
 * @showinitializer
 */

#ifndef SST_DOXYGEN

#if (defined(SST_UNICODE))
  #define sst_require_option_value sst_require_option_value_w
#else
  #define sst_require_option_value sst_require_option_value_a
#endif

#else

#define sst_require_option_value ...

#endif

#endif
