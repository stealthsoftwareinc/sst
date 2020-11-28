/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.BigResidueArray</code>
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
import com.stealthsoftwareinc.sst.InternalErrorStatus;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import com.stealthsoftwareinc.sst.LimitExceededStatus;
import com.stealthsoftwareinc.sst.NegativeArraySizeStatus;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.Rand;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.lang.Exception;
import java.lang.Math;
import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

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

public final class BigResidueArray
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

private ByteBuffer[] b;

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

private File file;

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

private RandomAccessFile fileStream;

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

private boolean isClosed;

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

private final long length;

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

private final BigInteger modulus;

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

private final int residueSize;

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

public BigResidueArray(
  final long length,
  final BigInteger modulus
) {
  final BigResidueArray that;
  try {
    that =
      new BigResidueArray(
        length,
        modulus,
        false
      )
    ;
  } catch (final IOException e) {
    throw (InternalErrorStatus)
      new InternalErrorStatus(
      ).initCause(e)
    ;
  }
  this.b = that.b;
  this.file = that.file;
  this.fileStream = that.fileStream;
  this.isClosed = that.isClosed;
  this.length = that.length;
  this.modulus = that.modulus;
  this.residueSize = that.residueSize;
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

public BigResidueArray(
  final long length,
  final BigInteger modulus,
  final boolean useFiles
) throws
  IOException
{
  this(
    length,
    modulus,
    useFiles,
    null
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

public BigResidueArray(
  final long length,
  final BigInteger modulus,
  final boolean useFiles,
  final File filesDirectory
) throws
  IOException
{
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (length < 0) {
      throw (NegativeArraySizeStatus)
        new NegativeArraySizeStatus(
          "length < 0"
        ).initCause(null)
      ;
    }
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
  final BigInteger intMax = BigInteger.valueOf(Integer.MAX_VALUE);
  final BigInteger residueSize =
    BigInteger.valueOf(Rand.residueSize(modulus))
  ;
  {
    final BigInteger nBytes =
      BigInteger.valueOf(length).multiply(residueSize)
    ;
    final BigInteger nResiduesPerBuffer =
      intMax.divide(residueSize)
    ;
    final BigInteger nBytesPerBuffer =
      nResiduesPerBuffer.multiply(residueSize)
    ;
    final BigInteger[] nBuffersQr =
      nBytes.divideAndRemainder(nBytesPerBuffer)
    ;
    final BigInteger nBuffers =
      nBuffersQr[0].add(BigInteger.valueOf(nBuffersQr[1].signum()))
    ;
    if (nBuffers.compareTo(intMax) > 0) {
      throw (LimitExceededStatus)
        new LimitExceededStatus(
        ).initCause(null)
      ;
    }
    final int nBuffersInt = nBuffers.intValue();
    final int nBytesPerBufferInt = nBytesPerBuffer.intValue();
    this.b = new ByteBuffer[nBuffersInt];
    if (useFiles) {
      this.file = File.createTempFile("tmp", null, filesDirectory);
      this.file.deleteOnExit();
      this.fileStream = new RandomAccessFile(this.file, "rw");
      try {
        this.fileStream.setLength(nBytes.longValue());
        final FileChannel c = this.fileStream.getChannel();
        try {
          for (int i = 0; i != nBuffersInt - 1; ++i) {
            this.b[i] =
              c.map(
                FileChannel.MapMode.READ_WRITE,
                (long)i * nBytesPerBufferInt,
                nBytesPerBufferInt
              )
            ;
          }
          this.b[nBuffersInt - 1] =
            c.map(
              FileChannel.MapMode.READ_WRITE,
              (long)(nBuffersInt - 1) * nBytesPerBufferInt,
              nBuffersQr[1].intValue()
            )
          ;
        } finally {
          try {
            c.close();
          } catch (final Exception e) {
          }
        }
      } catch (final Exception e1) {
        try {
          this.fileStream.close();
        } catch (final Exception e2) {
        }
        try {
          this.file.delete();
        } catch (final Exception e2) {
        }
        throw e1;
      }
    } else {
      this.file = null;
      this.fileStream = null;
      for (int i = 0; i != nBuffersInt - 1; ++i) {
        this.b[i] =
          ByteBuffer.allocate(nBytesPerBufferInt)
        ;
      }
      this.b[nBuffersInt - 1] =
        ByteBuffer.allocate(nBuffersQr[1].intValue())
      ;
    }
  }
  this.isClosed = false;
  this.length = length;
  this.modulus = modulus;
  this.residueSize = residueSize.intValue();
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

public final void close(
) {
  if (!this.isClosed) {
    if (this.fileStream != null) {
      try {
        this.fileStream.close();
      } catch (final Exception e) {
      }
    }
    if (this.file != null) {
      try {
        this.file.delete();
      } catch (final Exception e) {
      }
    }
    this.b = null;
    this.file = null;
    this.fileStream = null;
    this.isClosed = true;
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

public final ByteBuffer getBuffer(
  final int bufferIndex
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (this.isClosed) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this.isClosed"
        ).initCause(null)
      ;
    }
    if (bufferIndex < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "bufferIndex < 0"
        ).initCause(null)
      ;
    }
    if (bufferIndex >= this.b.length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "bufferIndex >= this.b.length"
        ).initCause(null)
      ;
    }
  }
  this.b[bufferIndex].position(0);
  return this.b[bufferIndex].duplicate();
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

public final int getBufferCount(
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (this.isClosed) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this.isClosed"
        ).initCause(null)
      ;
    }
  }
  return this.b.length;
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

