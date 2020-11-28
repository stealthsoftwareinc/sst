/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Rand</code>
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

import com.stealthsoftwareinc.sst.BuildConfig;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import com.stealthsoftwareinc.sst.InvalidOperationStatus;
import com.stealthsoftwareinc.sst.NegativeArrayIndexStatus;
import com.stealthsoftwareinc.sst.NegativeArraySizeStatus;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.OversizeArrayIndexStatus;
import java.lang.Integer;
import java.lang.Long;
import java.lang.Math;
import java.lang.System;
import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.security.SecureRandom;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

/* end_imports */

/**
 * Provides various static methods for random number generation.
 *
 * When looking at the code for this class, you may notice that certain
 * temporary arrays seem to be wasteful.
 * This is because Java's
 * <code>{@link java.util.Random}</code>
 * class cannot fill an array slice with random bytes.
 * It can only fill an entire array.
 * This forces us to be wasteful in certain situations where we could
 * otherwise reuse temporaries.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Rand
{

/**
 * Prevents objects of this class from being constructed.
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

private Rand(
) {
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void bytes(
  final Random src,
  final ByteBuffer dst
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
  }
  Rand.bytes(
    src,
    dst,
    dst.remaining()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void bytes(
  final Random src,
  final ByteBuffer dst,
  final int dstLength
) {
  Rand.bytes(
    src,
    dst,
    dstLength,
    Rand.defaultMemoryHint()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void bytes(
  final Random src,
  final ByteBuffer dst,
  final int dstLength,
  final int memoryHint
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
    if (dst.isReadOnly()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "dst.isReadOnly()"
        ).initCause(null)
      ;
    }
    if (dstLength > dst.remaining()) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "dstLength > dst.remaining()"
        ).initCause(null)
      ;
    }
  }
  if (src == null) {
    Rand.bytes(
      Rand.defaultSrc(),
      dst,
      dstLength,
      memoryHint
    );
    return;
  }
  if (memoryHint < 0) {
    Rand.bytes(
      src,
      dst,
      dstLength,
      Rand.defaultMemoryHint()
    );
    return;
  }
  final int nMax = Math.max(memoryHint, 1);
  int i = 0;
  if (dstLength - i >= nMax) {
    final int n = nMax;
    final byte[] xs = new byte[n];
    do {
      src.nextBytes(xs);
      dst.put(xs);
      i += n;
    } while (dstLength - i >= nMax);
  }
  if (dstLength - i != 0) {
    final int n = dstLength - i;
    final byte[] xs = new byte[n];
    src.nextBytes(xs);
    dst.put(xs);
    i += n;
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final Random defaultSrc(
) {
  return new SecureRandom();
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final int defaultMemoryHint(
) {
  return 1 * 1024 * 1024;
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final BigInteger[] dst
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
  }
  Rand.modular(
    src,
    modulus,
    dst,
    0,
    dst.length
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final BigInteger[] dst,
  final int dstOffset,
  final int dstLength
) {
  Rand.modular(
    src,
    modulus,
    dst,
    dstOffset,
    dstLength,
    Rand.defaultMemoryHint()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final BigInteger[] dst,
  final int dstOffset,
  final int dstLength,
  final int memoryHint
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (modulus == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "modulus == null"
        ).initCause(null)
      ;
    }
    if (modulus.signum() < 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus < 0"
        ).initCause(null)
      ;
    }
    if (modulus.signum() == 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus == 0"
        ).initCause(null)
      ;
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
    if (dstOffset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "dstOffset < 0"
        ).initCause(null)
      ;
    }
    if (dstLength < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "dstLength < 0"
        ).initCause(null)
      ;
    }
    if (dstOffset > dst.length - dstLength) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "dstOffset > dst.length - dstLength"
        ).initCause(null)
      ;
    }
  }
  if (src == null) {
    Rand.modular(
      Rand.defaultSrc(),
      modulus,
      dst,
      dstOffset,
      dstLength,
      memoryHint
    );
    return;
  }
  if (memoryHint < 0) {
    Rand.modular(
      src,
      modulus,
      dst,
      dstOffset,
      dstLength,
      Rand.defaultMemoryHint()
    );
    return;
  }
  final byte[] xMax = modulus.subtract(BigInteger.ONE).toByteArray();
  final int xLen;
  if (xMax.length == 1 || xMax[0] != 0) {
    xLen = xMax.length;
  } else {
    xLen = xMax.length - 1;
  }
  final byte[] x = new byte[1 + xLen];
  final int nMax = Math.max(memoryHint / 2 / xLen, 1);
  int i = 0;
  if (dstLength - i >= nMax) {
    final int n = nMax;
    final byte[] xs = new byte[n * xLen];
    do {
      Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
      for (int j = 0; j != n; ++j) {
        System.arraycopy(xs, j * xLen, x, 1, xLen);
        dst[dstOffset + i + j] = new BigInteger(x);
      }
      i += n;
    } while (dstLength - i >= nMax);
  }
  if (dstLength - i != 0) {
    final int n = dstLength - i;
    final byte[] xs = new byte[n * xLen];
    Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
    for (int j = 0; j != n; ++j) {
      System.arraycopy(xs, j * xLen, x, 1, xLen);
      dst[dstOffset + i + j] = new BigInteger(x);
    }
    i += n;
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final ByteBuffer dst
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
  }
  Rand.modular(
    src,
    modulus,
    dst,
    dst.remaining()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final ByteBuffer dst,
  final int dstLength
) {
  Rand.modular(
    src,
    modulus,
    dst,
    dstLength,
    Rand.defaultMemoryHint()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final ByteBuffer dst,
  final int dstLength,
  final int memoryHint
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (modulus == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "modulus == null"
        ).initCause(null)
      ;
    }
    if (modulus.signum() < 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus < 0"
        ).initCause(null)
      ;
    }
    if (modulus.signum() == 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus == 0"
        ).initCause(null)
      ;
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
    if (dst.isReadOnly()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "dst.isReadOnly()"
        ).initCause(null)
      ;
    }
    if (dstLength > dst.remaining()) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "dstLength > dst.remaining()"
        ).initCause(null)
      ;
    }
  }
  final byte[] xMax = modulus.subtract(BigInteger.ONE).toByteArray();
  final int xLen;
  if (xMax.length == 1 || xMax[0] != 0) {
    xLen = xMax.length;
  } else {
    xLen = xMax.length - 1;
  }
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dstLength % xLen != 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "dstLength % xLen != 0"
        ).initCause(null)
      ;
    }
  }
  if (src == null) {
    Rand.modular(
      Rand.defaultSrc(),
      modulus,
      dst,
      dstLength,
      memoryHint
    );
    return;
  }
  if (memoryHint < 0) {
    Rand.modular(
      src,
      modulus,
      dst,
      dstLength,
      Rand.defaultMemoryHint()
    );
    return;
  }
  final int dstOffset = dst.position();
  Rand.bytes(src, dst, dstLength, memoryHint);
  final int chopMask;
  if (xMax[xMax.length - xLen] == 0) {
    chopMask = 0;
  } else {
    final int w = xMax[xMax.length - xLen] & 0xFF;
    int m = 0xFF;
    while ((w & (m >>> 1)) == w) {
      m >>>= 1;
    }
    chopMask = m;
  }
  final byte[] x = new byte[1 + xLen];
  final List<Integer> retries = new LinkedList<Integer>();
  final int nMax = Math.max((int)(memoryHint / (xLen + 20L)), 1);
  int i = dstOffset;
  while (i != dstOffset + dstLength) {
    while (i != dstOffset + dstLength) {
      dst.put(i, (byte)(dst.get(i) & chopMask));
      dst.position(i);
      dst.get(x, 1, xLen);
      if (new BigInteger(x).compareTo(modulus) >= 0) {
        retries.add(i);
        if (retries.size() >= nMax) {
          i += xLen;
          break;
        }
      }
      i += xLen;
    }
    while (!retries.isEmpty()) {
      final byte[] xs = new byte[retries.size() * xLen];
      src.nextBytes(xs);
      final Iterator<Integer> p = retries.iterator();
      int j = 0;
      while (p.hasNext()) {
        final int k = (Integer)p.next();
        xs[j] &= chopMask;
        System.arraycopy(xs, j, x, 1, xLen);
        if (new BigInteger(x).compareTo(modulus) < 0) {
          dst.position(k);
          dst.put(xs, j, xLen);
          p.remove();
        }
        j += xLen;
      }
    }
  }
  dst.position(dstOffset + dstLength);
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final byte[] dst
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
  }
  Rand.modular(
    src,
    modulus,
    dst,
    0,
    dst.length
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final byte[] dst,
  final int dstOffset,
  final int dstLength
) {
  Rand.modular(
    src,
    modulus,
    dst,
    dstOffset,
    dstLength,
    Rand.defaultMemoryHint()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final byte[] dst,
  final int dstOffset,
  final int dstLength,
  final int memoryHint
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (modulus == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "modulus == null"
        ).initCause(null)
      ;
    }
    if (modulus.signum() < 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus < 0"
        ).initCause(null)
      ;
    }
    if (modulus.signum() == 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus == 0"
        ).initCause(null)
      ;
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
    if (dstOffset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "dstOffset < 0"
        ).initCause(null)
      ;
    }
    if (dstLength < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "dstLength < 0"
        ).initCause(null)
      ;
    }
    if (dstOffset > dst.length - dstLength) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "dstOffset > dst.length - dstLength"
        ).initCause(null)
      ;
    }
  }
  final byte[] xMax = modulus.subtract(BigInteger.ONE).toByteArray();
  final int xLen;
  if (xMax.length == 1 || xMax[0] != 0) {
    xLen = xMax.length;
  } else {
    xLen = xMax.length - 1;
  }
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dstLength % xLen != 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "dstLength % xLen != 0"
        ).initCause(null)
      ;
    }
  }
  if (src == null) {
    Rand.modular(
      Rand.defaultSrc(),
      modulus,
      dst,
      dstOffset,
      dstLength,
      memoryHint
    );
    return;
  }
  if (memoryHint < 0) {
    Rand.modular(
      src,
      modulus,
      dst,
      dstOffset,
      dstLength,
      Rand.defaultMemoryHint()
    );
    return;
  }
  if (dstOffset != 0 || dstLength != dst.length) {
    final int nMax = Math.max(memoryHint / 2 / xLen, 1);
    final int dstCount = dstLength / xLen;
    int i = 0;
    if (dstCount - i >= nMax) {
      final int n = nMax;
      final byte[] xs = new byte[n * xLen];
      do {
        Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
        System.arraycopy(xs, 0, dst, dstOffset + i * xLen, xs.length);
        i += n;
      } while (dstCount - i >= nMax);
    }
    if (dstCount - i != 0) {
      final int n = dstCount - i;
      final byte[] xs = new byte[n * xLen];
      Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
      System.arraycopy(xs, 0, dst, dstOffset + i * xLen, xs.length);
      i += n;
    }
    return;
  }
  src.nextBytes(dst);
  final int chopMask;
  if (xMax[xMax.length - xLen] == 0) {
    chopMask = 0;
  } else {
    final int w = xMax[xMax.length - xLen] & 0xFF;
    int m = 0xFF;
    while ((w & (m >>> 1)) == w) {
      m >>>= 1;
    }
    chopMask = m;
  }
  final byte[] x = new byte[1 + xLen];
  final List<Integer> retries = new LinkedList<Integer>();
  final int nMax = Math.max((int)(memoryHint / (xLen + 20L)), 1);
  int i = dstOffset;
  while (i != dstOffset + dstLength) {
    while (i != dstOffset + dstLength) {
      dst[i] &= chopMask;
      System.arraycopy(dst, i, x, 1, xLen);
      if (new BigInteger(x).compareTo(modulus) >= 0) {
        retries.add(i);
        if (retries.size() >= nMax) {
          i += xLen;
          break;
        }
      }
      i += xLen;
    }
    while (!retries.isEmpty()) {
      final byte[] xs = new byte[retries.size() * xLen];
      src.nextBytes(xs);
      final Iterator<Integer> p = retries.iterator();
      int j = 0;
      while (p.hasNext()) {
        final int k = (Integer)p.next();
        xs[j] &= chopMask;
        System.arraycopy(xs, j, x, 1, xLen);
        if (new BigInteger(x).compareTo(modulus) < 0) {
          System.arraycopy(xs, j, dst, k, xLen);
          p.remove();
        }
        j += xLen;
      }
    }
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final int[] dst
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
  }
  Rand.modular(
    src,
    modulus,
    dst,
    0,
    dst.length
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final int[] dst,
  final int dstOffset,
  final int dstLength
) {
  Rand.modular(
    src,
    modulus,
    dst,
    dstOffset,
    dstLength,
    Rand.defaultMemoryHint()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final int[] dst,
  final int dstOffset,
  final int dstLength,
  final int memoryHint
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (modulus == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "modulus == null"
        ).initCause(null)
      ;
    }
    if (modulus.signum() < 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus < 0"
        ).initCause(null)
      ;
    }
    if (modulus.signum() == 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus == 0"
        ).initCause(null)
      ;
    }
    {
      final BigInteger xMax = BigInteger.valueOf(Integer.MAX_VALUE);
      if (modulus.compareTo(xMax.add(BigInteger.ONE)) > 0) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "modulus > Integer.MAX_VALUE + 1"
          ).initCause(null)
        ;
      }
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
    if (dstOffset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "dstOffset < 0"
        ).initCause(null)
      ;
    }
    if (dstLength < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "dstLength < 0"
        ).initCause(null)
      ;
    }
    if (dstOffset > dst.length - dstLength) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "dstOffset > dst.length - dstLength"
        ).initCause(null)
      ;
    }
  }
  if (src == null) {
    Rand.modular(
      Rand.defaultSrc(),
      modulus,
      dst,
      dstOffset,
      dstLength,
      memoryHint
    );
    return;
  }
  if (memoryHint < 0) {
    Rand.modular(
      src,
      modulus,
      dst,
      dstOffset,
      dstLength,
      Rand.defaultMemoryHint()
    );
    return;
  }
  final byte[] xMax = modulus.subtract(BigInteger.ONE).toByteArray();
  final int xLen;
  if (xMax.length == 1 || xMax[0] != 0) {
    xLen = xMax.length;
  } else {
    xLen = xMax.length - 1;
  }
  final byte[] x = new byte[1 + xLen];
  final int nMax = Math.max(memoryHint / 2 / xLen, 1);
  int i = 0;
  if (dstLength - i >= nMax) {
    final int n = nMax;
    final byte[] xs = new byte[n * xLen];
    do {
      Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
      for (int j = 0; j != n; ++j) {
        System.arraycopy(xs, j * xLen, x, 1, xLen);
        dst[dstOffset + i + j] = new BigInteger(x).intValue();
      }
      i += n;
    } while (dstLength - i >= nMax);
  }
  if (dstLength - i != 0) {
    final int n = dstLength - i;
    final byte[] xs = new byte[n * xLen];
    Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
    for (int j = 0; j != n; ++j) {
      System.arraycopy(xs, j * xLen, x, 1, xLen);
      dst[dstOffset + i + j] = new BigInteger(x).intValue();
    }
    i += n;
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final long[] dst
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
  }
  Rand.modular(
    src,
    modulus,
    dst,
    0,
    dst.length
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final long[] dst,
  final int dstOffset,
  final int dstLength
) {
  Rand.modular(
    src,
    modulus,
    dst,
    dstOffset,
    dstLength,
    Rand.defaultMemoryHint()
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void modular(
  final Random src,
  final BigInteger modulus,
  final long[] dst,
  final int dstOffset,
  final int dstLength,
  final int memoryHint
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (modulus == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "modulus == null"
        ).initCause(null)
      ;
    }
    if (modulus.signum() < 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus < 0"
        ).initCause(null)
      ;
    }
    if (modulus.signum() == 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus == 0"
        ).initCause(null)
      ;
    }
    {
      final BigInteger xMax = BigInteger.valueOf(Long.MAX_VALUE);
      if (modulus.compareTo(xMax.add(BigInteger.ONE)) > 0) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "modulus > Long.MAX_VALUE + 1"
          ).initCause(null)
        ;
      }
    }
    if (dst == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "dst == null"
        ).initCause(null)
      ;
    }
    if (dstOffset < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "dstOffset < 0"
        ).initCause(null)
      ;
    }
    if (dstLength < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "dstLength < 0"
        ).initCause(null)
      ;
    }
    if (dstOffset > dst.length - dstLength) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "dstOffset > dst.length - dstLength"
        ).initCause(null)
      ;
    }
  }
  if (src == null) {
    Rand.modular(
      Rand.defaultSrc(),
      modulus,
      dst,
      dstOffset,
      dstLength,
      memoryHint
    );
    return;
  }
  if (memoryHint < 0) {
    Rand.modular(
      src,
      modulus,
      dst,
      dstOffset,
      dstLength,
      Rand.defaultMemoryHint()
    );
    return;
  }
  final byte[] xMax = modulus.subtract(BigInteger.ONE).toByteArray();
  final int xLen;
  if (xMax.length == 1 || xMax[0] != 0) {
    xLen = xMax.length;
  } else {
    xLen = xMax.length - 1;
  }
  final byte[] x = new byte[1 + xLen];
  final int nMax = Math.max(memoryHint / 2 / xLen, 1);
  int i = 0;
  if (dstLength - i >= nMax) {
    final int n = nMax;
    final byte[] xs = new byte[n * xLen];
    do {
      Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
      for (int j = 0; j != n; ++j) {
        System.arraycopy(xs, j * xLen, x, 1, xLen);
        dst[dstOffset + i + j] = new BigInteger(x).longValue();
      }
      i += n;
    } while (dstLength - i >= nMax);
  }
  if (dstLength - i != 0) {
    final int n = dstLength - i;
    final byte[] xs = new byte[n * xLen];
    Rand.modular(src, modulus, xs, 0, xs.length, memoryHint / 2);
    for (int j = 0; j != n; ++j) {
      System.arraycopy(xs, j * xLen, x, 1, xLen);
      dst[dstOffset + i + j] = new BigInteger(x).longValue();
    }
    i += n;
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
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
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final int residueSize(
  final BigInteger modulus
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (modulus == null) {
      throw (NullPointerStatus)
        new NullPointerStatus(
          "modulus == null"
        ).initCause(null)
      ;
    }
    if (modulus.signum() < 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus < 0"
        ).initCause(null)
      ;
    }
    if (modulus.signum() == 0) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "modulus == 0"
        ).initCause(null)
      ;
    }
  }
  final BigInteger xMax = modulus.subtract(BigInteger.ONE);
  if (xMax.signum() == 0) {
    return 1;
  }
  final byte[] xMaxBytes = xMax.toByteArray();
  if (xMaxBytes[0] == 0) {
    return xMaxBytes.length - 1;
  }
  return xMaxBytes.length;
}

}
