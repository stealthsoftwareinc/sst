changequote(`{|', `|}')
ifdef({|make_rules|}, {||}, {|{|
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
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import java.io.IOException;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CoderResult;
import java.nio.charset.CodingErrorAction;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

public final class Json {
  private Json() {
  }

  //--------------------------------------------------------------------
  // Fundamental escape methods
  //--------------------------------------------------------------------

  public static final Appendable escape(final Appendable dst,
                                        final char src)
      throws IOException {
    if (dst == null) {
      return escape(new StringBuilder(), src);
    }
    switch (src) {
      case '"':
        return dst.append("\\\"");
      case '\\':
        return dst.append("\\\\");
      case '/':
        return dst.append("\\/");
      case '\b':
        return dst.append("\\b");
      case '\f':
        return dst.append("\\f");
      case '\n':
        return dst.append("\\n");
      case '\r':
        return dst.append("\\r");
      case '\t':
        return dst.append("\\t");
    }
    if (src >= ' ' && src <= '~') {
      return dst.append(src);
    }
    dst.append("\\u");
    final String digits = "0123456789ABCDEF";
    for (int i = 0; i != 4; ++i) {
      dst.append(digits.charAt((src >>> (12 - 4 * i)) & 0xF));
    }
    return dst;
  }

  public static final CharsetEncoder defaultEncodeEncoder() {
    final CharsetEncoder encoder;
    encoder = StandardCharsets.UTF_16BE.newEncoder();
    encoder.onMalformedInput(CodingErrorAction.REPORT);
    encoder.onUnmappableCharacter(CodingErrorAction.REPORT);
    return encoder;
  }

  public static final ByteBuffer defaultEncodeDstBuffer() {
    return ByteBuffer.allocate(1024);
  }

  public static final Appendable escape(final Appendable dst,
                                        final CharSequence src,
                                        final CharsetEncoder encoder,
                                        final ByteBuffer dstBuffer)
      throws IOException {
    if (dst == null) {
      return escape(new StringBuilder(), src, encoder, dstBuffer);
    }
    if (src == null) {
      return escape(dst, "", encoder, dstBuffer);
    }
    if (encoder == null) {
      for (int i = 0; i != src.length(); ++i) {
        escape(dst, src.charAt(i));
      }
      return dst;
    }
    if (!encoder.charset().name().equals("UTF-16BE")) {
      throw new InvalidArgumentStatus("encoder is not UTF-16BE", null);
    }
    if (dstBuffer == null) {
      return escape(dst, src, encoder, defaultEncodeDstBuffer());
    }
    encoder.reset();
    final CharBuffer srcBuffer = CharBuffer.wrap(src);
    dstBuffer.clear();
    boolean flush = false;
    while (true) {
      final CoderResult result;
      if (flush) {
        result = encoder.flush(dstBuffer);
      } else {
        result = encoder.encode(srcBuffer, dstBuffer, true);
      }
      dstBuffer.flip();
      while (dstBuffer.remaining() >= 2) {
        final int b1 = dstBuffer.get() & 0xFF;
        final int b2 = dstBuffer.get() & 0xFF;
        final int c = (b1 << 8) | b2;
        escape(dst, (char)c);
      }
      dstBuffer.compact();
      if (result.isUnderflow()) {
        if (flush) {
          if (dstBuffer.position() != 0) {
            throw new InternalErrorStatus(
                "encoder produced an unexpected number of bytes",
                null);
          }
          return dst;
        }
        flush = true;
      } else if (result.isOverflow()) {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw new InvalidArgumentStatus("dstBuffer is too small",
                                        cause);
      } else if (result.isMalformed()) {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw new ParseFailureStatus(
            "src contains an invalid sequence of code units",
            cause);
      } else if (result.isUnmappable()) {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw new InternalErrorStatus(
            "encoder failed with an unmappable-character error",
            cause);
      } else {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw new InternalErrorStatus("unknown CoderResult", cause);
      }
    }
  }

  //--------------------------------------------------------------------
  // Fundamental quote methods
  //--------------------------------------------------------------------

  public static final Appendable quote(final Appendable dst,
                                       final char src)
      throws IOException {
    if (dst == null) {
      return quote(new StringBuilder(), src);
    }
    dst.append('"');
    escape(dst, src);
    dst.append('"');
    return dst;
  }

  public static final Appendable quote(final Appendable dst,
                                       final CharSequence src,
                                       final CharsetEncoder encoder,
                                       final ByteBuffer dstBuffer)
      throws IOException {
    if (dst == null) {
      return quote(new StringBuilder(), src, encoder, dstBuffer);
    }
    dst.append('"');
    escape(dst, src, encoder, dstBuffer);
    dst.append('"');
    return dst;
  }

  //--------------------------------------------------------------------
  // Convenience escape and quote methods
  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    public static final StringBuilder $1(final StringBuilder dst,
                                         final char src) {
      try {
        return (StringBuilder)$1((Appendable)dst, src);
      } catch (final IOException e) {
        throw new InternalErrorStatus(
            "StringBuilder threw an IOException",
            e);
      }
    }

    public static final String $1(final char src) {
      return $1((StringBuilder)null, src).toString();
    }

    public static final Appendable $1(final Appendable dst,
                                      final CharSequence src,
                                      final boolean recode)
        throws IOException {
      return $1(dst, src, recode ? defaultEncodeEncoder() : null, null);
    }

    public static final Appendable $1(final Appendable dst,
                                      final CharSequence src)
        throws IOException {
      return $1(dst, src, true);
    }

    public static final StringBuilder $1(final StringBuilder dst,
                                         final CharSequence src,
                                         final CharsetEncoder encoder,
                                         final ByteBuffer dstBuffer) {
      try {
        return (
            StringBuilder)$1((Appendable)dst, src, encoder, dstBuffer);
      } catch (final IOException e) {
        throw new InternalErrorStatus(
            "StringBuilder threw an IOException",
            e);
      }
    }

    public static final StringBuilder $1(final StringBuilder dst,
                                         final CharSequence src,
                                         final boolean recode) {
      try {
        return (StringBuilder)$1((Appendable)dst, src, recode);
      } catch (final IOException e) {
        throw new InternalErrorStatus(
            "StringBuilder threw an IOException",
            e);
      }
    }

    public static final StringBuilder $1(final StringBuilder dst,
                                         final CharSequence src) {
      return $1(dst, src, true);
    }

    public static final String $1(final CharSequence src) {
      return $1((StringBuilder)null, src).toString();
    }

  |}|})

  f({|escape|})
  f({|quote|})

  popdef({|f|})

  {|
  // clang-format on

  //--------------------------------------------------------------------
  // Smart quoting
  //--------------------------------------------------------------------

  public static final String smartQuote(final CharSequence str) {
    SST_ASSERT(str != null);
    final String x = str.toString();
    if (x.matches("[!#-&(-~]+")) {
      return x;
    }
    return quote(x);
  }

  public static final String smartQuote(final char c) {
    return smartQuote(String.valueOf(c));
  }

  public static final String smartQuoteKey(final CharSequence key) {
    SST_ASSERT(key != null);
    final String x = key.toString();
    if (x.matches("[A-Z_a-z][0-9A-Z_a-z]*")) {
      return x;
    }
    return quote(x);
  }

  //--------------------------------------------------------------------
  // Type checking
  //--------------------------------------------------------------------

  public static boolean isNull(final Object src) {
    return src == null;
  }

  public static boolean isInteger(final Object src) {
    boolean b = false;
    b = b || src instanceof Boolean;
    b = b || src instanceof Byte;
    b = b || src instanceof Short;
    b = b || src instanceof Integer;
    b = b || src instanceof Long;
    b = b || src instanceof BigInteger;
    return b;
  }

  public static boolean isReal(final Object src) {
    boolean b = false;
    b = b || src instanceof Float;
    b = b || src instanceof Double;
    b = b || src instanceof BigDecimal;
    return b;
  }

  public static boolean isNumber(final Object src) {
    boolean b = false;
    b = b || isInteger(src);
    b = b || isReal(src);
    return b;
  }

  public static boolean isString(final Object src) {
    if (src instanceof String) {
      return true;
    }
    return false;
  }

  public static boolean isArray(final Object src) {
    if (src instanceof List<?>) {
      return true;
    }
    return false;
  }

  public static boolean isObject(final Object src) {
    if (src instanceof Map) {
      if (!SST_NDEBUG) {
        for (final Object srcEntryObject : ((Map)src).entrySet()) {
          SST_ASSERT(srcEntryObject instanceof Map.Entry);
          final Map.Entry srcEntry = (Map.Entry)srcEntryObject;
          final Object srcKeyObject = srcEntry.getKey();
          SST_ASSERT(srcKeyObject instanceof String);
          final String srcKey = (String)srcKeyObject;
          final Object srcValue = srcEntry.getValue();
          isArray(srcValue);
        }
      }
      return true;
    }
    return false;
  }

  public static final String castToString(final Object src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(isString(src));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (String)src;
  }

  public static final List<?> castToArray(final Object src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(isArray(src));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (List<?>)src;
  }

  public static final Map<String, ?> castToObject(final Object src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(isObject(src));
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return (Map<String, ?>)src;
  }

  //--------------------------------------------------------------------
  // Copying and merging
  //--------------------------------------------------------------------

  public static final Object copy(final Object src,
                                  final boolean recursive) {
    if (isObject(src)) {
      final Map dst;
      if (recursive) {
        dst = new HashMap();
        for (final Object srcEntryObject : ((Map)src).entrySet()) {
          final Map.Entry srcEntry = (Map.Entry)srcEntryObject;
          final Object srcKeyObject = srcEntry.getKey();
          final String srcKey = (String)srcKeyObject;
          final Object srcValue = srcEntry.getValue();
          dst.put(srcKey, copy(srcValue, recursive));
        }
      } else {
        dst = new HashMap((Map)src);
      }
      return dst;
    }
    if (isArray(src)) {
      final List dst;
      if (recursive) {
        dst = new ArrayList();
        for (final Object srcValue : (List)src) {
          dst.add(copy(srcValue, recursive));
        }
      } else {
        dst = new ArrayList((List)src);
      }
      return dst;
    }
    return src;
  }

  public static final Object copy(final Object src) {
    return copy(src, false);
  }

  public static final Map<String, ?> copy(final Map<String, ?> src,
                                          final boolean recursive) {
    @SuppressWarnings("unchecked")
    final Map<String, ?> x =
        (Map<String, ?>)copy((Object)src, recursive);
    return x;
  }

  public static final Map<String, ?> copy(final Map<String, ?> src) {
    return copy(src, false);
  }

  public static final List copy(final List src,
                                final boolean recursive) {
    return (List)copy((Object)src, recursive);
  }

  public static final List copy(final List src) {
    return copy(src, false);
  }

  public static final Map merge(final Map dst,
                                final Map src,
                                final boolean recursiveMerge,
                                final boolean recursiveCopy) {
    SST_ASSERT(dst != null);
    SST_ASSERT(src != null);
    isObject(dst);
    isObject(src);
    for (final Object srcEntryObject : src.entrySet()) {
      SST_ASSERT(srcEntryObject != null);
      SST_ASSERT(srcEntryObject instanceof Map.Entry);
      final Map.Entry srcEntry = (Map.Entry)srcEntryObject;
      final Object srcKeyObject = srcEntry.getKey();
      SST_ASSERT(srcKeyObject != null);
      SST_ASSERT(srcKeyObject instanceof String);
      final String srcKey = (String)srcKeyObject;
      final Object srcValue = srcEntry.getValue();
      if (srcValue == null) {
        dst.remove(srcKey);
      } else if (recursiveMerge && (srcValue instanceof Map)) {
        final Object dstValue = dst.get(srcKey);
        if (dstValue instanceof Map) {
          merge((Map)dstValue,
                (Map)srcValue,
                recursiveMerge,
                recursiveCopy);
        } else {
          dst.put(srcKey, copy(srcValue, recursiveCopy));
        }
      } else {
        dst.put(srcKey, copy(srcValue, recursiveCopy));
      }
    }
    return dst;
  }

  public static final Map merge(final Map dst,
                                final Map src,
                                final boolean recursiveMerge) {
    return merge(dst, src, recursiveMerge, false);
  }

  public static final Map merge(final Map dst, final Map src) {
    return merge(dst, src, false);
  }

  //--------------------------------------------------------------------
  // Expectation checking
  //--------------------------------------------------------------------

  public static final <T> T expectPresent(final T value) {
    if (value == null) {
      throw new JsonException("Value is missing");
    }
    return value;
  }

  public static final String expectString(final Object value) {
    if (!isString(value)) {
      throw JsonException.expectedString();
    }
    return (String)value;
  }

  public static final List<?> expectArray(final Object value) {
    if (!isArray(value)) {
      throw JsonException.expectedArray();
    }
    @SuppressWarnings("unchecked")
    final List<?> x = (List<?>)value;
    return x;
  }

  public static final Map<String, ?> expectObject(final Object value) {
    if (!isObject(value)) {
      throw JsonException.expectedObject();
    }
    @SuppressWarnings("unchecked")
    final Map<String, ?> x = (Map<String, ?>)value;
    return x;
  }

  public static final void unknownKey(final Object src) {
    for (final String key : expectObject(src).keySet()) {
      throw new JsonException("unknown key: ." + smartQuoteKey(key));
    }
  }

  //--------------------------------------------------------------------
  // Fundamental dump utilities
  //--------------------------------------------------------------------

  public static final class DumpOptions {
    public static final class Builder {
      private int indent_ = -1;
      public final Builder indent(final int x) {
        indent_ = x;
        return this;
      }

      private String indentString_ = " ";
      public final Builder indentString(final CharSequence x) {
        if (!SST_NDEBUG) {
          try {
            SST_ASSERT(x != null);
          } catch (final Throwable e) {
            SST_ASSERT(e);
          }
        }
        indentString_ = x.toString();
        return this;
      }

      public final DumpOptions build() {
        return new DumpOptions(this);
      }
    }

    public static final Builder builder() {
      return new Builder();
    }
    public static final DumpOptions build() {
      return builder().build();
    }

    private final int indent_;
    public final int indent() {
      return indent_;
    }
    public static final Builder indent(final int x) {
      return builder().indent(x);
    }

    private final String indentString_;
    public final String indentString() {
      return indentString_;
    }
    public static final Builder indentString(final CharSequence x) {
      return builder().indentString(x);
    }

    private DumpOptions(final Builder b) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(b != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      indent_ = b.indent_;
      indentString_ = b.indentString_;
    }

    public static final DumpOptions DEFAULT = build();
    public static final DumpOptions INDENT_2 = indent(2).build();
    public static final DumpOptions INDENT_4 = indent(4).build();
  }

  private static void incrementIndentBuffer(
      final DumpOptions options,
      final StringBuilder indentBuffer) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(options != null);
        SST_ASSERT(indentBuffer != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (options.indent() >= 0) {
      if (indentBuffer.length() == 0) {
        indentBuffer.append('\n');
      }
      for (int i = 0; i != options.indent(); ++i) {
        indentBuffer.append(options.indentString());
      }
    }
  }

  private static void decrementIndentBuffer(
      final DumpOptions options,
      final StringBuilder indentBuffer) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(options != null);
        SST_ASSERT(indentBuffer != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (options.indent() >= 0) {
      indentBuffer.setLength(indentBuffer.length()
                             - options.indent()
                                   * options.indentString().length());
    }
  }

  private static Appendable dump(final Appendable dst,
                                 final Object src,
                                 final DumpOptions options,
                                 final StringBuilder indentBuffer)
      throws IOException {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(dst != null);
        SST_ASSERT(options != null);
        SST_ASSERT(indentBuffer != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (src == null) {
      dst.append("null");
    } else if (src instanceof Boolean) {
      dst.append(String.valueOf((Boolean)src));
    } else if (src instanceof Byte) {
      quote(dst, String.valueOf((Byte)src));
    } else if (src instanceof Short) {
      quote(dst, String.valueOf((Short)src));
    } else if (src instanceof Integer) {
      quote(dst, String.valueOf((Integer)src));
    } else if (src instanceof Long) {
      quote(dst, String.valueOf((Long)src));
    } else if (src instanceof BigInteger) {
      quote(dst, ((BigInteger)src).toString());
    } else if (src instanceof Float) {
      quote(dst, ((Float)src).toString());
    } else if (src instanceof Double) {
      quote(dst, ((Double)src).toString());
    } else if (src instanceof BigDecimal) {
      quote(dst, ((BigDecimal)src).toString());
    } else if (src instanceof CharSequence) {
      quote(dst, ((CharSequence)src).toString());
    } else if (src instanceof Iterable<?>) {
      final Iterable<?> xs = (Iterable<?>)src;
      dst.append('[');
      incrementIndentBuffer(options, indentBuffer);
      final Iterator<?> it = xs.iterator();
      boolean first = true;
      while (it.hasNext()) {
        final Object x = it.next();
        if (!first) {
          dst.append(',');
        }
        dst.append(indentBuffer);
        dump(dst, x, options, indentBuffer);
        first = false;
      }
      decrementIndentBuffer(options, indentBuffer);
      dst.append(indentBuffer);
      dst.append(']');
    } else if (isObject(src)) {
      final Set<? extends Map.Entry<String, ?>> xs =
          ((Map<String, ?>)src).entrySet();
      dst.append('{');
      incrementIndentBuffer(options, indentBuffer);
      boolean first = true;
      for (final Map.Entry<String, ?> x : xs) {
        if (!first) {
          dst.append(',');
        }
        dst.append(indentBuffer);
        quote(dst, x.getKey());
        dst.append(':');
        if (options.indent() >= 0) {
          dst.append(' ');
        }
        dump(dst, x.getValue(), options, indentBuffer);
        first = false;
      }
      decrementIndentBuffer(options, indentBuffer);
      dst.append(indentBuffer);
      dst.append('}');
    } else if (!SST_NDEBUG) {
      throw new ImpossibleException("Unknown object type: "
                                    + src.getClass().getCanonicalName()
                                    + ".");
    }
    return dst;
  }

  public final static Appendable dump(final Appendable dst,
                                      final Object src,
                                      final DumpOptions options)
      throws IOException {
    if (!SST_NDEBUG) {
      SST_ASSERT(dst != null);
    }
    return dump(dst,
                src,
                options == null ? DumpOptions.DEFAULT : options,
                new StringBuilder());
  }

  //--------------------------------------------------------------------
  // Convenience dump utilities
  //--------------------------------------------------------------------

  public final static Appendable dump(final Appendable dst,
                                      final Object src)
      throws IOException {
    if (!SST_NDEBUG) {
      SST_ASSERT(dst != null);
    }
    return dump(dst, src, null);
  }

  public final static StringBuilder dump(final StringBuilder dst,
                                         final Object src,
                                         final DumpOptions options) {
    if (!SST_NDEBUG) {
      SST_ASSERT(dst != null);
    }
    try {
      return (StringBuilder)dump((Appendable)dst, src, options);
    } catch (final IOException e) {
      throw new InternalErrorStatus(
          "StringBuilder threw an IOException",
          e);
    }
  }

  public final static StringBuilder dump(final StringBuilder dst,
                                         final Object src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(dst != null);
    }
    return dump(dst, src, null);
  }

  public final static String dump(final Object src,
                                  final DumpOptions options) {
    return dump(new StringBuilder(), src, options).toString();
  }

  public final static String dump(final Object src) {
    return dump(src, null);
  }

  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    public static final $1 getFrom(final $2 src) {
      return $1.valueOf(src);
    }

  |}|})

  f({|Boolean|}, {|boolean|})
  f({|Byte|}, {|byte|})
  f({|Short|}, {|short|})
  f({|Integer|}, {|int|})
  f({|Long|}, {|long|})

  popdef({|f|})

  {|
  // clang-format on

  public static final BigInteger getFrom(final BigInteger src) {
    return src;
  }

  public static final String getFrom(final CharSequence src) {
    if (src == null) {
      return null;
    }
    return src.toString();
  }

  public static final Object getFrom(final ToJson src) {
    if (src == null) {
      return null;
    }
    return src.toJson();
  }

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    public static final <T extends $1> List<$2> getFrom(
        final Iterable<T> src,
        final T srcValueType) {
      if (src == null) {
        return null;
      }
      final List<$2> dst = new ArrayList<$2>();
      final Iterator<T> it = src.iterator();
      while (it.hasNext()) {
        dst.add(getFrom(it.next()));
      }
      return dst;
    }

  |}|})

  f({|Boolean|}, {|Boolean|})
  f({|Byte|}, {|Byte|})
  f({|Short|}, {|Short|})
  f({|Integer|}, {|Integer|})
  f({|Long|}, {|Long|})
  f({|BigInteger|}, {|BigInteger|})
  f({|CharSequence|}, {|String|})
  f({|ToJson|}, {|Object|})

  popdef({|f|})

  {|
  // clang-format on

  public static final <K extends CharSequence, V extends ToJson>
      Map<String, Object> getFrom(final Map<K, V> src,
                                  final K srcKeyType,
                                  final V srcValueType) {
    if (src == null) {
      return null;
    }
    final Map<String, Object> dst = new HashMap<String, Object>();
    for (final Map.Entry<K, V> x : src.entrySet()) {
      // TODO: Reject duplicate keys?
      dst.put(getFrom(x.getKey()), getFrom(x.getValue()));
    }
    return dst;
  }

  //--------------------------------------------------------------------
  // Converting to string types
  //--------------------------------------------------------------------

  public static final String getAs(final Object src,
                                   final String dstType) {
    if (src instanceof CharSequence) {
      return ((CharSequence)src).toString();
    }
    throw JsonException.expectedType(dstType);
  }

  //
  // WARNING: Do not try to add an overload with a defaultValue
  // parameter. This will lead to adding getAs(Object src, String
  // dstType, String defaultValue), which will overlap getAs(Object src,
  // CharSequence key, String dstType) and be very confusing. A caller
  // should simply write src != null ? Json.getAs(src, dstType) :
  // defaultValue.
  //

  //--------------------------------------------------------------------
  // Converting a JSON value to an integer or real type
  //--------------------------------------------------------------------

  |}

  pushdef({|F|}, {|{|

    public static final $2 getAs(final Object src, final $3 dstType) {
      try {
        if (src instanceof Boolean) {
          return Rep.$1((Boolean)src, dstType);
        }
        if (src instanceof Byte) {
          return Rep.$1((Byte)src, dstType);
        }
        if (src instanceof Short) {
          return Rep.$1((Short)src, dstType);
        }
        if (src instanceof Integer) {
          return Rep.$1((Integer)src, dstType);
        }
        if (src instanceof Long) {
          return Rep.$1((Long)src, dstType);
        }
        if (src instanceof BigInteger) {
          return Rep.$1((BigInteger)src, dstType);
        }
        if (src instanceof Float) {
          return Rep.$1((Float)src, dstType);
        }
        if (src instanceof Double) {
          return Rep.$1((Double)src, dstType);
        }
        if (src instanceof BigDecimal) {
          return Rep.$1((BigDecimal)src, dstType);
        }
        if (src instanceof CharSequence) {
          return Rep.$1((CharSequence)src, dstType);
        }
      } catch (final RepException e) {
        throw new JsonException(e);
      }
      throw JsonException.expectedType(dstType);
    }

    //
    // WARNING: Do not try to add an overload with a defaultValue
    // parameter. This will lead to adding getAs(Object src, String
    // dstType, String defaultValue), which will overlap getAs(Object
    // src, CharSequence key, String dstType) and be very confusing. A
    // caller should simply write src != null ? Json.getAs(src, dstType)
    // : defaultValue.
    //

  |}|})

  F({|toInteger|}, {|boolean|}, {|Boolean|})
  F({|toInteger|}, {|byte|}, {|Byte|})
  F({|toInteger|}, {|short|}, {|Short|})
  F({|toInteger|}, {|int|}, {|Integer|})
  F({|toInteger|}, {|long|}, {|Long|})
  F({|toInteger|}, {|BigInteger|}, {|BigInteger|})
  F({|toReal|}, {|float|}, {|Float|})
  F({|toReal|}, {|double|}, {|Double|})
  F({|toReal|}, {|BigDecimal|}, {|BigDecimal|})

  popdef({|F|})

  {|

  //--------------------------------------------------------------------
  // Converting to custom types
  //--------------------------------------------------------------------

  public static final <T extends FromJson<T>> T getTo(final Object src,
                                                      final T dst) {
    SST_ASSERT(dst != null);
    final T r = dst.fromJson(src);
    SST_ASSERT(r == dst);
    return dst;
  }

  public static final <T extends FromJson<T>> T getAs(final Object src,
                                                      final T dstType) {
    SST_ASSERT(dstType != null);
    final T dst;
    try {
      @SuppressWarnings("unchecked")
      final T x =
          (T)dstType.getClass().getDeclaredConstructor().newInstance();
      dst = x;
    } catch (final Exception e) {
      throw new UncheckedException(e);
    }
    return getTo(src, dst);
  }

  public static final <T> T getAs(final Object src,
                                  final CreateFromJson<T> dstFactory) {
    SST_ASSERT(dstFactory != null);
    final T dst = dstFactory.createFromJson(src);
    SST_ASSERT(dst != null);
    return dst;
  }

  //--------------------------------------------------------------------
  // Converting a JSON array to a list or a set with any element type
  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|F2|}, {|{|

    public static final <L extends $1<? super $2>> L
    getTo(final Object src, final L dst, final $2 dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      dst.clear();
      if (src instanceof Iterable) {
        int i = 0;
        try {
          for (final Object srcValue : (Iterable)src) {
            dst.add($3(getAs(srcValue, dstValueType)));
            ++i;
          }
          return dst;
        } catch (final JsonException e) {
          throw e.addIndex(i);
        }
      }
      throw JsonException.expectedType(dst);
    }

    public static final <L extends $1<? super $2>> L
    getAs(final Object src, final L dstType, final $2 dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dstType != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final L dst;
      try {
        @SuppressWarnings("unchecked")
        final L x = (L)dstType.getClass()
                        .getDeclaredConstructor()
                        .newInstance();
        dst = x;
      } catch (final Exception e) {
        throw new UncheckedException(e);
      }
      return getTo(src, dst, dstValueType);
    }

  |}|})

  pushdef({|F1|}, {|{|

    |}
    F2({|$1|}, {|String|}, {||})
    F2({|$1|}, {|Boolean|}, {|Boolean.valueOf|})
    F2({|$1|}, {|Byte|}, {|Byte.valueOf|})
    F2({|$1|}, {|Short|}, {|Short.valueOf|})
    F2({|$1|}, {|Integer|}, {|Integer.valueOf|})
    F2({|$1|}, {|Long|}, {|Long.valueOf|})
    F2({|$1|}, {|BigInteger|}, {||})
    F2({|$1|}, {|Float|}, {|Float.valueOf|})
    F2({|$1|}, {|Double|}, {|Double.valueOf|})
    F2({|$1|}, {|BigDecimal|}, {||})
    {|

    public static final <L extends $1<T>, T extends FromJson<T>> L
    getTo(final Object src, final L dst, final T dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      dst.clear();
      if (src instanceof Iterable) {
        int i = 0;
        try {
          for (final Object srcValue : (Iterable)src) {
            dst.add(getAs(srcValue, dstValueType));
            ++i;
          }
          return dst;
        } catch (final JsonException e) {
          throw e.addIndex(i);
        }
      }
      throw JsonException.expectedType(dst);
    }

    public static final <L extends $1<T>, T extends FromJson<T>> L
    getAs(final Object src, final L dstType, final T dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dstType != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final L dst;
      try {
        @SuppressWarnings("unchecked")
        final L x = (L)dstType.getClass()
                        .getDeclaredConstructor()
                        .newInstance();
        dst = x;
      } catch (final Exception e) {
        throw new UncheckedException(e);
      }
      return getTo(src, dst, dstValueType);
    }

    public static final <L extends $1<T>, T, F
                             extends CreateFromJson<T>> L
    getTo(final Object src, final L dst, final F dstValueFactory) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(dstValueFactory != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      dst.clear();
      if (src instanceof Iterable) {
        int i = 0;
        try {
          for (final Object srcValue : (Iterable)src) {
            dst.add(getAs(srcValue, dstValueFactory));
            ++i;
          }
          return dst;
        } catch (final JsonException e) {
          throw e.addIndex(i);
        }
      }
      throw JsonException.expectedType(dst);
    }

    public static final <L extends $1<T>, T, F
                             extends CreateFromJson<T>> L
    getAs(final Object src, final L dstType, final F dstValueFactory) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dstType != null);
          SST_ASSERT(dstValueFactory != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final L dst;
      try {
        @SuppressWarnings("unchecked")
        final L x = (L)dstType.getClass()
                        .getDeclaredConstructor()
                        .newInstance();
        dst = x;
      } catch (final Exception e) {
        throw new UncheckedException(e);
      }
      return getTo(src, dst, dstValueFactory);
    }

  |}|})

  F1({|List|})
  F1({|Set|})

  popdef({|F1|})
  popdef({|F2|})

  {|
  // clang-format on

  //--------------------------------------------------------------------
  // Converting to simple map types
  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    public static final <T extends Map<String, ? super $1>>
        T getTo(final Object src, final T dst, final $1 dstValueType) {
      SST_ASSERT(dst != null);
      dst.clear();
      if (src instanceof Map) {
        for (final Object srcEntryObj : ((Map)src).entrySet()) {
          final Map.Entry srcEntry = (Map.Entry)srcEntryObj;
          final Object srcKeyObj = srcEntry.getKey();
          if (srcKeyObj instanceof CharSequence) {
            final String srcKey = ((CharSequence)srcKeyObj).toString();
            try {
              final Object srcValue = srcEntry.getValue();
              dst.put(srcKey, getAs(srcValue, dstValueType));
              continue;
            } catch (final JsonException e) {
              throw e.addKey(srcKey);
            }
          }
          throw JsonException.expectedType(dst);
        }
        return dst;
      }
      throw JsonException.expectedType(dst);
    }

    public static final <T extends Map<String, ? super $1>> T
    getAs(final Object src, final T dstType, final $1 dstValueType) {
      SST_ASSERT(dstType != null);
      final T dst;
      try {
        @SuppressWarnings("unchecked")
        final T x = (T)dstType.getClass()
                        .getDeclaredConstructor()
                        .newInstance();
        dst = x;
      } catch (final Exception e) {
        throw new UncheckedException(e);
      }
      return getTo(src, dst, dstValueType);
    }

  |}|})

  f({|String|})
  f({|Boolean|})
  f({|Byte|})
  f({|Short|})
  f({|Integer|})
  f({|Long|})
  f({|BigInteger|})
  f({|Float|})
  f({|Double|})
  f({|BigDecimal|})

  popdef({|f|})

  {|
  // clang-format on

  public static final <M extends Map<String, T>, T extends FromJson<T>>
      M getTo(final Object src, final M dst, final T dstValueType) {
    SST_ASSERT(dst != null);
    if (src instanceof Map) {
      final HashSet<String> keep =
          new HashSet<String>(((Map)src).size());
      for (final Object srcEntryObj : ((Map)src).entrySet()) {
        final Map.Entry srcEntry = (Map.Entry)srcEntryObj;
        final Object srcKeyObj = srcEntry.getKey();
        if (srcKeyObj instanceof CharSequence) {
          final String srcKey = ((CharSequence)srcKeyObj).toString();
          try {
            final Object srcValue = srcEntry.getValue();
            final T dstValue = dst.get(srcKey);
            if (dstValue != null) {
              getTo(srcValue, dstValue);
            } else {
              dst.put(srcKey, getAs(srcValue, dstValueType));
            }
            keep.add(srcKey);
            continue;
          } catch (final JsonException e) {
            throw e.addKey(srcKey);
          }
        }
        throw JsonException.expectedType(dst);
      }
      dst.keySet().retainAll(keep);
      return dst;
    }
    throw JsonException.expectedType(dst);
  }

  public static final <M extends Map<String, T>, T extends FromJson<T>>
      M getAs(final Object src, final M dstType, final T dstValueType) {
    SST_ASSERT(dstType != null);
    final M dst;
    try {
      @SuppressWarnings("unchecked")
      final M x =
          (M)dstType.getClass().getDeclaredConstructor().newInstance();
      dst = x;
    } catch (final Exception e) {
      throw new UncheckedException(e);
    }
    return getTo(src, dst, dstValueType);
  }

  public static final <M extends Map<String, T>, T, F
                           extends CreateFromJson<T>>
      M getTo(final Object src, final M dst, final F dstValueFactory) {
    SST_ASSERT(dst != null);
    SST_ASSERT(dstValueFactory != null);
    dst.clear();
    if (src instanceof Map) {
      for (final Object srcEntryObj : ((Map)src).entrySet()) {
        final Map.Entry srcEntry = (Map.Entry)srcEntryObj;
        final Object srcKeyObj = srcEntry.getKey();
        if (srcKeyObj instanceof CharSequence) {
          final String srcKey = ((CharSequence)srcKeyObj).toString();
          try {
            final Object srcValue = srcEntry.getValue();
            dst.put(srcKey, getAs(srcValue, dstValueFactory));
            continue;
          } catch (final JsonException e) {
            throw e.addKey(srcKey);
          }
        }
        throw JsonException.expectedType(dst);
      }
      return dst;
    }
    throw JsonException.expectedType(dst);
  }

  public static final <M extends Map<String, T>, T, F
                           extends CreateFromJson<T>> M
  getAs(final Object src, final M dstType, final F dstValueFactory) {
    SST_ASSERT(dstType != null);
    SST_ASSERT(dstValueFactory != null);
    final M dst;
    try {
      @SuppressWarnings("unchecked")
      final M x =
          (M)dstType.getClass().getDeclaredConstructor().newInstance();
      dst = x;
    } catch (final Exception e) {
      throw new UncheckedException(e);
    }
    return getTo(src, dst, dstValueFactory);
  }

  //--------------------------------------------------------------------
  // Finding object members
  //--------------------------------------------------------------------

  public static final Object find(final Object src,
                                  final CharSequence key) {
    SST_ASSERT(key != null);
    return expectObject(src).get(key.toString());
  }

  public static final Object remove(final Object src,
                                    final CharSequence key) {
    SST_ASSERT(key != null);
    return expectObject(src).remove(key.toString());
  }

  public static final boolean contains(final Object src,
                                       final CharSequence key) {
    SST_ASSERT(key != null);
    return find(src, key) != null;
  }

  //--------------------------------------------------------------------
  // Converting a JSON object member to any type
  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|F2|}, {|{|

    public static final <L extends $2<? super $1>> L getTo(
        final Object src,
        final CharSequence key,
        final L dst,
        final $1 dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(key != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final Object value = find(src, key);
      try {
        return getTo(expectPresent(value), dst, dstValueType);
      } catch (final JsonException e) {
        throw e.addKey(key);
      }
    }

    public static final <L extends $2<? super $1>> L removeTo(
        final Object src,
        final CharSequence key,
        final L dst,
        final $1 dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(key != null);
          SST_ASSERT(dst != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final L value = getTo(src, key, dst, dstValueType);
      remove(src, key);
      return value;
    }

    public static final <L extends $2<? super $1>> L getAs(
        final Object src,
        final CharSequence key,
        final L dstType,
        final $1 dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(key != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final Object value = find(src, key);
      try {
        return getAs(expectPresent(value), dstType, dstValueType);
      } catch (final JsonException e) {
        throw e.addKey(key);
      }
    }

    public static final <L extends $2<? super $1>> L removeAs(
        final Object src,
        final CharSequence key,
        final L dstType,
        final $1 dstValueType) {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(key != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final L value = getAs(src, key, dstType, dstValueType);
      remove(src, key);
      return value;
    }

  |}|})

  pushdef({|F1|}, {|{|

    public static final $1 getAs(final Object src,
                                 final CharSequence key,
                                 final $1 dstType) {
      SST_ASSERT(key != null);
      final Object value = find(src, key);
      try {
        return getAs(expectPresent(value), dstType);
      } catch (final JsonException e) {
        throw e.addKey(key);
      }
    }

    public static final $1 removeAs(final Object src,
                                    final CharSequence key,
                                    final $1 dstType) {
      SST_ASSERT(key != null);
      final $1 value = getAs(src, key, dstType);
      remove(src, key);
      return value;
    }

    public static final $1 getAs(final Object src,
                                 final CharSequence key,
                                 final $1 dstType,
                                 final $1 defaultValue) {
      SST_ASSERT(key != null);
      final Object value = find(src, key);
      try {
        if (value == null) {
          return defaultValue;
        }
        return getAs(value, dstType);
      } catch (final JsonException e) {
        throw e.addKey(key);
      }
    }

    public static final $1 removeAs(final Object src,
                                    final CharSequence key,
                                    final $1 dstType,
                                    final $1 defaultValue) {
      SST_ASSERT(key != null);
      final $1 value = getAs(src, key, dstType, defaultValue);
      remove(src, key);
      return value;
    }

    |}F2({|$1|}, {|List|}){|
    |}F2({|$1|}, {|Set|}){|

    public static final <M extends Map<String, ? super $1>>
        M getTo(final Object src,
                final CharSequence key,
                final M dst,
                final $1 dstValueType) {
      SST_ASSERT(key != null);
      SST_ASSERT(dst != null);
      final Object value = find(src, key);
      try {
        return getTo(expectPresent(value), dst, dstValueType);
      } catch (final JsonException e) {
        throw e.addKey(key);
      }
    }

    public static final <M extends Map<String, ? super $1>>
        M removeTo(final Object src,
                   final CharSequence key,
                   final M dst,
                   final $1 dstValueType) {
      SST_ASSERT(key != null);
      SST_ASSERT(dst != null);
      final M value = getTo(src, key, dst, dstValueType);
      remove(src, key);
      return value;
    }

    public static final <M extends Map<String, ? super $1>>
        M getAs(final Object src,
                final CharSequence key,
                final M dstType,
                final $1 dstValueType) {
      SST_ASSERT(key != null);
      final Object value = find(src, key);
      try {
        return getAs(expectPresent(value), dstType, dstValueType);
      } catch (final JsonException e) {
        throw e.addKey(key);
      }
    }

    public static final <M extends Map<String, ? super $1>>
        M removeAs(final Object src,
                   final CharSequence key,
                   final M dstType,
                   final $1 dstValueType) {
      SST_ASSERT(key != null);
      final M value = getAs(src, key, dstType, dstValueType);
      remove(src, key);
      return value;
    }

  |}|})

  F1({|String|})
  F1({|Boolean|})
  F1({|Byte|})
  F1({|Short|})
  F1({|Integer|})
  F1({|Long|})
  F1({|BigInteger|})
  F1({|Float|})
  F1({|Double|})
  F1({|BigDecimal|})

  popdef({|F1|})
  popdef({|F2|})

  {|
  // clang-format on

  public static final <T extends FromJson<T>>
      T getTo(final Object src, final CharSequence key, final T dst) {
    SST_ASSERT(key != null);
    SST_ASSERT(dst != null);
    final Object value = find(src, key);
    try {
      return getTo(expectPresent(value), dst);
    } catch (final JsonException e) {
      throw e.addKey(key);
    }
  }

  public static final <T extends FromJson<T>> T
  removeTo(final Object src, final CharSequence key, final T dst) {
    SST_ASSERT(key != null);
    SST_ASSERT(dst != null);
    final T value = getTo(src, key, dst);
    remove(src, key);
    return value;
  }

  public static final <T extends FromJson<T>>
      T getTo(final Object src,
              final CharSequence key,
              final T dst,
              final T defaultValue) {
    SST_ASSERT(key != null);
    SST_ASSERT(dst != null);
    final Object value = find(src, key);
    try {
      if (value == null) {
        return defaultValue;
      }
      return getTo(value, dst);
    } catch (final JsonException e) {
      throw e.addKey(key);
    }
  }

  public static final <T extends FromJson<T>>
      T removeTo(final Object src,
                 final CharSequence key,
                 final T dst,
                 final T defaultValue) {
    SST_ASSERT(key != null);
    SST_ASSERT(dst != null);
    final T value = getTo(src, key, dst, defaultValue);
    remove(src, key);
    return value;
  }

  public static final <T extends FromJson<T>> T
  getAs(final Object src, final CharSequence key, final T dstType) {
    SST_ASSERT(key != null);
    final Object value = find(src, key);
    try {
      return getAs(expectPresent(value), dstType);
    } catch (final JsonException e) {
      throw e.addKey(key);
    }
  }

  public static final <T extends FromJson<T>> T
  removeAs(final Object src, final CharSequence key, final T dstType) {
    SST_ASSERT(key != null);
    final T value = getAs(src, key, dstType);
    remove(src, key);
    return value;
  }

  public static final <T extends FromJson<T>>
      T getAs(final Object src,
              final CharSequence key,
              final T dstType,
              final T defaultValue) {
    SST_ASSERT(key != null);
    final Object value = find(src, key);
    try {
      if (value == null) {
        return defaultValue;
      }
      return getAs(value, dstType);
    } catch (final JsonException e) {
      throw e.addKey(key);
    }
  }

  public static final <T extends FromJson<T>>
      T removeAs(final Object src,
                 final CharSequence key,
                 final T dstType,
                 final T defaultValue) {
    SST_ASSERT(key != null);
    final T value = getAs(src, key, dstType, defaultValue);
    remove(src, key);
    return value;
  }

  public static final <T> T getAs(final Object src,
                                  final CharSequence key,
                                  final CreateFromJson<T> dstFactory) {
    SST_ASSERT(key != null);
    SST_ASSERT(dstFactory != null);
    final Object value = find(src, key);
    try {
      return getAs(value, dstFactory);
    } catch (final JsonException e) {
      throw e.addKey(key);
    }
  }

  public static final <T>
      T removeAs(final Object src,
                 final CharSequence key,
                 final CreateFromJson<T> dstFactory) {
    SST_ASSERT(key != null);
    SST_ASSERT(dstFactory != null);
    final T value = getAs(src, key, dstFactory);
    remove(src, key);
    return value;
  }

  public static final <T> T getAs(final Object src,
                                  final CharSequence key,
                                  final CreateFromJson<T> dstFactory,
                                  final T defaultValue) {
    SST_ASSERT(key != null);
    SST_ASSERT(dstFactory != null);
    final Object value = find(src, key);
    try {
      if (value == null) {
        return defaultValue;
      }
      return getAs(value, dstFactory);
    } catch (final JsonException e) {
      throw e.addKey(key);
    }
  }

  public static final <T> T removeAs(final Object src,
                                     final CharSequence key,
                                     final CreateFromJson<T> dstFactory,
                                     final T defaultValue) {
    SST_ASSERT(key != null);
    SST_ASSERT(dstFactory != null);
    final T value = getAs(src, key, dstFactory, defaultValue);
    remove(src, key);
    return value;
  }

  //--------------------------------------------------------------------
  // Converting to complex list types
  //--------------------------------------------------------------------
  // TODO: Rough ideas below.
  //
  // Object... dstValueTypes should hopefully be able to be placed at
  // the end of every getTo and getAs method, even the object member
  // access methods, without ambiguities. We probably don't need the
  // dstValueTypeHead and dstValueTail thing, just Object...
  // dstValueTypes should be enough.
  //

/*

  private static Class toClass(final Object x) {
    SST_ASSERT(x != null);
    return x instanceof Class ? (Class)x : x.getClass();
  }

  private static boolean isListOrMap(final Class x) {
    SST_ASSERT(x != null);
    return List.class.isAssignableFrom(x) || Map.class.isAssignableFrom(x);
  }

  private static boolean isExactly(final Class x, final Class y) {
    SST_ASSERT(x != null);
    SST_ASSERT(y != null);
    return x.isAssignableFrom(y) && y.isAssignableFrom(x);
  }

  private static boolean isBasic(final Class x) {
    SST_ASSERT(x != null);
    return
isExactly(x, String.class) ||
isExactly(x, Byte.class) ||
isExactly(x, Short.class) ||
isExactly(x, Integer.class) ||
isExactly(x, Long.class) ||
isExactly(x, BigInteger.class);
  }

    public static final <T extends List<?>>
        T getTo(final Object src,
                final T dst,
                final Object dstValueTypeHead,
                final Object... dstValueTail) {
      SST_ASSERT(dst != null);
      SST_ASSERT(dstValueTypeHead != null);
      final Class headClass = toClass(dstValueTypeHead);
      SST_ASSERT(isListOrMap(headClass));
      SST_ASSERT(dstValueTypeTail != null);
      SST_ASSERT(dstValueTypeTail.length > 0);
      for (int i = 0; i < dstValueTypeTail.length; ++i) {
        SST_ASSERT(dstValueTypeTail[i] != null);
        if (i < dstValueTypeTail.length - 1) {
          SST_ASSERT(isListOrMap(toClass(dstValueTypeTail[i])));
        } else {
          SST_ASSERT(isBasic(toClass(dstValueTypeTail[i])));
        }
      }
      dst.clear();
      if (src instanceof Iterable) {
        int i = 0;
        try {
          for (final Object x : (Iterable)src) {
            if (List.class.isAssignableFrom(headClass)) {
              if (dstValueTypeTail.length == 1) {
                dst.add(getAs(x, headClass, toClass(dstValueTypeTail[0]));
              }
              it's a list
            } else if (Map.class.isAssignableFrom(headClass)) {
              it's a map
            } else {
              SST_ASSERT(false);
            }
            dst.add($2(getAs(x, dstValueType)));
            ++i;
          }
          return dst;
        } catch (final JsonException e) {
          throw e.addIndex(i);
        }
      }
      throw new JsonException.expectedType(dst);
    }
*/

  //--------------------------------------------------------------------
  // Converting to complex map types
  //--------------------------------------------------------------------
  // TODO

  //--------------------------------------------------------------------

}

|}|})