public final long getLength(
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (this.isClosed) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this.isClosed"
        ).initCause(null)
      ;
    }
  }
  return this.length;
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

public final BigInteger getValue(
  final long index
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (this.isClosed) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this.isClosed"
        ).initCause(null)
      ;
    }
    if (index < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "index < 0"
        ).initCause(null)
      ;
    }
    if (index >= this.length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "index >= this.length"
        ).initCause(null)
      ;
    }
  }
  final int n = this.b[0].capacity() / this.residueSize;
  final int i = (int)(index / n);
  final int j = (int)(index % n);
  final byte[] x = new byte[1 + this.residueSize];
  this.b[i].position(j * this.residueSize);
  this.b[i].get(x, 1, this.residueSize);
  return new BigInteger(x);
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

public final void setValue(
  final long index,
  final BigInteger value
) {
  if (BuildConfig.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (this.isClosed) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this.isClosed"
        ).initCause(null)
      ;
    }
    if (index < 0) {
      throw (NegativeArrayIndexStatus)
        new NegativeArrayIndexStatus(
          "index < 0"
        ).initCause(null)
      ;
    }
    if (index >= this.length) {
      throw (OversizeArrayIndexStatus)
        new OversizeArrayIndexStatus(
          "index >= this.length"
        ).initCause(null)
      ;
    }
    if (value != null) {
      if (value.signum() < 0) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "value < 0"
          ).initCause(null)
        ;
      }
      if (value.compareTo(this.modulus) >= 0) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "value >= this.modulus"
          ).initCause(null)
        ;
      }
    }
  }
  if (value == null) {
    this.setValue(
      index,
      BigInteger.ZERO
    );
    return;
  }
  final int n = this.b[0].capacity() / this.residueSize;
  final int i = (int)(index / n);
  final int j = (int)(index % n);
  final byte[] x = value.toByteArray();
  final int xOffset;
  if (x.length == 1 || x[0] != 0) {
    xOffset = 0;
  } else {
    xOffset = 1;
  }
  this.b[i].position(j * this.residueSize);
  for (int k = 0; k != this.residueSize - (x.length - xOffset); ++k) {
    this.b[i].put((byte)0);
  }
  this.b[i].put(x, xOffset, x.length - xOffset);
}

}
