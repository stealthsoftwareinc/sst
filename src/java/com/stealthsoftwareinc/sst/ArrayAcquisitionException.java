//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

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
    extends NativeInterfaceException {

  public ArrayAcquisitionException() {
  }

  public ArrayAcquisitionException(final CharSequence message) {
    super(message);
  }

  public ArrayAcquisitionException(final CharSequence message,
                                   final Throwable cause) {
    super(message, cause);
  }

  public ArrayAcquisitionException(final Throwable cause) {
    super(cause);
  }
}
