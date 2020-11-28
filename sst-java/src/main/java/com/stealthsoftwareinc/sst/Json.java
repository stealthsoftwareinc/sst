/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Json</code>
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
import com.stealthsoftwareinc.sst.ParseFailureStatus;
import java.io.IOException;
import java.lang.Appendable;
import java.lang.CharSequence;
import java.lang.StringBuilder;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CoderResult;
import java.nio.charset.CodingErrorAction;

/* end_imports */

/**
 * Provides various static methods for working with JSON.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Json
{

/**
 * Prevents objects of this class from being constructed.
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

private Json(
) {
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
  encoder = Charset.forName("UTF-16BE").newEncoder();
  encoder.onMalformedInput(CodingErrorAction.REPLACE);
  encoder.onUnmappableCharacter(CodingErrorAction.REPORT);
  encoder.replaceWith(new byte[] {(byte)0xFF, (byte)0xFD});
  return encoder;
}

/**
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
 * all of the following:
 * <ol>
 * <li>
 * The underlying sequence of
 * <code>src</code>.
 * </li>
 * </ol>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if all of the following are true while this method is being called:
 * <ol>
 * <li>
 * The underlying sequence of
 * <code>src</code>
 * is not modified.
 * </li>
 * </ol>
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

public static final String encode(
  final CharSequence src
) {
  return Json.encode((StringBuilder)null, src).toString();
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

public static final Appendable encode(
  final Appendable dst,
  final CharSequence src
) throws
  IOException
{
  return Json.encode(dst, src, true);
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

public static final Appendable encode(
  final Appendable dst,
  final CharSequence src,
  final CharsetEncoder encoder,
  final ByteBuffer dstBuffer
) throws
  IOException
{
  if (src == null) {
    return
      Json.encode(
        dst,
        "",
        encoder,
        dstBuffer
      )
    ;
  }
  if (dst == null) {
    return
      Json.encode(
        new StringBuilder(),
        src,
        encoder,
        dstBuffer
      )
    ;
  }
  if (encoder == null) {
    for (int i = 0; i != src.length(); ++i) {
      Json.encode(dst, src.charAt(i));
    }
    return dst;
  }
  if (!encoder.charset().name().equals("UTF-16BE")) {
    throw (InvalidArgumentStatus)
      new InvalidArgumentStatus(
        "encoder is not UTF-16BE"
      ).initCause(null)
    ;
  }
  if (dstBuffer == null) {
    return
      Json.encode(
        dst,
        src,
        encoder,
        Json.defaultEncodeDstBuffer()
      )
    ;
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
      Json.encode(dst, (char)c);
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
      throw (InternalErrorStatus)
        new InternalErrorStatus(
          "encoder failed with an unmappable-character error"
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

public static final Appendable encode(
  final Appendable dst,
  final CharSequence src,
  final boolean recode
) throws
  IOException
{
  return
    Json.encode(
      dst,
      src,
      (recode) ? Json.defaultEncodeEncoder() : null,
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

public static final StringBuilder encode(
  final StringBuilder dst,
  final CharSequence src
) {
  return Json.encode(dst, src, true);
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

public static final StringBuilder encode(
  final StringBuilder dst,
  final CharSequence src,
  final CharsetEncoder encoder,
  final ByteBuffer dstBuffer
) {
  try {
    return
      (StringBuilder)Json.encode(
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

public static final StringBuilder encode(
  final StringBuilder dst,
  final CharSequence src,
  final boolean recode
) {
  try {
    return
      (StringBuilder)Json.encode(
        (Appendable)dst,
        src,
        recode
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
 * @param src
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

public static final String encode(
  final char src
) {
  return Json.encode((StringBuilder)null, src).toString();
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

public static final Appendable encode(
  final Appendable dst,
  final char src
) throws
  IOException
{
  if (dst == null) {
    return Json.encode(new StringBuilder(), src);
  }
  switch (src) {
    case '"':  return dst.append("\\\"");
    case '\\': return dst.append("\\\\");
    case '/':  return dst.append("\\/");
    case '\b': return dst.append("\\b");
    case '\f': return dst.append("\\f");
    case '\n': return dst.append("\\n");
    case '\r': return dst.append("\\r");
    case '\t': return dst.append("\\t");
  }
  if (src >= ' ' && src <= '~') {
    return dst.append(src);
  }
  dst.append("\\u");
  dst.append("0123456789ABCDEF".charAt((src >>> 12) & 0xF));
  dst.append("0123456789ABCDEF".charAt((src >>>  8) & 0xF));
  dst.append("0123456789ABCDEF".charAt((src >>>  4) & 0xF));
  dst.append("0123456789ABCDEF".charAt((src >>>  0) & 0xF));
  return dst;
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

public static final StringBuilder encode(
  final StringBuilder dst,
  final char src
) {
  try {
    return
      (StringBuilder)Json.encode(
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

}
