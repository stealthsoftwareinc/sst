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

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Uris</code>
 * Java class.
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import com.stealthsoftwareinc.sst.InternalErrorStatus;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import com.stealthsoftwareinc.sst.MissingCaseStatus;
import com.stealthsoftwareinc.sst.ParseFailureStatus;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CoderResult;
import java.nio.charset.CodingErrorAction;

/* end_imports */

/**
 * Provides various static methods for working with URIs.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Uris
{

/**
 * Prevents objects of this class from being constructed.
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

private Uris(
) {
}

/**
 * Percent-decodes a string.
 *
 * @param src
 * the string to percent-decode.
 * If
 * <code>src</code>
 * is a null reference, then it is implicitly adjusted to an immutable
 * empty string.
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String decode(
  final CharSequence src
) {
  return Uris.decode((StringBuilder)null, src).toString();
}

/**
 *
 * @param dst
 *
 * @param src
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final Appendable decode(
  final Appendable dst,
  final CharSequence src
) throws
  IOException
{
  return
    Uris.decode(
      dst,
      src,
      Uris.defaultDecodeDecoder(),
      null,
      null
    )
  ;
}

/**
 *
 * @param dst
 *
 * @param src
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final Appendable decode(
  final Appendable dst,
  final CharSequence src,
  final CharsetDecoder decoder,
  final ByteBuffer srcBuffer,
  final CharBuffer dstBuffer
) throws
  IOException
{
  if (src == null) {
    return
      Uris.decode(
        dst,
        "",
        decoder,
        srcBuffer,
        dstBuffer
      )
    ;
  }
  if (dst == null) {
    return
      Uris.decode(
        new StringBuilder(),
        src,
        decoder,
        srcBuffer,
        dstBuffer
      )
    ;
  }
  if (decoder == null) {
    int b1 = -1;
    int b2 = -1;
    int i = 0;
    for (;;) {
      if (b2 >= 0) {
        dst.append((char)((b1 << 8) | b2));
        b1 = -1;
        b2 = -1;
      }
      if (
        i < src.length() - 2 &&
        src.charAt(i) == '%' &&
        Uris.isHexDigit(src.charAt(i + 1)) &&
        Uris.isHexDigit(src.charAt(i + 2))
      ) {
        final int d1 = Character.digit(src.charAt(i + 1), 16);
        final int d2 = Character.digit(src.charAt(i + 2), 16);
        if (b1 < 0) {
          b1 = (d1 << 4) | d2;
        } else {
          b2 = (d1 << 4) | d2;
        }
        i += 3;
      } else {
        if (b1 >= 0) {
          throw (ParseFailureStatus)
            new ParseFailureStatus(
              "src contains an invalid sequence of code units"
            ).initCause(null)
          ;
        }
        if (i == src.length()) {
          return dst;
        }
        dst.append(src.charAt(i));
        i += 1;
      }
    }
  }
  if (srcBuffer == null) {
    return
      Uris.decode(
        dst,
        src,
        decoder,
        Uris.defaultDecodeSrcBuffer(),
        dstBuffer
      )
    ;
  }
  if (dstBuffer == null) {
    return
      Uris.decode(
        dst,
        src,
        decoder,
        srcBuffer,
        Uris.defaultDecodeDstBuffer()
      )
    ;
  }
  final int charset;
  final int UTF_16 = 1;
  final int OTHER = 0;
  {
    final String name = decoder.charset().name();
    if (false) {
    } else if (name.equals("UTF-16")) {
      charset = UTF_16;
    } else {
      charset = OTHER;
    }
  }
  decoder.reset();
  srcBuffer.clear();
  switch (charset) {
    case UTF_16: if (true) {
      if (srcBuffer.remaining() < 2) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "srcBuffer is too small"
          ).initCause(null)
        ;
      }
      srcBuffer.put((byte)0xFE);
      srcBuffer.put((byte)0xFF);
    } break;
    case OTHER: if (true) {
    } break;
    default: if (true) {
      throw (MissingCaseStatus)
        new MissingCaseStatus(
          String.valueOf(charset)
        ).initCause(null)
      ;
    } break;
  }
  int i = 0;
  for (;;) {
    if (
      i < src.length() - 2 &&
      src.charAt(i) == '%' &&
      Uris.isHexDigit(src.charAt(i + 1)) &&
      Uris.isHexDigit(src.charAt(i + 2))
    ) {
      if (srcBuffer.remaining() == 0) {
        srcBuffer.flip();
        for (;;) {
          dstBuffer.clear();
          final CoderResult result;
          result = decoder.decode(srcBuffer, dstBuffer, false);
          dstBuffer.flip();
          dst.append(dstBuffer);
          if (result.isUnderflow()) {
            break;
          } else if (result.isOverflow()) {
            if (dstBuffer.limit() == 0) {
              CharacterCodingException cause = null;
              try {
                result.throwException();
              } catch (final CharacterCodingException e) {
                cause = e;
              }
              throw (InvalidArgumentStatus)
                new InvalidArgumentStatus(
                  "dstBuffer is too small"
                ).initCause(cause)
              ;
            }
          } else if (result.isMalformed()) {
            CharacterCodingException cause = null;
            try {
              result.throwException();
            } catch (final CharacterCodingException e) {
              cause = e;
            }
            throw (ParseFailureStatus)
              new ParseFailureStatus(
                "src contains an invalid sequence of code units"
              ).initCause(cause)
            ;
          } else if (result.isUnmappable()) {
            CharacterCodingException cause = null;
            try {
              result.throwException();
            } catch (final CharacterCodingException e) {
              cause = e;
            }
            throw (ParseFailureStatus)
              new ParseFailureStatus(
                "src contains a non-Unicode character"
              ).initCause(cause)
            ;
          } else {
            CharacterCodingException cause = null;
            try {
              result.throwException();
            } catch (final CharacterCodingException e) {
              cause = e;
            }
            throw (InternalErrorStatus)
              new InternalErrorStatus(
                "unknown CoderResult"
              ).initCause(cause)
            ;
          }
        }
        srcBuffer.compact();
        if (srcBuffer.remaining() == 0) {
          throw (InvalidArgumentStatus)
            new InvalidArgumentStatus(
              "srcBuffer is too small"
            ).initCause(null)
          ;
        }
      }
      final int d1 = Character.digit(src.charAt(i + 1), 16);
      final int d2 = Character.digit(src.charAt(i + 2), 16);
      srcBuffer.put((byte)((d1 << 4) | d2));
      i += 3;
    } else {
      if (srcBuffer.position() != 0) {
        srcBuffer.flip();
        boolean flush = false;
        for (;;) {
          dstBuffer.clear();
          final CoderResult result;
          if (flush) {
            result = decoder.flush(dstBuffer);
          } else {
            result = decoder.decode(srcBuffer, dstBuffer, true);
          }
          dstBuffer.flip();
          dst.append(dstBuffer);
          if (result.isUnderflow()) {
            if (flush) {
              break;
            }
            flush = true;
          } else if (result.isOverflow()) {
            if (dstBuffer.limit() == 0) {
              CharacterCodingException cause = null;
              try {
                result.throwException();
              } catch (final CharacterCodingException e) {
                cause = e;
              }
              throw (InvalidArgumentStatus)
                new InvalidArgumentStatus(
                  "dstBuffer is too small"
                ).initCause(cause)
              ;
            }
          } else if (result.isMalformed()) {
            CharacterCodingException cause = null;
            try {
              result.throwException();
            } catch (final CharacterCodingException e) {
              cause = e;
            }
            throw (ParseFailureStatus)
              new ParseFailureStatus(
                "src contains an invalid sequence of code units"
              ).initCause(cause)
            ;
          } else if (result.isUnmappable()) {
            CharacterCodingException cause = null;
            try {
              result.throwException();
            } catch (final CharacterCodingException e) {
              cause = e;
            }
            throw (ParseFailureStatus)
              new ParseFailureStatus(
                "src contains a non-Unicode character"
              ).initCause(cause)
            ;
          } else {
            CharacterCodingException cause = null;
            try {
              result.throwException();
            } catch (final CharacterCodingException e) {
              cause = e;
            }
            throw (InternalErrorStatus)
              new InternalErrorStatus(
                "unknown CoderResult"
              ).initCause(cause)
            ;
          }
        }
        decoder.reset();
        srcBuffer.clear();
        switch (charset) {
          case UTF_16: if (true) {
            srcBuffer.put((byte)0xFE);
            srcBuffer.put((byte)0xFF);
          } break;
          case OTHER: if (true) {
          } break;
          default: if (true) {
            throw (MissingCaseStatus)
              new MissingCaseStatus(
                String.valueOf(charset)
              ).initCause(null)
            ;
          } break;
        }
      }
      if (i == src.length()) {
        return dst;
      }
      dst.append(src.charAt(i));
      i += 1;
    }
  }
}

/**
 * Percent-decodes a string.
 *
 * @param dst
 *
 * @param src
 * the string to percent-decode.
 * If
 * <code>src</code>
 * is a null reference, then it is implicitly adjusted to an immutable
 * empty string.
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @wellbehaved
 * if no other thread accesses
 * <code>dst</code>
 * while this method is being called
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final StringBuilder decode(
  final StringBuilder dst,
  final CharSequence src
) {
  try {
    return
      (StringBuilder)Uris.decode(
        (Appendable)dst,
        src
      )
    ;
  } catch (final IOException e) {
    throw (InternalErrorStatus)
      new InternalErrorStatus(
        "StringBuilder threw an IOException"
      ).initCause(e)
    ;
  }
}

/**
 *
 * @param dst
 *
 * @param src
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final StringBuilder decode(
  final StringBuilder dst,
  final CharSequence src,
  final CharsetDecoder decoder,
  final ByteBuffer srcBuffer,
  final CharBuffer dstBuffer
) {
  try {
    return
      (StringBuilder)Uris.decode(
        (Appendable)dst,
        src,
        decoder,
        srcBuffer,
        dstBuffer
      )
    ;
  } catch (final IOException e) {
    throw (InternalErrorStatus)
      new InternalErrorStatus(
        "StringBuilder threw an IOException"
      ).initCause(e)
    ;
  }
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final CharsetDecoder defaultDecodeDecoder(
) {
  final CharsetDecoder decoder;
  decoder = Charset.forName("UTF-8").newDecoder();
  decoder.onMalformedInput(CodingErrorAction.REPLACE);
  decoder.onUnmappableCharacter(CodingErrorAction.REPORT);
  decoder.replaceWith("\uFFFD");
  return decoder;
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final CharBuffer defaultDecodeDstBuffer(
) {
  return CharBuffer.allocate(1024);
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final ByteBuffer defaultDecodeSrcBuffer(
) {
  return ByteBuffer.allocate(1024);
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final ByteBuffer defaultEncodeDstBuffer(
) {
  return ByteBuffer.allocate(1024);
}

/**
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final CharsetEncoder defaultEncodeEncoder(
) {
  final CharsetEncoder encoder;
  encoder = Charset.forName("UTF-8").newEncoder();
  encoder.onMalformedInput(CodingErrorAction.REPLACE);
  encoder.onUnmappableCharacter(CodingErrorAction.REPORT);
  encoder.replaceWith(new byte[] {(byte)0xEF, (byte)0xBF, (byte)0xBD});
  return encoder;
}

/**
 * Percent-encodes a string.
 *
 * @param src
 * the string to percent-encode.
 * If
 * <code>src</code>
 * is a null reference, then it is implicitly adjusted to an immutable
 * empty string.
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String escape(
  final CharSequence src
) {
  return Uris.escape((StringBuilder)null, src).toString();
}

/**
 *
 * @param dst
 *
 * @param src
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final Appendable escape(
  final Appendable dst,
  final CharSequence src
) throws
  IOException
{
  return
    Uris.escape(
      dst,
      src,
      Uris.defaultEncodeEncoder(),
      null
    )
  ;
}

/**
 *
 * @param dst
 *
 * @param src
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final Appendable escape(
  final Appendable dst,
  final CharSequence src,
  final CharsetEncoder encoder,
  final ByteBuffer dstBuffer
) throws
  IOException
{
  if (src == null) {
    return
      Uris.escape(
        dst,
        "",
        encoder,
        dstBuffer
      )
    ;
  }
  if (dst == null) {
    return
      Uris.escape(
        new StringBuilder(),
        src,
        encoder,
        dstBuffer
      )
    ;
  }
  if (encoder == null) {
    for (int i = 0; i != src.length(); ++i) {
      final char c = src.charAt(i);
      if (Uris.isUnreserved(c)) {
        dst.append(c);
      } else {
        final int d1 = (c >>> 12) & 0xF;
        final int d2 = (c >>>  8) & 0xF;
        final int d3 = (c >>>  4) & 0xF;
        final int d4 = (c >>>  0) & 0xF;
        dst.append("%");
        dst.append("0123456789ABCDEF".charAt(d1));
        dst.append("0123456789ABCDEF".charAt(d2));
        dst.append("%");
        dst.append("0123456789ABCDEF".charAt(d3));
        dst.append("0123456789ABCDEF".charAt(d4));
      }
    }
    return dst;
  }
  if (dstBuffer == null) {
    return
      Uris.escape(
        dst,
        src,
        encoder,
        Uris.defaultEncodeDstBuffer()
      )
    ;
  }
  final int charset;
  final int ISO_8859_1 = 1;
  final int US_ASCII = 2;
  final int UTF_16 = 3;
  final int UTF_16BE = 4;
  final int UTF_16LE = 5;
  final int UTF_8 = 6;
  final int OTHER = 0;
  {
    final String name = encoder.charset().name();
    if (false) {
    } else if (name.equals("ISO-8859-1")) {
      charset = ISO_8859_1;
    } else if (name.equals("US-ASCII")) {
      charset = US_ASCII;
    } else if (name.equals("UTF-16")) {
      charset = UTF_16;
    } else if (name.equals("UTF-16BE")) {
      charset = UTF_16BE;
    } else if (name.equals("UTF-16LE")) {
      charset = UTF_16LE;
    } else if (name.equals("UTF-8")) {
      charset = UTF_8;
    } else {
      charset = OTHER;
    }
  }
  encoder.reset();
  final CharBuffer srcBuffer = CharBuffer.wrap(src);
  dstBuffer.clear();
  boolean byteOrderMark = true;
  boolean flush = false;
  for (;;) {
    final CoderResult result;
    if (flush) {
      result = encoder.flush(dstBuffer);
    } else {
      result = encoder.encode(srcBuffer, dstBuffer, true);
    }
    dstBuffer.flip();
    switch (charset) {
      case ISO_8859_1: if (true) {
        while (dstBuffer.remaining() >= 1) {
          final int b1 = dstBuffer.get() & 0xFF;
          if (Uris.isUnreserved(b1)) {
            dst.append((char)b1);
          } else {
            final int d1 = (b1 >>> 4) & 0xF;
            final int d2 = (b1 >>> 0) & 0xF;
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d1));
            dst.append("0123456789ABCDEF".charAt(d2));
          }
        }
      } break;
      case US_ASCII: if (true) {
        while (dstBuffer.remaining() >= 1) {
          final int b1 = dstBuffer.get() & 0xFF;
          if (Uris.isUnreserved(b1)) {
            dst.append((char)b1);
          } else {
            final int d1 = (b1 >>> 4) & 0xF;
            final int d2 = (b1 >>> 0) & 0xF;
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d1));
            dst.append("0123456789ABCDEF".charAt(d2));
          }
        }
      } break;
      case UTF_16: if (true) {
        while (dstBuffer.remaining() >= 2) {
          final int b1 = dstBuffer.get() & 0xFF;
          final int b2 = dstBuffer.get() & 0xFF;
          if (byteOrderMark) {
            byteOrderMark = false;
            continue;
          }
          if (b1 == 0 && Uris.isUnreserved(b2)) {
            dst.append((char)b2);
          } else {
            final int d1 = (b1 >>> 4) & 0xF;
            final int d2 = (b1 >>> 0) & 0xF;
            final int d3 = (b2 >>> 4) & 0xF;
            final int d4 = (b2 >>> 0) & 0xF;
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d1));
            dst.append("0123456789ABCDEF".charAt(d2));
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d3));
            dst.append("0123456789ABCDEF".charAt(d4));
          }
        }
      } break;
      case UTF_16BE: if (true) {
        while (dstBuffer.remaining() >= 2) {
          final int b1 = dstBuffer.get() & 0xFF;
          final int b2 = dstBuffer.get() & 0xFF;
          if (b1 == 0 && Uris.isUnreserved(b2)) {
            dst.append((char)b2);
          } else {
            final int d1 = (b1 >>> 4) & 0xF;
            final int d2 = (b1 >>> 0) & 0xF;
            final int d3 = (b2 >>> 4) & 0xF;
            final int d4 = (b2 >>> 0) & 0xF;
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d1));
            dst.append("0123456789ABCDEF".charAt(d2));
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d3));
            dst.append("0123456789ABCDEF".charAt(d4));
          }
        }
      } break;
      case UTF_16LE: if (true) {
        while (dstBuffer.remaining() >= 2) {
          final int b1 = dstBuffer.get() & 0xFF;
          final int b2 = dstBuffer.get() & 0xFF;
          if (b2 == 0 && Uris.isUnreserved(b1)) {
            dst.append((char)b1);
          } else {
            final int d1 = (b1 >>> 4) & 0xF;
            final int d2 = (b1 >>> 0) & 0xF;
            final int d3 = (b2 >>> 4) & 0xF;
            final int d4 = (b2 >>> 0) & 0xF;
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d1));
            dst.append("0123456789ABCDEF".charAt(d2));
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d3));
            dst.append("0123456789ABCDEF".charAt(d4));
          }
        }
      } break;
      case UTF_8: if (true) {
        while (dstBuffer.remaining() >= 1) {
          final int b1 = dstBuffer.get() & 0xFF;
          if (Uris.isUnreserved(b1)) {
            dst.append((char)b1);
          } else {
            final int d1 = (b1 >>> 4) & 0xF;
            final int d2 = (b1 >>> 0) & 0xF;
            dst.append("%");
            dst.append("0123456789ABCDEF".charAt(d1));
            dst.append("0123456789ABCDEF".charAt(d2));
          }
        }
      } break;
      case OTHER: if (true) {
        while (dstBuffer.remaining() >= 1) {
          final int b1 = dstBuffer.get() & 0xFF;
          final int d1 = (b1 >>> 4) & 0xF;
          final int d2 = (b1 >>> 0) & 0xF;
          dst.append("%");
          dst.append("0123456789ABCDEF".charAt(d1));
          dst.append("0123456789ABCDEF".charAt(d2));
        }
      } break;
      default: if (true) {
        throw (MissingCaseStatus)
          new MissingCaseStatus(
            String.valueOf(charset)
          ).initCause(null)
        ;
      } break;
    }
    dstBuffer.compact();
    if (result.isUnderflow()) {
      if (flush) {
        if (dstBuffer.position() != 0) {
          throw (InternalErrorStatus)
            new InternalErrorStatus(
              "encoder produced an unexpected number of bytes"
            ).initCause(null)
          ;
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
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "dstBuffer is too small"
        ).initCause(cause)
      ;
    } else if (result.isMalformed()) {
      CharacterCodingException cause = null;
      try {
        result.throwException();
      } catch (final CharacterCodingException e) {
        cause = e;
      }
      throw (ParseFailureStatus)
        new ParseFailureStatus(
          "src contains an invalid sequence of code units"
        ).initCause(cause)
      ;
    } else if (result.isUnmappable()) {
      CharacterCodingException cause = null;
      try {
        result.throwException();
      } catch (final CharacterCodingException e) {
        cause = e;
      }
      switch (charset) {
        case UTF_16: if (true) {
          throw (InternalErrorStatus)
            new InternalErrorStatus(
              "encoder failed with an unmappable-character error"
            ).initCause(cause)
          ;
        } break;
        case UTF_16BE: if (true) {
          throw (InternalErrorStatus)
            new InternalErrorStatus(
              "encoder failed with an unmappable-character error"
            ).initCause(cause)
          ;
        } break;
        case UTF_16LE: if (true) {
          throw (InternalErrorStatus)
            new InternalErrorStatus(
              "encoder failed with an unmappable-character error"
            ).initCause(cause)
          ;
        } break;
        case UTF_8: if (true) {
          throw (InternalErrorStatus)
            new InternalErrorStatus(
              "encoder failed with an unmappable-character error"
            ).initCause(cause)
          ;
        } break;
        case OTHER: if (true) {
          throw (ParseFailureStatus)
            new ParseFailureStatus(
              "encoder failed with an unmappable-character error"
            ).initCause(cause)
          ;
        } break;
        default: if (true) {
          throw (MissingCaseStatus)
            new MissingCaseStatus(
              String.valueOf(charset)
            ).initCause(null)
          ;
        } break;
      }
    } else {
      CharacterCodingException cause = null;
      try {
        result.throwException();
      } catch (final CharacterCodingException e) {
        cause = e;
      }
      throw (InternalErrorStatus)
        new InternalErrorStatus(
          "unknown CoderResult"
        ).initCause(cause)
      ;
    }
  }
}

/**
 * Percent-encodes a string.
 *
 * @param dst
 *
 * @param src
 * the string to percent-encode.
 * If
 * <code>src</code>
 * is a null reference, then it is implicitly adjusted to an immutable
 * empty string.
 *
 * @return
 * <code>dst</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final StringBuilder escape(
  final StringBuilder dst,
  final CharSequence src
) {
  try {
    return
      (StringBuilder)Uris.escape(
        (Appendable)dst,
        src
      )
    ;
  } catch (final IOException e) {
    throw (InternalErrorStatus)
      new InternalErrorStatus(
        "StringBuilder threw an IOException"
      ).initCause(e)
    ;
  }
}

/**
 *
 * @param dst
 *
 * @param src
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final StringBuilder escape(
  final StringBuilder dst,
  final CharSequence src,
  final CharsetEncoder encoder,
  final ByteBuffer dstBuffer
) {
  try {
    return
      (StringBuilder)Uris.escape(
        (Appendable)dst,
        src,
        encoder,
        dstBuffer
      )
    ;
  } catch (final IOException e) {
    throw (InternalErrorStatus)
      new InternalErrorStatus(
        "StringBuilder threw an IOException"
      ).initCause(e)
    ;
  }
}

/**
 * Determines whether an integer value is not the Unicode code point
 * value of a reserved or unreserved URI character.
 * <p>
 * The URI specification
 * (<a href="https://www.ietf.org/rfc/rfc3986.txt">RFC&nbsp;3986</a>)
 * defines the notion of
 * <i>reserved characters</i>,
 * which
 * &ldquo;may
 * (or may not) be defined as
 * delimiters&nbsp;[&hellip;]
 * URIs that differ in the replacement of a reserved character with its
 * corresponding percent-encoded [US-ASCII] octet are not [necessarily]
 * equivalent&rdquo;.
 * The three relevant grammar rules are as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *reserved    = gen-delims / sub-delims
 *gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "&#64;"
 *sub-delims  = "!" / "$" / "&amp;" / "'" / "(" / ")"
 *            / "*" / "+" / "," / ";" / "="
 *</pre></blockquote>
 * <p>
 * The URI specification also defines the notion of
 * <i>unreserved characters</i>,
 * which are
 * &ldquo;allowed
 * in a URI but do not have a reserved
 * purpose&nbsp;[&hellip;]
 * URIs that differ in the replacement of an unreserved character with
 * its corresponding percent-encoded US-ASCII octet are
 * equivalent&rdquo;.
 * The three relevant grammar rules (the latter two of which are
 * inherited from
 * <a href="https://www.ietf.org/rfc/rfc2234.txt">RFC&nbsp;2234</a>)
 * are as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
 *ALPHA       = %x41-5A / %x61-7A ; A-Z / a-z
 *DIGIT       = %x30-39 ; 0-9
 *</pre></blockquote>
 * <p>
 * The union of the reserved and unreserved characters along with the
 * &ldquo;<code>%</code>&rdquo;&nbsp;character,
 * which is a subset of ASCII, is the complete set of characters
 * strictly required to exist by the URI specification.
 * However, additional characters must often be handled in practice,
 * even if only to reject them.
 * These are called
 * <i>extended characters</i>.
 * </p>
 * <p>
 * The set of all integer values is partitioned into three groups by
 * this method, the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isReserved(int)}</code>
 * method, and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isUnreserved(int)}</code>
 * method.
 * In other words, exactly one of these methods returns
 * <code>true</code>
 * for any given integer value.
 * </p>
 * <p>
 * The
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isReserved(int)}</code>
 * and
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isUnreserved(int)}</code>
 * methods are not complementary despite having complementary names.
 * There are indeed no values for which both methods return
 * <code>true</code>,
 * but there are many values for which both methods return
 * <code>false</code>,
 * namely those for which this method returns
 * <code>true</code>.
 * </p>
 * <p>
 * This method is a catch-all in that it returns
 * <code>true</code>
 * for all values for which both the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isReserved(int)}</code>
 * method and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isUnreserved(int)}</code>
 * method return
 * <code>false</code>.
 * In particular, this method does not check
 * whether&nbsp;<code>c</code>
 * is a valid Unicode code point in any sense.
 * </p>
 *
 * @param c
 * the integer value to check
 *
 * @return
 * <code>false</code>
 * if
 * <code>c</code>
 * is the Unicode code point value of a reserved or unreserved URI
 * character, or
 * <code>true</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @see com.stealthsoftwareinc.sst.Uris#isReserved(int)
 * @see com.stealthsoftwareinc.sst.Uris#isUnreserved(int)
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * <ol>
 * <li>
 * The following calls return
 * <code>true</code>:
 *<!--code{.java}--><blockquote><pre>
 *Uris.isExtended('^');
 *Uris.isExtended(-12);
 *</pre></blockquote>
 * </li>
 * <li>
 * The following calls return
 * <code>false</code>:
 *<!--code{.java}--><blockquote><pre>
 *Uris.isExtended('?'); // reserved
 *Uris.isExtended('='); // reserved
 *Uris.isExtended('x'); // unreserved
 *Uris.isExtended('-'); // unreserved
 *</pre></blockquote>
 * </li>
 * </ol>
 *
 * @notablechanges
 * none
 */

