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

import com.stealthsoftwareinc.sst.UncheckedException;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.DefaultFileRegion;
import io.netty.handler.codec.http.DefaultFullHttpResponse;
import io.netty.handler.codec.http.DefaultHttpResponse;
import io.netty.handler.codec.http.FullHttpResponse;
import io.netty.handler.codec.http.HttpHeaderNames;
import io.netty.handler.codec.http.HttpMethod;
import io.netty.handler.codec.http.HttpObject;
import io.netty.handler.codec.http.HttpRequest;
import io.netty.handler.codec.http.HttpResponse;
import io.netty.handler.codec.http.HttpResponseStatus;
import io.netty.handler.codec.http.HttpUtil;
import io.netty.handler.codec.http.HttpVersion;
import io.netty.handler.codec.http.LastHttpContent;
import java.io.File;
import java.net.URI;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public final class HttpDirectoryServerCore {
  private static final String ACCEPTABLE_PATH_REGEX =
      "^"
      + "/"
      + "([0-9A-Z_a-z][-.0-9A-Z_a-z]*/)*"
      + "([0-9A-Z_a-z][-.0-9A-Z_a-z]*)?"
      + "$";

  private final Path directory_;
  private final String prefix_;

  public HttpDirectoryServerCore(final CharSequence directory,
                                 final CharSequence prefix) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(directory != null);
        SST_ASSERT(prefix != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    directory_ = Paths.get(directory.toString());
    prefix_ = prefix.toString();
  }

  public HttpDirectoryServerCore(final CharSequence directory) {
    this(directory, "");
  }

  private static final String getContentType(final Path file) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(file != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final String x = file.toString();
    if (x.endsWith(".css")) {
      return "text/css; charset=UTF-8";
    }
    if (x.endsWith(".js")) {
      return "text/javascript; charset=UTF-8";
    }
    if (x.endsWith(".html")) {
      return "text/html; charset=UTF-8";
    }
    return null;
  }

  private final boolean handle(final ChannelHandlerContext ctx,
                               final HttpRequest request) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(ctx != null);
        SST_ASSERT(request != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try {
      final String path1 = new URI(request.uri()).getRawPath();
      if (path1 == null) {
        throw new HttpResponseStatusException(
            HttpResponseStatus.BAD_REQUEST);
      }
      if (!path1.startsWith(prefix_)) {
        return false;
      }
      final String path2 = path1.substring(prefix_.length());
      if (!path2.matches(ACCEPTABLE_PATH_REGEX)) {
        return false;
      }
      final HttpMethod method = request.method();
      if (method != HttpMethod.GET && method != HttpMethod.HEAD) {
        throw new HttpResponseStatusException(
            HttpResponseStatus.METHOD_NOT_ALLOWED);
      }
      final Path file;
      {
        final Path f = directory_.resolve(
            path2.substring(1).replace("/", File.separator));
        if (!Files.isDirectory(f)) {
          file = f;
        } else if (path1.endsWith("/")) {
          file = f.resolve("index.html");
        } else {
          final FullHttpResponse response =
              new DefaultFullHttpResponse(HttpVersion.HTTP_1_1,
                                          HttpResponseStatus.FOUND);
          HttpUtil.setKeepAlive(response.headers(),
                                response.protocolVersion(),
                                HttpUtil.isKeepAlive(request));
          response.headers().set(HttpHeaderNames.LOCATION, path1 + "/");
          ctx.writeAndFlush(response);
          return true;
        }
      }
      if (!Files.isRegularFile(file)) {
        throw new HttpResponseStatusException(
            HttpResponseStatus.NOT_FOUND);
      }
      final long size = Files.size(file);
      final HttpResponse response =
          new DefaultHttpResponse(HttpVersion.HTTP_1_1,
                                  HttpResponseStatus.OK);
      HttpUtil.setKeepAlive(response.headers(),
                            response.protocolVersion(),
                            HttpUtil.isKeepAlive(request));
      HttpUtil.setContentLength(response, size);
      final String contentType = getContentType(file);
      if (contentType != null) {
        response.headers().set(HttpHeaderNames.CONTENT_TYPE,
                               contentType);
      }
      ctx.write(response);
      if (method == HttpMethod.GET) {
        ctx.write(new DefaultFileRegion(file.toFile(), 0, size));
      }
      ctx.writeAndFlush(LastHttpContent.EMPTY_LAST_CONTENT);
      return true;
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  private boolean inRequest_ = false;

  public final boolean handle(final ChannelHandlerContext ctx,
                              final HttpObject object) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(ctx != null);
        SST_ASSERT(object != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (!inRequest_) {
      if (!(object instanceof HttpRequest)) {
        return false;
      }
      if (!handle(ctx, (HttpRequest)object)) {
        return false;
      }
      inRequest_ = true;
    }
    if (object instanceof LastHttpContent) {
      inRequest_ = false;
    }
    return true;
  }
}

|}|}, {|{|

public final class HttpDirectoryServerCore {
  private HttpDirectoryServerCore() {
  }
}

|}|})|})
