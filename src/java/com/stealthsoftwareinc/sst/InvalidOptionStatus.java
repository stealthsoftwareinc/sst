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
 * <code>com.stealthsoftwareinc.sst.InvalidOptionStatus</code>
 * Java class.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

/* end_imports */

/**
 * Thrown when a
 * <code>main</code>-like
 * method is given an invalid command-line option.
 * <p>
 * This class corresponds to the
 * <code>SST_INVALID_OPTION</code>
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

public class InvalidOptionStatus extends InvalidArgumentStatus {

  /**
 * Constructs an
 * <code>InvalidOptionStatus</code>
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

  public InvalidOptionStatus() {
  }

  /**
 * Constructs an
 * <code>InvalidOptionStatus</code>
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

  public InvalidOptionStatus(final CharSequence message) {
    super(message);
  }

  public InvalidOptionStatus(final CharSequence message,
                             final Throwable cause) {
    super(message, cause);
  }

  public InvalidOptionStatus(final Throwable cause) {
    super(cause);
  }
}
