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

import com.stealthsoftwareinc.sst.InternalErrorStatus;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import com.stealthsoftwareinc.sst.ParseFailureStatus;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CoderResult;
import java.nio.charset.CodingErrorAction;

public final class JavaLex {

  private JavaLex() {
  }

  public static final Appendable escape(final Appendable dst,
                                        final char src)
      throws IOException {
    if (dst == null) {
      return escape(new StringBuilder(), src);
    }
    switch (src) {
      case '\b':
        return dst.append("\\b");
      case '\t':
        return dst.append("\\t");
      case '\n':
        return dst.append("\\n");
      case '\f':
        return dst.append("\\f");
      case '\r':
        return dst.append("\\r");
      case '"':
        return dst.append("\\\"");
      case '\'':
        return dst.append("\\'");
      case '\\':
        return dst.append("\\\\");
    }
    if (src >= ' ' && src <= '~') {
      return dst.append(src);
    }
    dst.append("\\u");
    dst.append("0123456789ABCDEF".charAt((src >>> 12) & 0xF));
    dst.append("0123456789ABCDEF".charAt((src >>> 8) & 0xF));
    dst.append("0123456789ABCDEF".charAt((src >>> 4) & 0xF));
    dst.append("0123456789ABCDEF".charAt((src >>> 0) & 0xF));
    return dst;
  }

  public static final StringBuilder escape(final StringBuilder dst,
                                           final char src) {
    try {
      return (StringBuilder)escape((Appendable)dst, src);
    } catch (final IOException e) {
      throw(InternalErrorStatus) new InternalErrorStatus(
          "StringBuilder threw an IOException")
          .initCause(e);
    }
  }

  public static final StringBuilder escape(final char src) {
    return escape((StringBuilder)null, src);
  }

  public static final CharsetEncoder defaultEncodeEncoder() {
    final CharsetEncoder encoder;
    encoder = Charset.forName("UTF-16BE").newEncoder();
    encoder.onMalformedInput(CodingErrorAction.REPLACE);
    encoder.onUnmappableCharacter(CodingErrorAction.REPORT);
    encoder.replaceWith(new byte[] {(byte)0xFF, (byte)0xFD});
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
      throw(InvalidArgumentStatus) new InvalidArgumentStatus(
          "encoder is not UTF-16BE")
          .initCause(null);
    }
    if (dstBuffer == null) {
      return escape(dst,
                    src,
                    encoder,
                    JavaLex.defaultEncodeDstBuffer());
    }
    encoder.reset();
    final CharBuffer srcBuffer = CharBuffer.wrap(src);
    dstBuffer.clear();
    boolean flush = false;
    for (;;) {
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
            throw(InternalErrorStatus) new InternalErrorStatus(
                "encoder produced an unexpected number of bytes")
                .initCause(null);
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
        throw(InvalidArgumentStatus) new InvalidArgumentStatus(
            "dstBuffer is too small")
            .initCause(cause);
      } else if (result.isMalformed()) {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw(ParseFailureStatus) new ParseFailureStatus(
            "src contains an invalid sequence of code units")
            .initCause(cause);
      } else if (result.isUnmappable()) {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw(InternalErrorStatus) new InternalErrorStatus(
            "encoder failed with an unmappable-character error")
            .initCause(cause);
      } else {
        CharacterCodingException cause = null;
        try {
          result.throwException();
        } catch (final CharacterCodingException e) {
          cause = e;
        }
        throw(InternalErrorStatus) new InternalErrorStatus(
            "unknown CoderResult")
            .initCause(cause);
      }
    }
  }

  public static final StringBuilder escape(final StringBuilder dst,
                                           final CharSequence src,
                                           final CharsetEncoder encoder,
                                           final ByteBuffer dstBuffer) {
    try {
      return (StringBuilder)
          escape((Appendable)dst, src, encoder, dstBuffer);
    } catch (final IOException e) {
      throw(InternalErrorStatus) new InternalErrorStatus(
          "StringBuilder threw an IOException")
          .initCause(e);
    }
  }

  public static final Appendable escape(final Appendable dst,
                                        final CharSequence src,
                                        final boolean recode)
      throws IOException {
    return escape(dst,
                  src,
                  (recode) ? JavaLex.defaultEncodeEncoder() : null,
                  null);
  }

  public static final StringBuilder escape(final StringBuilder dst,
                                           final CharSequence src,
                                           final boolean recode) {
    try {
      return (StringBuilder)escape((Appendable)dst, src, recode);
    } catch (final IOException e) {
      throw(InternalErrorStatus) new InternalErrorStatus(
          "StringBuilder threw an IOException")
          .initCause(e);
    }
  }

  public static final Appendable escape(final Appendable dst,
                                        final CharSequence src)
      throws IOException {
    return escape(dst, src, true);
  }

  public static final StringBuilder escape(final StringBuilder dst,
                                           final CharSequence src) {
    return escape(dst, src, true);
  }

  public static final StringBuilder escape(final CharSequence src) {
    return escape((StringBuilder)null, src);
  }
}
