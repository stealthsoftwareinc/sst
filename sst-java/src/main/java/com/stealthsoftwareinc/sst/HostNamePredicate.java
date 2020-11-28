/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import java.net.InetSocketAddress;

/* end_imports */

/**
 * Determines whether a string is a host name.
 */

public final class HostNamePredicate
implements
  ConfigPredicate
{

  public HostNamePredicate(
  ) {
  }

  @Override
  public final boolean test(
    final CharSequence t
  ) {
    if (t == null) {
      return false;
    }
    return !new InetSocketAddress(t.toString(), 0).isUnresolved();
  }

}
