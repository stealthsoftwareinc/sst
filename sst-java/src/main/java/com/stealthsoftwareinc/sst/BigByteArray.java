/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.BigByteArray</code>
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
import com.stealthsoftwareinc.sst.LimitExceededStatus;
import com.stealthsoftwareinc.sst.NegativeArraySizeStatus;
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

public final class BigByteArray
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

public BigByteArray(
  final long length
) {
  final BigByteArray that;
  try {
    that =
      new BigByteArray(
        length,
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

public BigByteArray(
  final long length,
  final boolean useFiles
) throws
  IOException
{
  this(
    length,
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

public BigByteArray(
  final long length,
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
  }
  final BigInteger intMax = BigInteger.valueOf(Integer.MAX_VALUE);
  {
    final BigInteger nBytes =
      BigInteger.valueOf(length)
    ;
    final BigInteger nBytesPerBuffer =
      intMax
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

public final byte getValue(
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
  final int i = (int)(index / this.b[0].capacity());
  final int j = (int)(index % this.b[0].capacity());
  return this.b[i].get(j);
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
  final byte value
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
  final int i = (int)(index / this.b[0].capacity());
  final int j = (int)(index % this.b[0].capacity());
  this.b[i].put(j, value);
}

}
