//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ConcurrentLruQueue</code>
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

import com.stealthsoftwareinc.sst.ConcurrentLruQueueEntry;
import java.util.Iterator;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

/* end_imports */

/**
 * A least-recently-in-first-out queue.
 * <p>
 * As a consequence of the technique used for concurrency, certain
 * operations on a
 * <code>{@link com.stealthsoftwareinc.sst.ConcurrentLruQueue}</code>
 * accumulate garbage, which can be purged by occasionally calling the
 * <code>{@link com.stealthsoftwareinc.sst.ConcurrentLruQueue#purge()}</code>
 * method.
 * No other thread must access the queue while it is being purged.
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

public final class ConcurrentLruQueue<E>
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

private ConcurrentHashMap<E, ConcurrentLruQueueEntry<E>> map;

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

private final ConcurrentLinkedQueue<ConcurrentLruQueueEntry<E>> queue;

/**
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

public ConcurrentLruQueue(
) {
  this.map = new ConcurrentHashMap<E, ConcurrentLruQueueEntry<E>>();
  this.queue = new ConcurrentLinkedQueue<ConcurrentLruQueueEntry<E>>();
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
 * if the call to this method does not overlap any call to the
 * <code>{@link com.stealthsoftwareinc.sst.ConcurrentLruQueue#purge()}</code>
 * method
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

public final boolean add(
  final E e
) {
  if (e == null) {
    throw (NullPointerException)
      new NullPointerException(
        "e is a null reference"
      ).initCause(null)
    ;
  }
  final ConcurrentLruQueueEntry<E> entry =
    new ConcurrentLruQueueEntry<E>(e)
  ;
  this.map.put(e, entry);
  this.queue.add(entry);
  return true;
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
 * if the call to this method does not overlap any call to the
 * <code>{@link com.stealthsoftwareinc.sst.ConcurrentLruQueue#purge()}</code>
 * method
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

public final E poll(
) {
  for (;;) {
    final ConcurrentLruQueueEntry<E> entry1 = this.queue.poll();
    if (entry1 == null) {
      return null;
    }
    final ConcurrentLruQueueEntry<E> entry2 = this.map.get(entry1.e);
    if (entry2 == entry1) {
      return entry1.e;
    }
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
 * if the call to this method does not overlap any other call to any
 * method
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

public final long purge(
) {
  final ConcurrentHashMap<E, ConcurrentLruQueueEntry<E>> map;
  map = new ConcurrentHashMap<E, ConcurrentLruQueueEntry<E>>();
  final Iterator<ConcurrentLruQueueEntry<E>> iterator;
  iterator = this.queue.iterator();
  while (iterator.hasNext()) {
    final ConcurrentLruQueueEntry<E> entry = iterator.next();
    if (this.map.get(entry.e) == entry) {
      map.put(entry.e, entry);
    } else {
      iterator.remove();
    }
  }
  this.map = map;
  return 0;
}

}
