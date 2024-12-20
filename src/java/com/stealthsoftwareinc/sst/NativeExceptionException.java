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

package com.stealthsoftwareinc.sst;

/**
 * Thrown when a native method fails to throw an exception.
 * <p>
 * A native method ultimately calls the
 * <code>Throw</code>
 * or
 * <code>ThrowNew</code>
 * functions from the Java Native Interface to throw an exception.
 * However, these functions may fail.
 * If the native method communicates these failures to the caller, then
 * the caller should normally throw a
 * <code>NativeExceptionException</code>
 * in response.
 * </p>
 * <p>
 * It is recommended to make all native methods that throw exceptions
 * return
 * <code>boolean</code>,
 * where
 * <code>true</code>
 * means that the method succeeded, and
 * <code>false</code>
 * means that the method failed and attempted to throw an exception.
 * Such a native method can be called from Java with roughly the
 * following code:
 * </p>
 *<!--code{.java}--><blockquote><pre>
 *if (!package.Class.method()) {
 *  throw (NativeExceptionException)
 *    new NativeExceptionException(
 *      "package." +
 *      "Class.method"
 *    ).initCause(null)
 *  ;
 *}
 *</pre></blockquote>
 * <p>
 * This code has three possible outcomes:
 * </p>
 * <ol>
 * <li>
 * If the method succeeds, then the
 * <code>if</code>&nbsp;block
 * is skipped.
 * </li>
 * <li>
 * If the method throws an exception, then the
 * <code>if</code>&nbsp;block
 * is preempted.
 * </li>
 * <li>
 * If the method fails to throw an exception, then the
 * <code>if</code>&nbsp;block
 * throws a
 * <code>NativeExceptionException</code>.
 * </li>
 * </ol>
 * <p>
 * Such a native method can also be called from another native method
 * that follows the same return value convention with roughly the
 * following
 * C&nbsp;code:
 * </p>
 *<!--code{.c}--><blockquote><pre>
 *if (!Java_package_Class_method(env, clazz)) {
 *  if (!(*env)-&gt;ExceptionCheck(env)) {
 *    char const * const ec =
 *      SST_EC_NATIVE_EXCEPTION_EXCEPTION
 *    ;
 *    char const * const em =
 *      "package."
 *      "Class.method"
 *    ;
 *    (void)sst_ThrowNew(env, ec, em, NULL);
 *  }
 *  return JNI_FALSE;
 *}
 *</pre></blockquote>
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public class NativeExceptionException extends NativeInterfaceException {

  public NativeExceptionException() {
  }

  /**
 * Constructs a
 * <code>NativeExceptionException</code>
 * with or without a detail message and with an uninitialized cause.
 *
 * @param message
 * the detail message, or
 * <code>null</code>
 * for no detail message.
 * This is conventionally the name of the native method that failed to
 * throw an exception, written like
 * <code>"package.Class.method"</code>.
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
 * This constructor was changed to accept an arbitrary detail message
 * instead of requiring it to be the name of the native method that
 * failed to throw an exception.
 * </li>
 * </ul>
 */

  public NativeExceptionException(final CharSequence message) {
    super(message);
  }

  public NativeExceptionException(final CharSequence message,
                                  final Throwable cause) {
    super(message, cause);
  }

  public NativeExceptionException(final Throwable cause) {
    super(cause);
  }
}
