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
 * <code>com.stealthsoftwareinc.sst.NetworkMessage</code>
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

import com.stealthsoftwareinc.sst.InvalidOperationStatus;
import java.nio.ByteBuffer;

/* end_imports */

/**
 * Represents a message that can be serialized over a network.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public abstract class NetworkMessage<T extends NetworkMessage<T>>
{

/**
 * Indicates whether this message is mutable.
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

private boolean mutable;

/**
 * The first routing number of this message.
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

protected long route1;

/**
 * The second routing number of this message.
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

protected long route2;

/**
 * The type number of this message.
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

public final int type;

/**
 * Indicates whether this message is an unmodifiable view.
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

protected final T viewee;

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
 * <ol>
 * <li>
 * If you are implementing a network protocol with more than one message
 * type, then you should ignore this constructor.
 * </li>
 * </ol>
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

protected NetworkMessage(
) {
  this(0, null);
}

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
 * <ol>
 * <li>
 * If you are implementing a network protocol with more than one message
 * type, then you should ignore this constructor.
 * </li>
 * </ol>
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

protected NetworkMessage(
  final T viewee
) {
  this(0, viewee);
}

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
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

protected NetworkMessage(
  final int type
) {
  this(type, null);
}

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
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

protected NetworkMessage(
  final int type,
  final T viewee
) {
  this.mutable = (viewee == null);
  this.route1 = 0;
  this.route2 = 0;
  this.type = type;
  this.viewee = viewee;
}

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

public final ByteBuffer getBlob(
) {
  return this.getBlob(null);
}

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

public abstract ByteBuffer getBlob(
  ByteBuffer dst
);

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

public abstract int getBlobSize(
);

/**
 *
 * @return
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
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

protected abstract T getNull(
);

/**
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

public final long getRoute1(
) {
  if (this.isView()) {
    return this.viewee.getRoute1();
  }
  return this.route1;
}

/**
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

public final long getRoute2(
) {
  if (this.isView()) {
    return this.viewee.getRoute2();
  }
  return this.route2;
}

/**
 * Gets this message with the proper type.
 *
 * @return
 * this message with the proper type
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
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

protected abstract T getThis(
);

/**
 * Determines whether this message is immutable.
 *
 * @return
 * <code>true</code>
 * if this message is immutable, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * the mutability state of this message
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if this message is not mutable or its mutability state is not
 * modified while this method is being called
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

public final boolean isImmutable(
) {
  return !this.isMutable() && !this.isView();
}

/**
 * Determines whether this message is mutable.
 *
 * @return
 * <code>true</code>
 * if this message is mutable, or
 * <code>false</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * the mutability state of this message
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if this message is not mutable or its mutability state is not
 * modified while this method is being called
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

public final boolean isMutable(
) {
  return this.mutable;
}

/**
 * Determines whether this message is an unmodifiable view.
 *
 * @return
 * <code>true</code>
 * if this message is an unmodifiable view, or
 * <code>false</code>
 * if not
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

public final boolean isView(
) {
  return this.viewee != null;
}

/**
 * Makes this message immutable.
 *
 * @return
 * this message
 *
 * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
 * if and only if this message is not mutable
 *
 * @throws java.lang.Throwable
 *
 * @accesses
 *
 * @modifies
 * all of the following if this message is mutable:
 * <ol>
 * <li>
 * The mutability state of this message.
 * </li>
 * </ol>
 *
 * @wellbehaved
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

public final T makeImmutable(
) {
  if (!this.isMutable()) {
    throw (InvalidOperationStatus)
      new InvalidOperationStatus(
        "this message is not mutable"
      ).initCause(null)
    ;
  }
  this.mutable = false;
  return this.getThis();
}

/**
 * Sets this message by copying another message.
 *
 * @param src
 *
 * @return
 * this message
 *
 * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
 * (priority&nbsp;1)
 * if and only if this message is not mutable
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed.
 * If this message is mutable, then the modifications to this message
 * may have been interrupted, but this message is still valid.
 * The result is as if this method had succeeded with an unspecified
 * <code>src</code>
 * argument.
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public abstract T set(
  T src
);

/**
 * Sets this message by parsing a sequence of octets.
 *
 * @param src
 *
 * @return
 * this message
 *
 * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
 * (priority&nbsp;1)
 * if and only if this message is not mutable
 *
 * @throws com.stealthsoftwareinc.sst.ParseFailureStatus
 * (or a subclass thereof)
 * (priority&nbsp;2)
 * if and only if the sequence of octets is invalid
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed.
 * If this message is mutable, then the modifications to this message
 * may have been interrupted, but this message is still valid.
 * The result is as if this method had succeeded with an unspecified
 * <code>src</code>
 * argument.
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public abstract T setBlob(
  ByteBuffer src
);

/**
 *
 * @return
 * this message
 *
 * @throws java.lang.Throwable
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

public final T setRoute1(
  final long route1
) {
  if (!this.isMutable()) {
    throw (InvalidOperationStatus)
      new InvalidOperationStatus(
        "this message is not mutable"
      ).initCause(null)
    ;
  }
  this.route1 = route1;
  return this.getThis();
}

/**
 *
 * @return
 * this message
 *
 * @throws java.lang.Throwable
 *
 * @accesses
 *
 * @modifies
 *
 * @wellbehaved
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

public final T setRoute2(
  final long route2
) {
  if (!this.isMutable()) {
    throw (InvalidOperationStatus)
      new InvalidOperationStatus(
        "this message is not mutable"
      ).initCause(null)
    ;
  }
  this.route2 = route2;
  return this.getThis();
}

/**
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
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final T toImmutable(
) {
  if (this.isImmutable()) {
    return this.getThis();
  }
  return this.toImmutableCopy();
}

/**
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
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final T toImmutableCopy(
) {
  return this.toMutable().makeImmutable();
}

/**
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
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @inheritancenotes
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public abstract T toMutable(
);

/**
 * Gets this message if it is an unmodifiable view, or a new
 * unmodifiable view if not.
 *
 * @return
 * this message if it is an unmodifiable view, or a new unmodifiable
 * view if not
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
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public abstract T toView(
);

}
