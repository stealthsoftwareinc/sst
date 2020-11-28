/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_status_ec</code>
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

#ifndef SST_SST_STATUS_EC_H
#define SST_SST_STATUS_EC_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_status.h>

/* end_includes */

/**
 * Maps a status code that implies
 * <code>::SST_FAILURE</code>
 * to the slash-delimited fully qualified name of the corresponding Java
 * exception class.
 *
 * @param s
 * a status code.
 * If
 * <code>s</code>
 * is larger than
 * <code>::SST_STATUS_MAXVAL</code>
 * or does not imply
 * <code>::SST_FAILURE</code>,
 * then it is implicitly adjusted to
 * <code>::SST_FAILURE</code>.
 *
 * @return
 * a pointer to a string with static storage duration that holds the
 * slash-delimited fully qualified name of the Java exception class that
 * corresponds
 * to&nbsp;<code>s</code>.
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
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ul>
 * <li>
 * This function was updated to actually return the appropriate Java
 * exception class names.
 * Prior to this version, this function would simply return
 * <code>"java/lang/RuntimeException"</code>
 * as a placeholder.
 * </li>
 * </ul>
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION char const * (sst_status_ec)(
  sst_status
);

#else

char const * sst_status_ec(
  sst_status s
);

#endif

#endif
