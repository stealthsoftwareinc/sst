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
 * <code>com.stealthsoftwareinc.sst.BlobStore</code>
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

import com.stealthsoftwareinc.sst.ConfigH;
import com.stealthsoftwareinc.sst.ConcurrentLruQueue;
import com.stealthsoftwareinc.sst.FileOps;
import com.stealthsoftwareinc.sst.InternalErrorStatus;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import com.stealthsoftwareinc.sst.JavaLex;
import com.stealthsoftwareinc.sst.Memory;
import com.stealthsoftwareinc.sst.NullPointerStatus;
import com.stealthsoftwareinc.sst.Uris;
import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.nio.file.StandardOpenOption;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Collections;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

/* end_imports */

/**
 * A content-addressed collection of byte arrays stored on disk.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class BlobStore
{

/**
 * The name of the hash algorithm being used to hash the byte arrays.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

private final String algorithm;

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

private final ConcurrentHashMap<String, byte[]> cache;

/**
 * The directory on disk being used to store this blob store.
 * <p>
 * If this variable is a null reference, then the directory is the
 * current working directory.
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

private final File directory;

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

private final int hashNibbleSize;

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

private final ConcurrentLruQueue<String> lruQueue;

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

private long memoryUsage;

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

private final String salt;

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

public BlobStore(
  final File directory,
  final String algorithm,
  final boolean preferAlgorithmFile,
  final boolean algorithmFileMustMatchAlgorithm
) throws
  IOException
{
  this.cache = new ConcurrentHashMap<String, byte[]>();
  this.directory = directory;
  final File algorithmFile = new File(this.directory, "algorithm");
  final boolean algorithmFileExists = algorithmFile.isFile();
  {
    final Path path = algorithmFile.toPath();
    final Charset charset = StandardCharsets.UTF_8;
    final String alg = (algorithm == null) ? "SHA-256" : algorithm;
    if (algorithmFileExists && preferAlgorithmFile) {
      final byte[] bytes = Files.readAllBytes(path);
      this.algorithm = new String(bytes, charset).trim();
      if (algorithmFileMustMatchAlgorithm) {
        if (!this.algorithm.equals(alg)) {
          throw (InvalidArgumentStatus)
            new InvalidArgumentStatus(
              "algorithm = \"" +
              JavaLex.escape(this.algorithm) +
              "\" from file \"" +
              JavaLex.escape(algorithmFile.toString()) +
              "\" does not match algorithm = " +
              (
                (algorithm == null) ?
                  "null"
                :
                  "\"" +
                  JavaLex.escape(algorithm) +
                  "\""
              )
            ).initCause(null)
          ;
        }
      }
    } else {
      this.algorithm = alg;
      final Set<String> line = Collections.singleton(this.algorithm);
      FileOps.makeParents(algorithmFile);
      Files.write(path, line, charset);
    }
  }
  {
    final MessageDigest hasher;
    try {
      hasher = MessageDigest.getInstance(this.algorithm);
    } catch (final NoSuchAlgorithmException e) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "algorithm = \"" +
          JavaLex.escape(this.algorithm) +
          "\" " +
          (
            (algorithmFileExists) ?
              "from file \"" +
              JavaLex.escape(algorithmFile.toString()) +
              "\" "
            :
              ""
          ) +
          "is not recognized"
        ).initCause(e)
      ;
    }
    final int hashOctetSize = hasher.digest().length;
    if (hashOctetSize > Integer.MAX_VALUE / 2) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "the digest size of algorithm = \"" +
          JavaLex.escape(this.algorithm) +
          "\" is too big"
        ).initCause(null)
      ;
    }
    this.hashNibbleSize = hashOctetSize * 2;
  }
  this.lruQueue = new ConcurrentLruQueue<String>();
  this.memoryUsage = 0;
  {
    final byte[] salt = new byte[8];
    new SecureRandom().nextBytes(salt);
    this.salt = Memory.toHexString(salt).toString();
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

public final byte[] get(
  final CharSequence hash
) throws
  IOException
{
  if (hash == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "hash is a null reference"
      ).initCause(null)
    ;
  }
  return this.get(hash.toString());
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

public final byte[] get(
  final String hash
) throws
  IOException
{
  if (hash == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "hash is a null reference"
      ).initCause(null)
    ;
  }
  if (hash.length() != this.hashNibbleSize) {
    throw (InvalidArgumentStatus)
      new InvalidArgumentStatus(
        "hash does not contain the correct number of characters"
      ).initCause(null)
    ;
  }
  for (int i = 0; i != hash.length(); ++i) {
    if (!Uris.isHexDigit(hash.charAt(i), true)) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "hash does not contain only uppercase hexadecimal digits"
        ).initCause(null)
      ;
    }
  }
  {
    final byte[] blob = this.cache.get(hash);
    if (blob != null) {
      this.lruQueue.add(hash);
      return blob;
    }
  }
  {
    final File file = this.getBlobFile(hash);
    if (!file.isFile()) {
      return null;
    }
    final byte[] blob = Files.readAllBytes(file.toPath());
    final byte[] oldBlob = this.cache.putIfAbsent(hash, blob);
    this.lruQueue.add(hash);
    if (oldBlob == null) {
      this.memoryUsage += blob.length;
      return blob;
    }
    return oldBlob;
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

private final File getBlobFile(
  final String hash
) {
  File file = new File(this.directory, "blobs");
  if (hash.length() > 2) {
    file = new File(file, hash.substring(0, 2));
  }
  if (hash.length() > 4) {
    file = new File(file, hash.substring(0, 4));
  }
  file = new File(file, hash);
  return file;
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
  final long memoryLimit
) {
  final long oldMemoryUsage = this.memoryUsage;
  while (this.memoryUsage > memoryLimit) {
    final String hash = this.lruQueue.poll();
    if (hash == null) {
      break;
    }
    final byte[] blob = this.cache.get(hash);
    this.cache.remove(hash);
    this.memoryUsage -= blob.length;
  }
  long memoryFreed = 0;
  memoryFreed += oldMemoryUsage - this.memoryUsage;
  memoryFreed += this.lruQueue.purge();
  return memoryFreed;
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

public final void put(
  final CharSequence hash,
  final byte[] blob
) throws
  IOException
{
  if (hash == null) {
    this.put((String)null, blob);
    return;
  }
  this.put(hash.toString(), blob);
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

public final void put(
  final String hash,
  final byte[] blob
) throws
  IOException
{
  if (blob == null) {
    this.put(hash, new byte[0]);
    return;
  }
  if (hash == null) {
    final MessageDigest hasher;
    try {
      hasher = MessageDigest.getInstance(this.algorithm);
    } catch (final NoSuchAlgorithmException e) {
      throw (InternalErrorStatus)
        new InternalErrorStatus(
          "MessageDigest.getInstance(\"" +
          JavaLex.escape(this.algorithm) +
          "\") succeeded earlier but is now throwing " +
          "NoSuchAlgorithmException"
        ).initCause(e)
      ;
    }
    final byte[] digest = hasher.digest(blob);
    this.put(Memory.toHexString(digest), blob);
    return;
  }
  if (ConfigH.ENABLE_INVALID_ARGUMENT_CHECKS) {
    if (hash.length() != this.hashNibbleSize) {
      throw (InvalidArgumentStatus)
        new InvalidArgumentStatus(
          "hash does not contain the correct number of characters"
        ).initCause(null)
      ;
    }
    for (int i = 0; i != hash.length(); ++i) {
      if (!Uris.isHexDigit(hash.charAt(i), true)) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "hash does not contain only uppercase hexadecimal digits"
          ).initCause(null)
        ;
      }
    }
    {
      final MessageDigest hasher;
      try {
        hasher = MessageDigest.getInstance(this.algorithm);
      } catch (final NoSuchAlgorithmException e) {
        throw (InternalErrorStatus)
          new InternalErrorStatus(
            "MessageDigest.getInstance(\"" +
            JavaLex.escape(this.algorithm) +
            "\") succeeded earlier but is now throwing " +
            "NoSuchAlgorithmException"
          ).initCause(e)
        ;
      }
      final byte[] digest = hasher.digest(blob);
      if (!hash.equals(Memory.toHexString(digest).toString())) {
        throw (InvalidArgumentStatus)
          new InvalidArgumentStatus(
            "hash is not the hash of blob"
          ).initCause(null)
        ;
      }
    }
  }
  if (this.get(hash) != null) {
    return;
  }
  final File file = this.getBlobFile(hash);
  FileOps.makeParents(file);
  final File newFile;
  {
    final File parent = file.getParentFile();
    final long thread = Thread.currentThread().getId();
    final String name = file.getName() + "." + this.salt + "-" + thread;
    long attempt = 1;
    for (;;) {
      final File f = new File(parent, name + "-" + attempt);
      try {
        Files.write(
          f.toPath(),
          blob,
          StandardOpenOption.CREATE_NEW,
          StandardOpenOption.WRITE
        );
      } catch (final FileAlreadyExistsException e) {
        ++attempt;
        if (attempt < 0) {
          attempt = 1;
        }
        continue;
      }
      newFile = f;
      break;
    }
  }
  try {
    Files.move(
      newFile.toPath(),
      file.toPath(),
      StandardCopyOption.ATOMIC_MOVE
    );
  } catch (final FileAlreadyExistsException e) {
    newFile.delete();
    return;
  }
  final byte[] oldBlob = this.cache.putIfAbsent(hash, blob);
  this.lruQueue.add(hash);
  if (oldBlob == null) {
    this.memoryUsage += blob.length;
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

public final void put(
  final byte[] blob
) throws
  IOException
{
  this.put((String)null, blob);
}

}
