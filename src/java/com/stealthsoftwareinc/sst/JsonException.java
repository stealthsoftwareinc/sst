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

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;

import java.io.File;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.nio.file.Path;
import java.util.List;
import java.util.Map;
import java.util.Set;

public final class JsonException extends RuntimeException {

  private static final class Verbatim {}
  private static final Verbatim verbatim = null;
  private JsonException(final String tail,
                        final Throwable cause,
                        final Verbatim verbatim) {
    super(tail, cause);
  }

  //--------------------------------------------------------------------

  public JsonException(final CharSequence tail) {
    this(": " + Exceptions.checkMessage(tail), null, verbatim);
  }

  private static String tailMessage(final Throwable tail) {
    SST_ASSERT(tail != null);
    SST_ASSERT(!(tail instanceof JsonException));
    final String m = tail.getLocalizedMessage();
    return m != null ? m : tail.toString();
  }

  public JsonException(final Throwable tail) {
    this(": " + tailMessage(tail), tail, verbatim);
  }

  public JsonException(final CharSequence head, final Throwable tail) {
    this(Exceptions.checkMessage(head) + ": " + tailMessage(tail),
         tail,
         verbatim);
  }

  //--------------------------------------------------------------------
  // "Value is missing" exceptions
  //--------------------------------------------------------------------

  public static final JsonException expectedValue() {
    return new JsonException("Value is missing");
  }

  //--------------------------------------------------------------------
  // "Value must be a string" exceptions
  //--------------------------------------------------------------------

  public static final JsonException expectedType(final String type) {
    return new JsonException("Value must be a string");
  }

  public static final JsonException expectedString() {
    return expectedType((String)null);
  }

  //--------------------------------------------------------------------
  // "Value must be an integer" exceptions
  //--------------------------------------------------------------------

  public static final JsonException expectedType(final Boolean type) {
    return new JsonException("Value must be an integer");
  }

  public static final JsonException expectedType(final Byte type) {
    return expectedType((Boolean)null);
  }

  public static final JsonException expectedType(final Short type) {
    return expectedType((Boolean)null);
  }

  public static final JsonException expectedType(final Integer type) {
    return expectedType((Boolean)null);
  }

  public static final JsonException expectedType(final Long type) {
    return expectedType((Boolean)null);
  }

  public static final JsonException
  expectedType(final BigInteger type) {
    return expectedType((Boolean)null);
  }

  public static final JsonException expectedInteger() {
    return expectedType((Boolean)null);
  }

  //--------------------------------------------------------------------
  // "Value must be a real number" exceptions
  //--------------------------------------------------------------------

  public static final JsonException expectedType(final Float type) {
    return new JsonException("Value must be a real number");
  }

  public static final JsonException expectedType(final Double type) {
    return expectedType((Float)null);
  }

  public static final JsonException
  expectedType(final BigDecimal type) {
    return expectedType((Float)null);
  }

  public static final JsonException expectedReal() {
    return expectedType((Float)null);
  }

  //--------------------------------------------------------------------
  // "Value must be an array" exceptions
  //--------------------------------------------------------------------

  public static final JsonException expectedType(final List<?> type) {
    return new JsonException("Value must be an array");
  }

  public static final JsonException expectedType(final Set<?> type) {
    return expectedType((List<?>)null);
  }

  public static final JsonException expectedArray() {
    return expectedType((List<?>)null);
  }

  //--------------------------------------------------------------------
  // "Value must be an object" exceptions
  //--------------------------------------------------------------------

  public static final JsonException
  expectedType(final Map<String, ?> type) {
    return new JsonException("Value must be an object");
  }

  public static final JsonException expectedObject() {
    return expectedType((Map<String, ?>)null);
  }

  //--------------------------------------------------------------------

  public final JsonException add(final CharSequence head) {
    SST_ASSERT(head != null);
    return new JsonException(head + getLocalizedMessage(),
                             this,
                             verbatim);
  }

  //--------------------------------------------------------------------

  public final JsonException addIndex(final long i) {
    SST_ASSERT(i >= 0);
    return add("[" + i + "]");
  }

  public final JsonException addIndex(final BigInteger i) {
    SST_ASSERT(i != null);
    SST_ASSERT(i.signum() >= 0);
    return add("[" + i + "]");
  }

  //--------------------------------------------------------------------

  public final JsonException addKey(final CharSequence key) {
    SST_ASSERT(key != null);
    return add("." + Json.smartQuoteKey(key));
  }

  //--------------------------------------------------------------------

  public final JsonException addFile(final CharSequence file) {
    SST_ASSERT(file != null);
    return add(Json.smartQuote(file)
               + (getLocalizedMessage().startsWith(":") ? "" : ": "));
  }

  public final JsonException addFile(final File file) {
    SST_ASSERT(file != null);
    return addFile(file.toString());
  }

  public final JsonException addFile(final Path file) {
    SST_ASSERT(file != null);
    return addFile(file.toString());
  }
}
