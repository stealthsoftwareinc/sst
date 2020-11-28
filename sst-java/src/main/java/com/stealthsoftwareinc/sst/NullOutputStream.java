/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.NullOutputStream</code>
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

import java.io.OutputStream;

/* end_imports */

/**
 * An output stream that discards all input.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class NullOutputStream
extends OutputStream
{

/**
 * Constructs a null output stream.
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public NullOutputStream(
) {
  super();
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

@Override
public final void write(
  final byte[] b,
  final int off,
  final int len
) {
  if (b == null) {
    throw (NullPointerException)
      new NullPointerException(
        "b is null"
      ).initCause(null)
    ;
  }
  if (off < 0) {
    throw (IndexOutOfBoundsException)
      new IndexOutOfBoundsException(
        "off is negative"
      ).initCause(null)
    ;
  }
  if (len < 0) {
    throw (IndexOutOfBoundsException)
      new IndexOutOfBoundsException(
        "len is negative"
      ).initCause(null)
    ;
  }
  if (len > b.length - off) {
    throw (IndexOutOfBoundsException)
      new IndexOutOfBoundsException(
        "len is greater than b.length - off"
      ).initCause(null)
    ;
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

@Override
public final void write(
  final int b
) {
}

}
