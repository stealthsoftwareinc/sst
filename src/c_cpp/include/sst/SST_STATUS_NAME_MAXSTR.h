/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::SST_STATUS_NAME_MAXSTR</code>
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

#ifndef SST_SST_STATUS_NAME_MAXSTR_H
#define SST_SST_STATUS_NAME_MAXSTR_H

/**
 * A character string literal whose length (excluding the null
 * terminator) is
 * <code>::SST_STATUS_NAME_MAXLEN</code>.
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
 * This string was changed from
 * length&nbsp;31
 * to
 * length&nbsp;63.
 * </li>
 * <li>
 * This string was changed from a sequence of digits counting its length
 * to a visual placeholder.
 * </li>
 * </ul>
 *
 * @showinitializer
 */

#define SST_STATUS_NAME_MAXSTR "[-------------------SST_STATUS_NAME_MAXSTR--------------------]"

#endif
