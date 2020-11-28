/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.IntegerPredicate</code>
 * Java class.
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

import com.stealthsoftwareinc.sst.ConfigPredicate;
import java.lang.CharSequence;

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

public final class IntegerPredicate
implements
  ConfigPredicate
{

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

public IntegerPredicate(
) {
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
public final boolean test(
  final CharSequence input
) {
  if (input == null) {
    return false;
  }
  if (input.length() == 0) {
    return false;
  }
  int i;
  if (input.charAt(0) == '-') {
    if (input.length() == 1) {
      return false;
    }
    i = 1;
  } else {
    i = 0;
  }
  if (input.length() - i > 1 && input.charAt(i) == '0') {
    return false;
  }
  for (; i != input.length(); ++i) {
    if (input.charAt(i) < '0') {
      return false;
    }
    if (input.charAt(i) > '9') {
      return false;
    }
  }
  return true;
}

}
