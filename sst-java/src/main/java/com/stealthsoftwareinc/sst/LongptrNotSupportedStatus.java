/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.LongptrNotSupportedStatus</code>
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
 * Thrown when a method is not supported because native pointers cannot
 * be represented by the
 * <code>long</code>
 * type.
 * <p>
 * This class corresponds to the
 * <code>SST_LONGPTR_NOT_SUPPORTED</code>
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

public class LongptrNotSupportedStatus
extends NotSupportedStatus
{

/**
 * Constructs a
 * <code>LongptrNotSupportedStatus</code>
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

public LongptrNotSupportedStatus(
) {
  this(null);
}

/**
 * Constructs a
 * <code>LongptrNotSupportedStatus</code>
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

public LongptrNotSupportedStatus(
  final String message
) {
  super(message);
}

}
