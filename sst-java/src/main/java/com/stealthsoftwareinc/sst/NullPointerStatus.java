/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.NullPointerStatus</code>
 * Java class.
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import java.lang.String;

/* end_imports */

/**
 * Thrown when a method is called incorrectly and the call could be more
 * correct if a null reference argument or a null native pointer
 * argument had a different value.
 * <p>
 * This class corresponds to the
 * <code>SST_NULL_POINTER</code>
 * status code.
 * For more information, see the Status Codes section of the SST manual.
 * </p>
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public class NullPointerStatus
extends InvalidPointerStatus
{

/**
 * Constructs a
 * <code>NullPointerStatus</code>
 * exception without a detail message and with an uninitialized cause.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public NullPointerStatus(
) {
  this(null);
}

/**
 * Constructs a
 * <code>NullPointerStatus</code>
 * exception with or without a detail message and with an uninitialized
 * cause.
 *
 * @param message
 * the detail message, or
 * <code>null</code>
 * for no detail message
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public NullPointerStatus(
  final String message
) {
  super(message);
}

}
