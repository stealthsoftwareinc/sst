/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ConcurrentPool</code>
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

import com.stealthsoftwareinc.sst.DefaultConstructorFactory;
import com.stealthsoftwareinc.sst.Factory;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.Pool;
import com.stealthsoftwareinc.sst.PoolEntry;
import com.stealthsoftwareinc.sst.WrapperException;
import java.lang.Class;
import java.lang.IllegalAccessException;
import java.lang.InstantiationException;
import java.util.concurrent.ConcurrentLinkedQueue;

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

public final class ConcurrentPool<T>
implements
  Pool<T>
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

private final Factory<T> factory;

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

private final ConcurrentLinkedQueue<PoolEntry<T>> queue;

/**
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * if and only if
 * <code>clazz</code>
 * is a null reference
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

public ConcurrentPool(
  final Class<T> clazz
) {
  if (clazz == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "clazz is a null reference"
      ).initCause(null)
    ;
  }
  this.factory = new DefaultConstructorFactory<T>(clazz);
  this.queue = new ConcurrentLinkedQueue<PoolEntry<T>>();
}

/**
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * if and only if
 * <code>factory</code>
 * is a null reference
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

public ConcurrentPool(
  final Factory<T> factory
) {
  if (factory == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "factory is a null reference"
      ).initCause(null)
    ;
  }
  this.factory = factory;
  this.queue = new ConcurrentLinkedQueue<PoolEntry<T>>();
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
public PoolEntry<T> acquire(
) {
  {
    final PoolEntry<T> entry = this.queue.poll();
    if (entry != null) {
      return entry;
    }
  }
  return new PoolEntry<T>(this.factory.get(), this);
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
public void release(
  final PoolEntry<T> entry
) {
  this.queue.add(entry);
}

}
