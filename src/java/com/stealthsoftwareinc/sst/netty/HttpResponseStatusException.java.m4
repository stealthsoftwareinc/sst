dnl#
dnl# Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
dnl#
dnl# Permission is hereby granted, free of charge, to any person
dnl# obtaining a copy of this software and associated documentation
dnl# files (the "Software"), to deal in the Software without
dnl# restriction, including without limitation the rights to use,
dnl# copy, modify, merge, publish, distribute, sublicense, and/or
dnl# sell copies of the Software, and to permit persons to whom the
dnl# Software is furnished to do so, subject to the following
dnl# conditions:
dnl#
dnl# The above copyright notice and this permission notice (including
dnl# the next paragraph) shall be included in all copies or
dnl# substantial portions of the Software.
dnl#
dnl# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl# OTHER DEALINGS IN THE SOFTWARE.
dnl#
dnl# SPDX-License-Identifier: MIT
dnl#

include(`src/m4/config.m4')

changequote(`{|', `|}')

ifdef({|make_rules|}, {|{|
  |}make_target{|: src/m4/config.m4
|}|}, {|{|

package com.stealthsoftwareinc.sst.netty;

|}ifelse(WITH_NETTY, 1, {|{|

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import io.netty.handler.codec.http.HttpResponseStatus;

public class HttpResponseStatusException extends RuntimeException {
  private final HttpResponseStatus status_;

  private static final String
  getMessage(final HttpResponseStatus status) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(status != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return status.toString();
  }

  public HttpResponseStatusException(final HttpResponseStatus status,
                                     final Throwable cause) {
    super(getMessage(status), cause);
    status_ = status;
  }

  public HttpResponseStatusException(final HttpResponseStatus status) {
    this(status, null);
  }

  public final HttpResponseStatus status() {
    return status_;
  }
}

|}|}, {|{|

public final class HttpResponseStatusException {
  private HttpResponseStatusException() {
  }
}

|}|})|})
