/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ConfigPredicate</code>
 * Java interface.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
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
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public interface ConfigPredicate
{

/**
 * Evaluates this predicate on the input argument.
 * <p>
 * There is no convention for what this method should do when it is
 * given a null reference.
 * The main purpose of this interface is to be used by the
 * <code>{@link com.stealthsoftwareinc.sst.ConfigBase}</code>
 * class, which never calls this method with a null reference.
 * </p>
 *
 * @param input
 * the input argument
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

public boolean test(
  final CharSequence input
);

}
