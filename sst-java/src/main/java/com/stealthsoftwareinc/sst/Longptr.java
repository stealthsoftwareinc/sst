/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Longptr</code>
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

/* end_imports */

/**
 * Provides information about using the
 * <code>long</code>
 * type to represent native pointers.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Longptr
{

/**
 * Indicates whether native pointers can be represented by the
 * <code>long</code>
 * type.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean IS_SUPPORTED = getIsSupported();

/**
 * The null pointer value if native pointers can be represented by the
 * <code>long</code>
 * type, or zero if not.
 * <p>
 * You should not normally use this variable to determine whether native
 * pointers can be represented by the
 * <code>long</code>
 * type, as either case is possible when this variable is zero.
 * Use the
 * <code>{@link com.stealthsoftwareinc.sst.Longptr#IS_SUPPORTED}</code>
 * variable instead.
 * </p>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final long/*ptr*/ NULL = getNull();

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

private Longptr(
) {
}

/**
 * TODO: Change this into a native method that does the right thing.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

private static final boolean getIsSupported(
) {
  return true;
}

/**
 * TODO: Change this into a native method that does the right thing.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

private static final long/*ptr*/ getNull(
) {
  return 0;
}

}
