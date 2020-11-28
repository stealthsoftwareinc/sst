/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_option_pair</code>
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

#ifndef SST_SST_OPTION_PAIR_H
#define SST_SST_OPTION_PAIR_H

#include <sst/sst_option_pair_a.h>
#include <sst/sst_option_pair_w.h>

/**
 * Expands to
 * <code>::sst_option_pair_w</code>
 * if the
 * <code>SST_UNICODE</code>
 * macro is defined, or to
 * <code>::sst_option_pair_a</code>
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
  #define sst_option_pair sst_option_pair_w
#else
  #define sst_option_pair sst_option_pair_a
#endif

#else

#define sst_option_pair ...

#endif

#endif
