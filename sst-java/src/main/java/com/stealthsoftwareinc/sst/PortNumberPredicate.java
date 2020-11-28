/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.PortNumberPredicate</code>
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

public final class PortNumberPredicate
implements
  ConfigPredicate
{

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

private final boolean allowZero;

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

public PortNumberPredicate(
) {
  this(false);
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

public PortNumberPredicate(
  final boolean allowZero
) {
  this.allowZero = allowZero;
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
  if (input.length() > 5) {
    return false;
  }
  if (input.length() > 1 && input.charAt(0) == '0') {
    return false;
  }
  int n = 0;
  for (int i = 0; i != input.length(); ++i) {
    if (input.charAt(i) < '0') {
      return false;
    }
    if (input.charAt(i) > '9') {
      return false;
    }
    n = n * 10 + (input.charAt(i) - '0');
  }
  if (n == 0 && !this.allowZero) {
    return false;
  }
  if (n > 65535) {
    return false;
  }
  return true;
}

}
