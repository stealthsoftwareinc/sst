/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ZeroArraySizeStatus</code>
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
 * correct if an argument that specifies the number of elements in an
 * array were not zero.
 * <p>
 * This class corresponds to the
 * <code>SST_ZERO_ARRAY_SIZE</code>
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

public class ZeroArraySizeStatus
extends InvalidArraySizeStatus
{

/**
 * Constructs a
 * <code>ZeroArraySizeStatus</code>
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

public ZeroArraySizeStatus(
) {
  this(null);
}

/**
 * Constructs a
 * <code>ZeroArraySizeStatus</code>
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

public ZeroArraySizeStatus(
  final String message
) {
  super(message);
}

}
