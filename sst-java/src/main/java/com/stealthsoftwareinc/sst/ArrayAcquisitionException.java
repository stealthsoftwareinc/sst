/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ArrayAcquisitionException</code>
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
 * Thrown when a native method fails to acquire a Java array.
 * <p>
 * </p>
 * <ul>
 * <li>
 * <code>GetBooleanArrayElements</code>
 * </li>
 * <li>
 * <code>GetByteArrayElements</code>
 * </li>
 * <li>
 * <code>GetCharArrayElements</code>
 * </li>
 * <li>
 * <code>GetDoubleArrayElements</code>
 * </li>
 * <li>
 * <code>GetFloatArrayElements</code>
 * </li>
 * <li>
 * <code>GetIntArrayElements</code>
 * </li>
 * <li>
 * <code>GetLongArrayElements</code>
 * </li>
 * <li>
 * <code>GetPrimitiveArrayCritical</code>
 * </li>
 * <li>
 * <code>GetShortArrayElements</code>
 * </li>
 * <li>
 * <code>GetStringChars</code>
 * </li>
 * <li>
 * <code>GetStringCritical</code>
 * </li>
 * <li>
 * <code>GetStringUTFChars</code>
 * </li>
 * </ul>
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public class ArrayAcquisitionException
extends NativeInterfaceException
{

/**
 * Constructs an
 * <code>ArrayAcquisitionException</code>
 * without a detail message and with an uninitialized cause.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public ArrayAcquisitionException(
) {
  this(null);
}

/**
 * Constructs an
 * <code>ArrayAcquisitionException</code>
 * with or without a detail message and with an uninitialized cause.
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

public ArrayAcquisitionException(
  final String message
) {
  super(message);
}

}
