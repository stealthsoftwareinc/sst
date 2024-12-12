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

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import java.util.Map;
import java.util.TreeMap;

/**
 * Thrown when a URI query string is invalid.
 */

public class QueryStringException
    extends RuntimeException implements ToJson {
  private final String queryString_;
  private final int spanLeft_;
  private final int spanRight_;

  public QueryStringException(final CharSequence message,
                              final Throwable cause,
                              final CharSequence queryString,
                              final int spanLeft,
                              final int spanRight) {
    super(Exceptions.checkMessage(message), cause);
    if (!SST_NDEBUG) {
      if (queryString == null) {
        SST_ASSERT(spanLeft == 0);
        SST_ASSERT(spanRight == 0);
      } else {
        SST_ASSERT(spanLeft >= 0);
        SST_ASSERT(spanLeft <= queryString.length());
        SST_ASSERT(spanRight >= spanLeft);
        SST_ASSERT(spanRight <= queryString.length());
      }
    }
    if (queryString == null) {
      queryString_ = null;
    } else {
      queryString_ = queryString.toString();
    }
    spanLeft_ = spanLeft;
    spanRight_ = spanRight;
  }

  public QueryStringException(final CharSequence message,
                              final CharSequence queryString,
                              final int spanLeft,
                              final int spanRight) {
    this(message, null, queryString, spanLeft, spanRight);
  }

  public QueryStringException(final Throwable cause,
                              final CharSequence queryString,
                              final int spanLeft,
                              final int spanRight) {
    this(Exceptions.checkCause(cause).getMessage(),
         cause,
         queryString,
         spanLeft,
         spanRight);
  }

  public QueryStringException(final CharSequence message,
                              final Throwable cause,
                              final CharSequence queryString) {
    this(message, cause, queryString, 0, 0);
  }

  public QueryStringException(final CharSequence message,
                              final CharSequence queryString) {
    this(message, queryString, 0, 0);
  }

  public QueryStringException(final Throwable cause,
                              final CharSequence queryString) {
    this(cause, queryString, 0, 0);
  }

  public QueryStringException(final CharSequence message,
                              final Throwable cause) {
    this(message, cause, null);
  }

  public QueryStringException(final CharSequence message) {
    this(message, (CharSequence)null);
  }

  public QueryStringException(final Throwable cause) {
    this(cause, null);
  }

  public String queryString() {
    return queryString_;
  }

  public int spanLeft() {
    return spanLeft_;
  }

  public int spanRight() {
    return spanRight_;
  }

  @Override
  public Map<String, Object> toJson() {
    final Map<String, Object> json = new TreeMap<String, Object>();
    json.put("error", "invalid_query_string");
    json.put("message", getMessage());
    if (queryString_ != null) {
      json.put("qs_body", queryString_);
      if (spanLeft_ < spanRight_) {
        final StringBuilder span = new StringBuilder();
        int i = 0;
        for (; i != spanLeft_; ++i) {
          span.append(' ');
        }
        for (; i != spanRight_; ++i) {
          span.append('^');
        }
        json.put("qs_span", span.toString());
        json.put("qs_span_left", Integer.valueOf(spanLeft_));
        json.put("qs_span_right", Integer.valueOf(spanRight_));
      }
    }
    return json;
  }
}
