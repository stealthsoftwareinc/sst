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

import java.util.HashMap;
import java.util.Map;

public final class HostAndPort implements ToJson {
  //--------------------------------------------------------------------
  // State
  //--------------------------------------------------------------------

  private String host_;
  private int port_;

  //--------------------------------------------------------------------
  // Constructor
  //--------------------------------------------------------------------

  public HostAndPort(final CharSequence host, final int port) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(host != null);
        SST_ASSERT(port >= 0);
        SST_ASSERT(port <= 65535);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    host_ = host.toString();
    port_ = port;
  }

  //--------------------------------------------------------------------
  // fromJson
  //--------------------------------------------------------------------

  private void createFromJson(final Map<String, ?> src,
                              final String defaultHost,
                              final Integer defaultPort) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
        if (defaultPort != null) {
          SST_ASSERT(defaultPort >= 0);
          SST_ASSERT(defaultPort <= 65535);
        }
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }

    if (defaultHost == null) {
      host_ = Json.removeAs(src, "host", host_);
    } else {
      host_ = Json.removeAs(src, "host", host_, defaultHost);
    }

    if (defaultPort == null) {
      port_ = Json.removeAs(src, "port", port_);
    } else {
      port_ = Json.removeAs(src, "port", port_, defaultPort);
    }
    try {
      if (port_ < 0) {
        throw new JsonException(
            "A port number must be "
            + "an integer between 0 and 65535 inclusive.");
      }
    } catch (final JsonException e) {
      throw e.addKey("port");
    }

    Json.unknownKey(src);
  }

  private HostAndPort(
      final Object src,
      final String defaultHost,
      final Integer defaultPort,
      final CreateFromJson<HostAndPort> createFromJsonTag) {
    if (!SST_NDEBUG) {
      try {
        if (defaultPort != null) {
          SST_ASSERT(defaultPort >= 0);
          SST_ASSERT(defaultPort <= 65535);
        }
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (src == null) {
      if (defaultHost == null || defaultPort == null) {
        throw JsonException.expectedObject();
      }
      host_ = defaultHost;
      port_ = defaultPort;
    } else {
      createFromJson(Json.copy(Json.expectObject(src)),
                     defaultHost,
                     defaultPort);
    }
  }

  public static final CreateFromJson<HostAndPort>
  fromJson(final String defaultHost, final Integer defaultPort) {
    if (!SST_NDEBUG) {
      try {
        if (defaultPort != null) {
          SST_ASSERT(defaultPort >= 0);
          SST_ASSERT(defaultPort <= 65535);
        }
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return new CreateFromJson<HostAndPort>() {
      @Override
      public final HostAndPort createFromJson(final Object src) {
        return new HostAndPort(src, defaultHost, defaultPort, this);
      }
    };
  }

  public static final CreateFromJson<HostAndPort> fromJson() {
    return fromJson(null, null);
  }

  //--------------------------------------------------------------------
  // toJson
  //--------------------------------------------------------------------

  @Override
  public final Object toJson() {
    final Map<String, Object> dst = new HashMap<String, Object>();
    dst.put("host", host_);
    dst.put("port", port_);
    return dst;
  }

  //--------------------------------------------------------------------
  // Getters
  //--------------------------------------------------------------------

  public final String host() {
    return host_;
  }

  public final int port() {
    return port_;
  }

  //--------------------------------------------------------------------
}
