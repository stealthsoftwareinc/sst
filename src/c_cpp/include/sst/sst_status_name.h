/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_status_name</code>
 * function.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_STATUS_NAME_H
#define SST_SST_STATUS_NAME_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_status.h>

/* end_includes */

/**
 * Maps the value of a status code to the name of the status code.
 *
 * @param s
 * the value of a status code.
 * If
 * <code>s</code>
 * is larger than
 * <code>::SST_STATUS_MAXVAL</code>,
 * then the function behaves as if
 * <code>s</code>
 * were
 * <code>::SST_UNKNOWN</code>.
 *
 * @return
 * a pointer to a string with static storage duration that holds the
 * name of the status code.
 * If the program attempts to modify the string, then the behavior is
 * undefined.
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
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION char const * (sst_status_name)(
  sst_status
);

#else

char const * sst_status_name(
  sst_status s
);

#endif

#endif
