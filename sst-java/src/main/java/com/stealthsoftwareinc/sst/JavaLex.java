/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.JavaLex</code>
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
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class JavaLex
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

private JavaLex(
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

public static final StringBuilder encode(
  final CharSequence src
) {
  return JavaLex.encode(src, (StringBuilder)null);
}

/**
 *
 * @param src
 *
 * @param dst
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
  final CharSequence src,
  final Appendable dst
) throws
  IOException
{
  return JavaLex.encode(src, dst, true);
}

/**
 *
 * @param src
 *
 * @param dst
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
  final CharSequence src,
  final Appendable dst,
  final CharsetEncoder encoder,
  final ByteBuffer dstBuffer
) throws
  IOException
{
  if (src == null) {
    return
      JavaLex.encode(
        "",
        dst,
        encoder,
        dstBuffer
      )
    ;
  }
  if (dst == null) {
    return
      JavaLex.encode(
        src,
        new StringBuilder(),
        encoder,
        dstBuffer
      )
    ;
  }
  if (encoder == null) {
    for (int i = 0; i != src.length(); ++i) {
      JavaLex.encode(src.charAt(i), dst);
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
      JavaLex.encode(
        src,
        dst,
        encoder,
        JavaLex.defaultEncodeDstBuffer()
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
      JavaLex.encode((char)c, dst);
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
 * @param src
 *
 * @param dst
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
  final CharSequence src,
  final Appendable dst,
  final boolean recode
) throws
  IOException
{
  return
    JavaLex.encode(
      src,
      dst,
      (recode) ? JavaLex.defaultEncodeEncoder() : null,
      null
    )
  ;
}

/**
 *
 * @param src
 *
 * @param dst
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
  final CharSequence src,
  final StringBuilder dst
) {
  return JavaLex.encode(src, dst, true);
}

/**
 *
 * @param src
 *
 * @param dst
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
  final CharSequence src,
  final StringBuilder dst,
  final CharsetEncoder encoder,
  final ByteBuffer dstBuffer
) {
  try {
    return
      (StringBuilder)JavaLex.encode(
        src,
        (Appendable)dst,
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
 * @param src
 *
 * @param dst
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
  final CharSequence src,
  final StringBuilder dst,
  final boolean recode
) {
  try {
    return
      (StringBuilder)JavaLex.encode(
        src,
        (Appendable)dst,
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

public static final StringBuilder encode(
  final char src
) {
  return JavaLex.encode(src, (StringBuilder)null);
}

/**
 *
 * @param src
 *
 * @param dst
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
  final char src,
  final Appendable dst
) throws
  IOException
{
  if (dst == null) {
    return JavaLex.encode(src, new StringBuilder());
  }
  switch (src) {
    case '\b': return dst.append("\\b");
    case '\t': return dst.append("\\t");
    case '\n': return dst.append("\\n");
    case '\f': return dst.append("\\f");
    case '\r': return dst.append("\\r");
    case '"':  return dst.append("\\\"");
    case '\'': return dst.append("\\'");
    case '\\': return dst.append("\\\\");
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
 * @param src
 *
 * @param dst
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
  final char src,
  final StringBuilder dst
) {
  try {
    return
      (StringBuilder)JavaLex.encode(
        src,
        (Appendable)dst
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