public static final boolean isExtended(
  final int c
) {
  return !Uris.isReserved(c) && !Uris.isUnreserved(c);
}

/**
 * Determines whether an integer value is the Unicode code point value
 * of a
 * <code>gen-delims</code>
 * character.
 * <p>
 * The URI specification
 * (<a href="https://www.ietf.org/rfc/rfc3986.txt">RFC&nbsp;3986</a>)
 * defines the set of
 * <code>gen-delims</code>
 * characters as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "&#64;"
 *</pre></blockquote>
 *
 * @param c
 * the integer value to check
 *
 * @return
 * <code>true</code>
 * if
 * <code>c</code>
 * is the Unicode code point value of a
 * <code>gen-delims</code>
 * character, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isGenDelim(
  final int c
) {
  switch (c) {
    case ':': return true;
    case '/': return true;
    case '?': return true;
    case '#': return true;
    case '[': return true;
    case ']': return true;
    case '@': return true;
  }
  return false;
}

/**
 * Determines whether an integer value is the Unicode code point value
 * of an ASCII hexadecimal digit.
 * <p>
 * The
 * &ldquo;0&rdquo;&nbsp;to&nbsp;&ldquo;9&rdquo;&nbsp;characters
 * (U+0030&nbsp;to&nbsp;U+0039),
 * the
 * &ldquo;A&rdquo;&nbsp;to&nbsp;&ldquo;F&rdquo;&nbsp;characters
 * (U+0041&nbsp;to&nbsp;U+0046),
 * and the
 * &ldquo;a&rdquo;&nbsp;to&nbsp;&ldquo;f&rdquo;&nbsp;characters
 * (U+0061&nbsp;to&nbsp;U+0066)
 * are collectively called the
 * <i>ASCII hexadecimal digits</i>.
 * These characters are used by percent-encoded octets to represent the
 * values of the original octets.
 * For example, the ASCII octet of the
 * &ldquo;?&rdquo;&nbsp;character
 * (U+003F) can be percent-encoded as
 * &ldquo;<code>%3F</code>&rdquo;
 * or&nbsp;&ldquo;<code>%3f</code>&rdquo;.
 * </p>
 * <p>
 * After using this method to identify an ASCII hexadecimal digit, you
 * can use the
 * <code>{@link java.lang.Character#digit(char, int)}</code>
 * method or the
 * <code>{@link java.lang.Character#digit(int, int)}</code>
 * method to retrieve the numeric value of the digit.
 * For example,
 * <code>Character.digit('A',&nbsp;16)</code>
 * returns&nbsp;10.
 * However, you should be wary of using these methods to identify
 * digits, as they accept various characters that are not part of ASCII.
 * For example,
 * <code>Character.digit('&#92;uFF17',&nbsp;16)</code>
 * returns&nbsp;7,
 * not&nbsp;&minus;1.
 * </p>
 *
 * @param c
 * the integer value to check
 *
 * @return
 * <code>true</code>
 * if
 * <code>c</code>
 * is the Unicode code point value of an ASCII hexadecimal digit, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @see java.lang.Character#digit(char, int)
 * @see java.lang.Character#digit(int, int)
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isHexDigit(
  final int c
) {
  if (c >= '0' && c <= '9') return true;
  if (c >= 'A' && c <= 'F') return true;
  if (c >= 'a' && c <= 'f') return true;
  return false;
}

/**
 *
 * @param c
 * the integer value to check
 *
 * @param uppercase
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isHexDigit(
  final int c,
  final boolean uppercase
) {
  if (uppercase) {
    if (c >= '0' && c <= '9') return true;
    if (c >= 'A' && c <= 'F') return true;
    return false;
  }
  if (c >= '0' && c <= '9') return true;
  if (c >= 'a' && c <= 'f') return true;
  return false;
}

/**
 * Determines whether an integer value is the Unicode code point value
 * of a reserved URI character.
 * <p>
 * The URI specification
 * (<a href="https://www.ietf.org/rfc/rfc3986.txt">RFC&nbsp;3986</a>)
 * defines the notion of
 * <i>reserved characters</i>,
 * which
 * &ldquo;may
 * (or may not) be defined as
 * delimiters&nbsp;[&hellip;]
 * URIs that differ in the replacement of a reserved character with its
 * corresponding percent-encoded [US-ASCII] octet are not [necessarily]
 * equivalent&rdquo;.
 * The three relevant grammar rules are as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *reserved    = gen-delims / sub-delims
 *gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "&#64;"
 *sub-delims  = "!" / "$" / "&amp;" / "'" / "(" / ")"
 *            / "*" / "+" / "," / ";" / "="
 *</pre></blockquote>
 * <p>
 * The URI specification also defines the notion of
 * <i>unreserved characters</i>,
 * which are
 * &ldquo;allowed
 * in a URI but do not have a reserved
 * purpose&nbsp;[&hellip;]
 * URIs that differ in the replacement of an unreserved character with
 * its corresponding percent-encoded US-ASCII octet are
 * equivalent&rdquo;.
 * The three relevant grammar rules (the latter two of which are
 * inherited from
 * <a href="https://www.ietf.org/rfc/rfc2234.txt">RFC&nbsp;2234</a>)
 * are as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
 *ALPHA       = %x41-5A / %x61-7A ; A-Z / a-z
 *DIGIT       = %x30-39 ; 0-9
 *</pre></blockquote>
 * <p>
 * The union of the reserved and unreserved characters along with the
 * &ldquo;<code>%</code>&rdquo;&nbsp;character,
 * which is a subset of ASCII, is the complete set of characters
 * strictly required to exist by the URI specification.
 * However, additional characters must often be handled in practice,
 * even if only to reject them.
 * These are called
 * <i>extended characters</i>.
 * </p>
 * <p>
 * The set of all integer values is partitioned into three groups by
 * this method, the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isUnreserved(int)}</code>
 * method, and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isExtended(int)}</code>
 * method.
 * In other words, exactly one of these methods returns
 * <code>true</code>
 * for any given integer value.
 * </p>
 * <p>
 * This method and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isUnreserved(int)}</code>
 * method are not complementary despite having complementary names.
 * There are indeed no values for which both methods return
 * <code>true</code>,
 * but there are many values for which both methods return
 * <code>false</code>,
 * namely those for which the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isExtended(int)}</code>
 * method returns
 * <code>true</code>.
 * </p>
 * <p>
 * The
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isExtended(int)}</code>
 * method is a catch-all in that it returns
 * <code>true</code>
 * for all values for which both this method and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isUnreserved(int)}</code>
 * method return
 * <code>false</code>.
 * In particular, it does not check
 * whether&nbsp;<code>c</code>
 * is a valid Unicode code point in any sense.
 * </p>
 *
 * @param c
 * the integer value to check
 *
 * @return
 * <code>true</code>
 * if
 * <code>c</code>
 * is the Unicode code point value of a reserved URI character, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @see com.stealthsoftwareinc.sst.Uris#isExtended(int)
 * @see com.stealthsoftwareinc.sst.Uris#isUnreserved(int)
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * <ol>
 * <li>
 * The following calls return
 * <code>true</code>:
 *<!--code{.java}--><blockquote><pre>
 *Uris.isReserved('?');
 *Uris.isReserved('=');
 *</pre></blockquote>
 * </li>
 * <li>
 * The following calls return
 * <code>false</code>:
 *<!--code{.java}--><blockquote><pre>
 *Uris.isReserved('x'); // unreserved
 *Uris.isReserved('-'); // unreserved
 *Uris.isReserved('^'); // extended
 *Uris.isReserved(-12); // extended
 *</pre></blockquote>
 * </li>
 * </ol>
 *
 * @notablechanges
 * none
 */

