/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_option_pair_w_ut</code>
 * type.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_OPTION_PAIR_W_UT_H
#define SST_SST_OPTION_PAIR_W_UT_H

/* begin_includes */

#include <stddef.h>

/* end_includes */

/**
 * Represents an option that has been (attempted to be) parsed by the
 * <code>::sst_require_option_value_w</code>
 * function, the
 * <code>::sst_permit_option_value_w</code>
 * function, or the
 * <code>::sst_forbid_option_value_w</code>
 * function.
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
 */

struct sst_option_pair_w_ut {

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  wchar_t const * sst_name;

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  wchar_t const * sst_value;

  /**
   *
   * @available
   * always
   *
   * @since SST&nbsp;X.X.X (XXXX-XX-XX)
   */

  wchar_t sst_buffer[3];

};

typedef struct sst_option_pair_w_ut sst_option_pair_w_ut;

#endif
