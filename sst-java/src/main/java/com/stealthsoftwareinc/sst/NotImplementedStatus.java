/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.NotImplementedStatus</code>
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
 * Thrown when part of a method is not yet implemented.
 * <p>
 * This class corresponds to the
 * <code>SST_NOT_IMPLEMENTED</code>
 * status code.
 * For more information, see the Status Codes section of the SST manual.
 * </p>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public class NotImplementedStatus
extends InternalErrorStatus
{

/**
 * Constructs a
 * <code>NotImplementedStatus</code>
 * exception without a detail message and with an uninitialized cause.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public NotImplementedStatus(
) {
  this(null);
}

/**
 * Constructs a
 * <code>NotImplementedStatus</code>
 * exception with or without a detail message and with an uninitialized
 * cause.
 *
 * @param message
 * the detail message, or
 * <code>null</code>
 * for no detail message
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public NotImplementedStatus(
  final String message
) {
  super(message);
}

}
