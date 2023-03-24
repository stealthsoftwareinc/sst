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

public final class ConfigPartition {

  public static final ConfigPredicate DEFAULT_NAME_PREDICATE;
  public static final ConfigPredicate DEFAULT_VALUE_PREDICATE;
  public static final String DEFAULT_DEFAULT_VALUE = "";

  static {
    DEFAULT_NAME_PREDICATE = new ConfigPredicate() {
      @Override
      public final boolean test(final CharSequence input) {
        return true;
      }
    };
    DEFAULT_VALUE_PREDICATE = new ConfigPredicate() {
      @Override
      public final boolean test(final CharSequence input) {
        return true;
      }
    };
  }

  public final ConfigPredicate namePredicate;
  public final ConfigPredicate valuePredicate;
  public final String defaultValue;

  public ConfigPartition(final ConfigPredicate namePredicate,
                         final ConfigPredicate valuePredicate,
                         final CharSequence defaultValue) {
    if (namePredicate == null) {
      this.namePredicate = DEFAULT_NAME_PREDICATE;
    } else {
      this.namePredicate = namePredicate;
    }
    if (valuePredicate == null) {
      this.valuePredicate = DEFAULT_VALUE_PREDICATE;
    } else {
      this.valuePredicate = valuePredicate;
    }
    if (defaultValue == null) {
      this.defaultValue = DEFAULT_DEFAULT_VALUE;
    } else {
      this.defaultValue = defaultValue.toString();
    }
    assert this.valuePredicate.test(this.defaultValue);
  }

  public ConfigPartition(final ConfigPredicate namePredicate,
                         final ConfigPredicate valuePredicate) {
    this(namePredicate, valuePredicate, null);
  }

  public ConfigPartition(final ConfigPredicate namePredicate,
                         final CharSequence defaultValue) {
    this(namePredicate, null, defaultValue);
  }

  public ConfigPartition(final ConfigPredicate namePredicate) {
    this(namePredicate, null, null);
  }

  public ConfigPartition(final CharSequence defaultValue) {
    this(null, null, defaultValue);
  }

  public ConfigPartition() {
    this(null, null, null);
  }
}
