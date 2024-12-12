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

public final class JdbcName implements ToJson {
  private String name_;
  private String underlyingName_;

  //--------------------------------------------------------------------
  // JSON representation
  //--------------------------------------------------------------------

  private static final String NAME_KEY = "name";
  private static final String UNDERLYING_NAME_KEY = "underlying_name";

  private void createFromJson(final String src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    name_ = src;
    underlyingName_ = src;
  }

  private void createFromJson(final Map<String, ?> src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(src != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final boolean haveName = Json.contains(src, NAME_KEY);
    final boolean haveUnderlyingName =
        Json.contains(src, UNDERLYING_NAME_KEY);
    if (!haveName && !haveUnderlyingName) {
      throw new JsonException("at least one of ."
                              + Json.smartQuoteKey(NAME_KEY) + " and ."
                              + Json.smartQuoteKey(UNDERLYING_NAME_KEY)
                              + " must be present");
    }
    if (haveName) {
      name_ = Json.removeAs(src, NAME_KEY, name_);
    }
    if (haveUnderlyingName) {
      underlyingName_ =
          Json.removeAs(src, UNDERLYING_NAME_KEY, underlyingName_);
    }
    if (!haveName) {
      name_ = underlyingName_;
    }
    if (!haveUnderlyingName) {
      underlyingName_ = name_;
    }
    Json.unknownKey(src);
  }

  private JdbcName(final Object src,
                   final CreateFromJson<JdbcName> createFromJsonTag) {
    if (Json.isString(src)) {
      createFromJson(Json.castToString(src));
    } else if (Json.isObject(src)) {
      createFromJson(Json.copy(Json.castToObject(src)));
    } else {
      throw new JsonException("value must be a string or an object");
    }
  }

  public static final CreateFromJson<JdbcName> fromJson() {
    return new CreateFromJson<JdbcName>() {
      @Override
      public final JdbcName createFromJson(final Object src) {
        return new JdbcName(src, this);
      }
    };
  }

  @Override
  public final Object toJson() {
    if (name_.equals(underlyingName_)) {
      return name_;
    } else {
      final Map<String, Object> dst = new HashMap<String, Object>();
      dst.put(NAME_KEY, Json.getFrom(name_));
      dst.put(UNDERLYING_NAME_KEY, Json.getFrom(underlyingName_));
      return dst;
    }
  }

  //--------------------------------------------------------------------
  // Getters
  //--------------------------------------------------------------------

  public final String name() {
    return name_;
  }

  public final String underlyingName() {
    return underlyingName_;
  }

  //--------------------------------------------------------------------
}