public static final boolean isReserved(
  final int c
) {
  return Uris.isGenDelim(c) || Uris.isSubDelim(c);
}

/**
 * Determines whether an integer value is the Unicode code point value
 * of a
 * <code>sub-delims</code>
 * character.
 * <p>
 * The URI specification
 * (<a href="https://www.ietf.org/rfc/rfc3986.txt">RFC&nbsp;3986</a>)
 * defines the set of
 * <code>sub-delims</code>
 * characters as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *sub-delims  = "!" / "$" / "&amp;" / "'" / "(" / ")"
 *            / "*" / "+" / "," / ";" / "="
 *</pre></blockquote>
 *
 * @param c
 * the integer value to check
 *
 * @return
 * <code>true</code>
 * if
 * <code>c</code>
 * is the Unicode code point value of a
 * <code>sub-delims</code>
 * character, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isSubDelim(
  final int c
) {
  switch (c) {
    case '!':  return true;
    case '$':  return true;
    case '&':  return true;
    case '\'': return true;
    case '(':  return true;
    case ')':  return true;
    case '*':  return true;
    case '+':  return true;
    case ',':  return true;
    case ';':  return true;
    case '=':  return true;
  }
  return false;
}

/**
 * Determines whether an integer value is the Unicode code point value
 * of an unreserved URI character.
 * <p>
 * The URI specification
 * (<a href="https://www.ietf.org/rfc/rfc3986.txt">RFC&nbsp;3986</a>)
 * defines the notion of
 * <i>unreserved characters</i>,
 * which are
 * &ldquo;allowed
 * in a URI but do not have a reserved
 * purpose&nbsp;[&hellip;]
 * URIs that differ in the replacement of an unreserved character with
 * its corresponding percent-encoded US-ASCII octet are
 * equivalent&rdquo;.
 * The three relevant grammar rules (the latter two of which are
 * inherited from
 * <a href="https://www.ietf.org/rfc/rfc2234.txt">RFC&nbsp;2234</a>)
 * are as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *unreserved  = ALPHA / DIGIT / "-" / "." / "_" / "~"
 *ALPHA       = %x41-5A / %x61-7A ; A-Z / a-z
 *DIGIT       = %x30-39 ; 0-9
 *</pre></blockquote>
 * <p>
 * The URI specification also defines the notion of
 * <i>reserved characters</i>,
 * which
 * &ldquo;may
 * (or may not) be defined as
 * delimiters&nbsp;[&hellip;]
 * URIs that differ in the replacement of a reserved character with its
 * corresponding percent-encoded [US-ASCII] octet are not [necessarily]
 * equivalent&rdquo;.
 * The three relevant grammar rules are as follows:
 * </p>
 *<!--code{.unparsed}--><blockquote><pre>
 *reserved    = gen-delims / sub-delims
 *gen-delims  = ":" / "/" / "?" / "#" / "[" / "]" / "&#64;"
 *sub-delims  = "!" / "$" / "&amp;" / "'" / "(" / ")"
 *            / "*" / "+" / "," / ";" / "="
 *</pre></blockquote>
 * <p>
 * The union of the reserved and unreserved characters along with the
 * &ldquo;<code>%</code>&rdquo;&nbsp;character,
 * which is a subset of ASCII, is the complete set of characters
 * strictly required to exist by the URI specification.
 * However, additional characters must often be handled in practice,
 * even if only to reject them.
 * These are called
 * <i>extended characters</i>.
 * </p>
 * <p>
 * The set of all integer values is partitioned into three groups by
 * this method, the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isReserved(int)}</code>
 * method, and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isExtended(int)}</code>
 * method.
 * In other words, exactly one of these methods returns
 * <code>true</code>
 * for any given integer value.
 * </p>
 * <p>
 * This method and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isReserved(int)}</code>
 * method are not complementary despite having complementary names.
 * There are indeed no values for which both methods return
 * <code>true</code>,
 * but there are many values for which both methods return
 * <code>false</code>,
 * namely those for which the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isExtended(int)}</code>
 * method returns
 * <code>true</code>.
 * </p>
 * <p>
 * The
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isExtended(int)}</code>
 * method is a catch-all in that it returns
 * <code>true</code>
 * for all values for which both this method and the
 * <code>{@link com.stealthsoftwareinc.sst.Uris#isReserved(int)}</code>
 * method return
 * <code>false</code>.
 * In particular, it does not check
 * whether&nbsp;<code>c</code>
 * is a valid Unicode code point in any sense.
 * </p>
 *
 * @param c
 * the integer value to check
 *
 * @return
 * <code>true</code>
 * if
 * <code>c</code>
 * is the Unicode code point value of an unreserved URI character, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * nothing
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * always
 *
 * @available
 * always
 *
 * @see com.stealthsoftwareinc.sst.Uris#isExtended(int)
 * @see com.stealthsoftwareinc.sst.Uris#isReserved(int)
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * <ol>
 * <li>
 * The following calls return
 * <code>true</code>:
 *<!--code{.java}--><blockquote><pre>
 *Uris.isUnreserved('x');
 *Uris.isUnreserved('-');
 *</pre></blockquote>
 * </li>
 * <li>
 * The following calls return
 * <code>false</code>:
 *<!--code{.java}--><blockquote><pre>
 *Uris.isUnreserved('?'); // reserved
 *Uris.isUnreserved('='); // reserved
 *Uris.isUnreserved('^'); // extended
 *Uris.isUnreserved(-12); // extended
 *</pre></blockquote>
 * </li>
 * </ol>
 *
 * @notablechanges
 * none
 */

public static final boolean isUnreserved(
  final int c
) {
  if (c >= 'A' && c <= 'Z') return true;
  if (c >= 'a' && c <= 'z') return true;
  if (c >= '0' && c <= '9') return true;
  switch (c) {
    case '-': return true;
    case '.': return true;
    case '_': return true;
    case '~': return true;
  }
  return false;
}

}
