/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_option_pair_ut</code>
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

#ifndef SST_SST_OPTION_PAIR_UT_H
#define SST_SST_OPTION_PAIR_UT_H

#include <sst/sst_option_pair_a_ut.h>
#include <sst/sst_option_pair_w_ut.h>

/**
 * Expands to
 * <code>::sst_option_pair_w_ut</code>
 * if the
 * <code>SST_UNICODE</code>
 * macro is defined, or to
 * <code>::sst_option_pair_a_ut</code>
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
  #define sst_option_pair_ut sst_option_pair_w_ut
#else
  #define sst_option_pair_ut sst_option_pair_a_ut
#endif

#else

#define sst_option_pair_ut ...

#endif

#endif
