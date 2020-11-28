/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_is_unvalued_long_option</code>
 * macro.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_IS_UNVALUED_LONG_OPTION_H
#define SST_SST_IS_UNVALUED_LONG_OPTION_H

#include <sst/sst_is_unvalued_long_option_a.h>
#include <sst/sst_is_unvalued_long_option_w.h>

/**
 * Expands to
 * <code>::sst_is_unvalued_long_option_w</code>
 * if the
 * <code>SST_UNICODE</code>
 * macro is defined, or to
 * <code>::sst_is_unvalued_long_option_a</code>
 * if not.
 *
 * @available
 * always
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
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
  #define sst_is_unvalued_long_option sst_is_unvalued_long_option_w
#else
  #define sst_is_unvalued_long_option sst_is_unvalued_long_option_a
#endif

#else

#define sst_is_unvalued_long_option ...

#endif

#endif
