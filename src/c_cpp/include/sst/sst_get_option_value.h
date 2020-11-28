/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_get_option_value</code>
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

#ifndef SST_SST_GET_OPTION_VALUE_H
#define SST_SST_GET_OPTION_VALUE_H

#include <sst/sst_get_option_value_a.h>
#include <sst/sst_get_option_value_w.h>

/**
 * Expands to
 * <code>::sst_get_option_value_w</code>
 * if the
 * <code>SST_UNICODE</code>
 * macro is defined, or to
 * <code>::sst_get_option_value_a</code>
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
  #define sst_get_option_value sst_get_option_value_w
#else
  #define sst_get_option_value sst_get_option_value_a
#endif

#else

#define sst_get_option_value ...

#endif

#endif
