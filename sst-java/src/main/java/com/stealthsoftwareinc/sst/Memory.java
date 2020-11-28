/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Memory</code>
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

import com.stealthsoftwareinc.sst.AllocationFailedStatus;
import com.stealthsoftwareinc.sst.AllocationImpossibleStatus;
import com.stealthsoftwareinc.sst.InternalErrorStatus;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import java.io.IOException;
import java.lang.Appendable;
import java.lang.ArrayIndexOutOfBoundsException;
import java.lang.Class;
import java.lang.Integer;
import java.lang.OutOfMemoryError;
import java.lang.String;
import java.lang.StringBuilder;
import java.lang.System;
import java.lang.reflect.Array;
import java.util.Arrays;

/* end_imports */

/**
 * Provides various static methods for working with memory.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Memory
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

private Memory(
) {
}

/**
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

/*
 * Although saying <P extends Q, Q> would be natural, we do not do this,
 * as System.arraycopy is not this strict, and we want to be consistent
 * with that. For example, the following calls will succeed:
 *
 *     System.arraycopy(new Object[] {""}, 0, new String[1], 0, 1)
 *     System.arraycopy(new Byte[] {0}, 0, new Long[1], 0, 0)
 */
public static final <P, Q> void copy(
  final P[] p,
  final int i,
  final Q[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   *
   * It is impossible for p and q to not be arrays or null references,
   * as the Java language itself prohibits such arguments from being
   * given to this method, so we don't need to check for those cases.
   *
   * It is impossible for p and q to have primitive component types, as
   * the Java language itself prohibits such arguments from being given
   * to this method, so we don't need to do any checks that are related
   * to those cases.
   *
   * Although copying would be impossible if p and q have unrelated
   * component types, we do not check for this, as System.arraycopy
   * checks for this only as it actually copies each element, and we
   * want to be consistent with that. For example, the following two
   * calls will succeed and fail, respectively:
   *
   *     System.arraycopy(new Byte[] {0}, 0, new Long[1], 0, 0)
   *     System.arraycopy(new Byte[] {0}, 0, new Long[1], 0, 1)
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

public static final void copy(
  final boolean[] p,
  final int i,
  final boolean[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "byte".
 */
public static final void copy(
  final byte[] p,
  final int i,
  final byte[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "char".
 */
public static final void copy(
  final char[] p,
  final int i,
  final char[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "double".
 */
public static final void copy(
  final double[] p,
  final int i,
  final double[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "float".
 */
public static final void copy(
  final float[] p,
  final int i,
  final float[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "int".
 */
public static final void copy(
  final int[] p,
  final int i,
  final int[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "long".
 */
public static final void copy(
  final long[] p,
  final int i,
  final long[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "short".
 */
public static final void copy(
  final short[] p,
  final int i,
  final short[] q,
  final int j,
  final int n
) {
  /*
   * If n != 0, then we'll use System.arraycopy to do all of the work,
   * including checking for invalid arguments and throwing exceptions.
   *
   * However, if n < 0, then we want to complain about that before we
   * might complain about p or q being null references. We don't know
   * the order of exceptions used by System.arraycopy, so we check it
   * ourselves.
   */
  if (n != 0) {
    if (n < 0) {
      throw (ArrayIndexOutOfBoundsException)
        new ArrayIndexOutOfBoundsException(
          "n < 0"
        ).initCause(null)
      ;
    }
    System.arraycopy(p, i, q, j, n);
    return;
  }
  /*
   * Otherwise, n == 0, so we want to take no action, but we still need
   * to check for invalid arguments. We'll mimic System.arraycopy to be
   * consistent.
   */
  if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && i < 0"
      ).initCause(null)
    ;
  }
  if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p == null && i > 0"
      ).initCause(null)
    ;
  }
  if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && p != null && i > p.length"
      ).initCause(null)
    ;
  }
  if (j < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && j < 0"
      ).initCause(null)
    ;
  }
  if (q == null && j > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q == null && j > 0"
      ).initCause(null)
    ;
  }
  if (q != null && j > q.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "n == 0 && q != null && j > q.length"
      ).initCause(null)
    ;
  }
}

/**
 *
 * @param c
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static final <P> P[] ensure(
  final Class<P> c,
  final P[] p,
  final int s
) {
  if (c == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "c is a null reference"
      ).initCause(null)
    ;
  }
  final int n = (p != null) ? p.length : 0;
  int nn = n;
  if (nn >= s) {
    return p;
  }
  do {
    if (nn == 0) {
      nn = 1;
    } else if (nn == 1) {
      nn = 2;
    } else if (nn <= Integer.MAX_VALUE - nn / 2) {
      nn = nn + nn / 2;
    } else {
      nn = Integer.MAX_VALUE;
    }
  } while (nn < s);
  for (;;) {
    final P[] pp;
    try {
      @SuppressWarnings("unchecked")
      final P[] t = (P[])Array.newInstance(c, nn);
      pp = t;
    } catch (final OutOfMemoryError e) {
      if (nn == s) {
        throw (AllocationFailedStatus)
          new AllocationFailedStatus(
          ).initCause(e)
        ;
      }
      nn = s + (nn - s) / 2;
      continue;
    }
    Memory.copy(p, 0, pp, 0, n);
    return pp;
  }
}

/**
 *
 * @param c
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static final <P> P[] ensure(
  final Class<P> c,
  final P[] p,
  final long s
) {
  if (s < 0) {
    return Memory.ensure(c, p, 0);
  }
  if (s > Integer.MAX_VALUE) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(c, p, (int)s);
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static boolean[] ensure(
  final boolean[] p,
  final int s
) {
  final int n = (p != null) ? p.length : 0;
  int nn = n;
  if (nn >= s) {
    return p;
  }
  do {
    if (nn == 0) {
      nn = 1;
    } else if (nn == 1) {
      nn = 2;
    } else if (nn <= Integer.MAX_VALUE - nn / 2) {
      nn = nn + nn / 2;
    } else {
      nn = Integer.MAX_VALUE;
    }
  } while (nn < s);
  for (;;) {
    final boolean[] pp;
    try {
      pp = new boolean[nn];
    } catch (final OutOfMemoryError e) {
      if (nn == s) {
        throw (AllocationFailedStatus)
          new AllocationFailedStatus(
          ).initCause(e)
        ;
      }
      nn = s + (nn - s) / 2;
      continue;
    }
    Memory.copy(p, 0, pp, 0, n);
    return pp;
  }
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static boolean[] ensure(
  final boolean[] p,
  final long s
) {
  if (s < 0) {
    return Memory.ensure(p, 0);
  }
  if (s > Integer.MAX_VALUE) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(p, (int)s);
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "byte".
 */
public static byte[] ensure(
  final byte[] p,
  final int s
) {
  final int n = (p != null) ? p.length : 0;
  int nn = n;
  if (nn >= s) {
    return p;
  }
  do {
    if (nn == 0) {
      nn = 1;
    } else if (nn == 1) {
      nn = 2;
    } else if (nn <= Integer.MAX_VALUE - nn / 2) {
      nn = nn + nn / 2;
    } else {
      nn = Integer.MAX_VALUE;
    }
  } while (nn < s);
  for (;;) {
    final byte[] pp;
    try {
      pp = new byte[nn];
    } catch (final OutOfMemoryError e) {
      if (nn == s) {
        throw (AllocationFailedStatus)
          new AllocationFailedStatus(
          ).initCause(e)
        ;
      }
      nn = s + (nn - s) / 2;
      continue;
    }
    Memory.copy(p, 0, pp, 0, n);
    return pp;
  }
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "byte".
 */
public static byte[] ensure(
  final byte[] p,
  final long s
) {
  if (s < 0) {
    return Memory.ensure(p, 0);
  }
  if (s > Integer.MAX_VALUE) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(p, (int)s);
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static byte[][] ensure(
  final byte[][] p,
  final int s
) {
  return Memory.ensure(byte[].class, p, s);
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static byte[][] ensure(
  final byte[][] p,
  final long s
) {
  return Memory.ensure(byte[].class, p, s);
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static int[] ensure(
  final int[] p,
  final int s
) {
  final int n = (p != null) ? p.length : 0;
  int nn = n;
  if (nn >= s) {
    return p;
  }
  do {
    if (nn == 0) {
      nn = 1;
    } else if (nn == 1) {
      nn = 2;
    } else if (nn <= Integer.MAX_VALUE - nn / 2) {
      nn = nn + nn / 2;
    } else {
      nn = Integer.MAX_VALUE;
    }
  } while (nn < s);
  for (;;) {
    final int[] pp;
    try {
      pp = new int[nn];
    } catch (final OutOfMemoryError e) {
      if (nn == s) {
        throw (AllocationFailedStatus)
          new AllocationFailedStatus(
          ).initCause(e)
        ;
      }
      nn = s + (nn - s) / 2;
      continue;
    }
    Memory.copy(p, 0, pp, 0, n);
    return pp;
  }
}

/**
 *
 * @param p
 *
 * @param s
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
 * nothing
 *
 * @wellbehaved
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

public static int[] ensure(
  final int[] p,
  final long s
) {
  if (s < 0) {
    return Memory.ensure(p, 0);
  }
  if (s > Integer.MAX_VALUE) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(p, (int)s);
}

/**
 *
 * @param c
 *
 * @param p
 *
 * @param s1
 *
 * @param s2
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
 * nothing
 *
 * @wellbehaved
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

public static final <P> P[] ensure_2(
  final Class<P> c,
  final P[] p,
  final int s1,
  final int s2
) {
  if (s2 > 0 && s1 > Integer.MAX_VALUE - s2) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(c, p, s1 + s2);
}

/**
 *
 * @param p
 *
 * @param s1
 *
 * @param s2
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
 * nothing
 *
 * @wellbehaved
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

public static byte[] ensure_2(
  final byte[] p,
  final int s1,
  final int s2
) {
  if (s2 > 0 && s1 > Integer.MAX_VALUE - s2) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(p, s1 + s2);
}

/**
 *
 * @param p
 *
 * @param s1
 *
 * @param s2
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
 * nothing
 *
 * @wellbehaved
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

public static int[] ensure_2(
  final int[] p,
  final int s1,
  final int s2
) {
  if (s2 > 0 && s1 > Integer.MAX_VALUE - s2) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
      ).initCause(null)
    ;
  }
  return Memory.ensure(p, s1 + s2);
}

/**
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

public static final <P> void fill(
  final P[] p,
  final P v
) {
  if (p != null) {
    Memory.fill(p, 0, p.length, v);
  }
}

/**
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

public static final <P> void fill(
  final P[] p,
  final int i,
  final int j,
  final P v
) {
  if (i != j) {
    Arrays.fill(p, i, j, v);
  } else if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && i < 0"
      ).initCause(null)
    ;
  } else if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p == null && i > 0"
      ).initCause(null)
    ;
  } else if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p != null && i > p.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

public static final void fill(
  final boolean[] p,
  final boolean v
) {
  if (p != null) {
    Memory.fill(p, 0, p.length, v);
  }
}

/**
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

public static final void fill(
  final boolean[] p,
  final int i,
  final int j,
  final boolean v
) {
  if (i != j) {
    Arrays.fill(p, i, j, v);
  } else if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && i < 0"
      ).initCause(null)
    ;
  } else if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p == null && i > 0"
      ).initCause(null)
    ;
  } else if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p != null && i > p.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "byte".
 */
public static final void fill(
  final byte[] p,
  final byte v
) {
  if (p != null) {
    Memory.fill(p, 0, p.length, v);
  }
}

/**
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

/*
 * Except for this comment, this method should be identical to the
 * overload for boolean[] with "boolean" replaced with "byte".
 */
public static final void fill(
  final byte[] p,
  final int i,
  final int j,
  final byte v
) {
  if (i != j) {
    Arrays.fill(p, i, j, v);
  } else if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && i < 0"
      ).initCause(null)
    ;
  } else if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p == null && i > 0"
      ).initCause(null)
    ;
  } else if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p != null && i > p.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

public static final void fill(
  final int[] p,
  final int v
) {
  if (p != null) {
    Memory.fill(p, 0, p.length, v);
  }
}

/**
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

public static final void fill(
  final int[] p,
  final int i,
  final int j,
  final int v
) {
  if (i != j) {
    Arrays.fill(p, i, j, v);
  } else if (i < 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && i < 0"
      ).initCause(null)
    ;
  } else if (p == null && i > 0) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p == null && i > 0"
      ).initCause(null)
    ;
  } else if (p != null && i > p.length) {
    throw (ArrayIndexOutOfBoundsException)
      new ArrayIndexOutOfBoundsException(
        "i == j && p != null && i > p.length"
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
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

public static final StringBuilder toHexString(
  final byte[] src
) {
  return Memory.toHexString(src, (StringBuilder)null);
}

/**
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

public static final Appendable toHexString(
  final byte[] src,
  final Appendable dst
) throws
  IOException
{
  return Memory.toHexString(src, dst, true);
}

/**
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

public static final Appendable toHexString(
  final byte[] src,
  final Appendable dst,
  final boolean uppercase
) throws
  IOException
{
  if (src == null) {
    return Memory.toHexString(new byte[0], dst, uppercase);
  }
  if (dst == null) {
    return Memory.toHexString(src, new StringBuilder(), uppercase);
  }
  for (int i = 0; i != src.length; ++i) {
    final int d1 = (src[i] >>> 4) & 0xF;
    final int d2 = (src[i] >>> 0) & 0xF;
    if (uppercase) {
      dst.append("0123456789ABCDEF".charAt(d1));
      dst.append("0123456789ABCDEF".charAt(d2));
    } else {
      dst.append("0123456789abcdef".charAt(d1));
      dst.append("0123456789abcdef".charAt(d2));
    }
  }
  return dst;
}

/**
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

public static final StringBuilder toHexString(
  final byte[] src,
  final StringBuilder dst
) {
  try {
    return
      (StringBuilder)Memory.toHexString(
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

/**
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

public static final StringBuilder toHexString(
  final byte[] src,
  final StringBuilder dst,
  final boolean uppercase
) {
  try {
    return
      (StringBuilder)Memory.toHexString(
        src,
        (Appendable)dst,
        uppercase
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
