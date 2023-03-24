//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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

public final class Assert {
  private Assert() {
  }

  public static final boolean SST_NDEBUG = false;
  public static final boolean SST_ASSERT_THROWS = false;

  public static final void SST_ASSERT(final Throwable e,
                                      final CharSequence message) {
    if (!SST_NDEBUG) {
      if (SST_ASSERT_THROWS) {
        throw new AssertionError(
            "assertion failed: "
                + (message != null ? message.toString() + ": " : ""),
            e);
      }
      if (e == null) {
        try {
          SST_ASSERT(new AssertionError(
              "assertion failed"
                  + (message != null ? ": " + message.toString() : ""),
              null));
        } catch (final Throwable e2) {
          SST_ASSERT(e2);
        }
      }
      try {
        synchronized (System.err) {
          e.printStackTrace();
          System.err.flush();
        }
      } catch (final Throwable e2) {
      }
      try {
        Runtime.getRuntime().halt(1);
      } catch (final Throwable e2) {
      }
      System.exit(1);
    }
  }

  public static final void SST_ASSERT(final Throwable e) {
    SST_ASSERT(e, null);
  }

  public static final void SST_ASSERT(final boolean x,
                                      final CharSequence message) {
    if (!SST_NDEBUG) {
      if (!x) {
        SST_ASSERT((Throwable)null, message);
      }
    }
  }

  public static final void SST_ASSERT(final boolean x) {
    SST_ASSERT(x, null);
  }

  public static final void SST_ASSERT(final ThrowingRunnable f,
                                      final CharSequence message) {
    if (!SST_NDEBUG) {
      SST_ASSERT(f != null);
      try {
        f.run();
      } catch (final Throwable e) {
        SST_ASSERT(e, message);
      }
    }
  }

  public static final void SST_ASSERT(final ThrowingRunnable f) {
    SST_ASSERT(f, null);
  }
}
