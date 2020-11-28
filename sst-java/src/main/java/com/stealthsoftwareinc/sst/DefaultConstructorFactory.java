/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.DefaultConstructorFactory</code>
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

import com.stealthsoftwareinc.sst.Factory;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.WrapperException;
import java.lang.Class;
import java.lang.IllegalAccessException;
import java.lang.InstantiationException;
import java.lang.Object;

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

public final class DefaultConstructorFactory<T>
implements
  Factory<T>
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

private final Class<T> clazz;

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

public DefaultConstructorFactory(
  final Class<T> clazz
) {
  if (clazz == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "clazz is a null reference"
      ).initCause(null)
    ;
  }
  this.clazz = clazz;
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
public T get(
) {
  final T object;
  try {
    object = this.clazz.newInstance();
  } catch (final IllegalAccessException e) {
    throw (WrapperException)
      new WrapperException(
      ).initCause(e)
    ;
  } catch (final InstantiationException e) {
    throw (WrapperException)
      new WrapperException(
      ).initCause(e)
    ;
  }
  return object;
}

}
