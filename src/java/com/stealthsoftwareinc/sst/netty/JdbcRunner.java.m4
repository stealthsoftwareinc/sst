dnl
dnl Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
dnl
dnl Permission is hereby granted, free of charge, to any person
dnl obtaining a copy of this software and associated documentation
dnl files (the "Software"), to deal in the Software without
dnl restriction, including without limitation the rights to use,
dnl copy, modify, merge, publish, distribute, sublicense, and/or
dnl sell copies of the Software, and to permit persons to whom the
dnl Software is furnished to do so, subject to the following
dnl conditions:
dnl
dnl The above copyright notice and this permission notice (including
dnl the next paragraph) shall be included in all copies or
dnl substantial portions of the Software.
dnl
dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl OTHER DEALINGS IN THE SOFTWARE.
dnl
dnl SPDX-License-Identifier: MIT
dnl

include(`src/m4/config.m4')

changequote(`{|', `|}')

ifdef({|make_rules|}, {|{|
  |}make_target{|: src/m4/config.m4
|}|}, {|{|

package com.stealthsoftwareinc.sst.netty;

|}ifelse(WITH_NETTY, 1, {|{|

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import com.stealthsoftwareinc.sst.Consumer;
import com.stealthsoftwareinc.sst.JdbcConnection;
import com.stealthsoftwareinc.sst.Pool;
import com.stealthsoftwareinc.sst.PoolEntry;
import com.stealthsoftwareinc.sst.UncheckedException;
import io.netty.util.concurrent.EventExecutorGroup;
import io.netty.util.concurrent.GenericFutureListener;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

public final class JdbcRunner implements AutoCloseable {
  private final Set<Statement> statements_ = new HashSet<Statement>();
  private final Set<ResultSet> resultSets_ = new HashSet<ResultSet>();

  private boolean brokenForever_ = false;

  private PoolEntry<io.netty.util.concurrent.Future<JdbcConnection>>
      connectionEntry_ = null;
  private AtomicBoolean connectionIsDone_ = null;
  private AtomicReference<Object> connection_ = null;
  private AtomicReference<Throwable> connectionException_ = null;

  private AtomicBoolean resultIsDone_ = null;
  private AtomicReference<Object> result_ = null;
  private AtomicReference<Throwable> resultException_ = null;

  public JdbcRunner() {
  }

  private void close(final boolean closeConnection) {
    try {
      for (final ResultSet x : resultSets_) {
        try {
          x.close();
        } catch (final Throwable ignore) {
        }
      }
      resultSets_.clear();
    } catch (final Throwable e) {
      brokenForever_ = true;
    }
    try {
      for (final Statement x : statements_) {
        try {
          x.close();
        } catch (final Throwable ignore) {
        }
      }
      statements_.clear();
    } catch (final Throwable e) {
      brokenForever_ = true;
    }
    if (connectionEntry_ != null) {
      if (closeConnection) {
        try {
          connectionEntry_.object().sync().get().close();
        } catch (final Throwable ignore) {
        }
      } else {
        try {
          connectionEntry_.release();
        } catch (final Throwable e) {
          try {
            connectionEntry_.object().sync().get().close();
          } catch (final Throwable ignore) {
          }
        }
      }
    }
    connectionEntry_ = null;
    connectionIsDone_ = null;
    connection_ = null;
    connectionException_ = null;
    resultIsDone_ = null;
    result_ = null;
    resultException_ = null;
  }

  @Override
  public final void close() {
    close(false);
  }

  private <T> void
  runAsyncHelper(final Consumer<T> onSuccess,
                 final Consumer<Throwable> onFailure,
                 final io.netty.util.concurrent.Future<T> future,
                 final AtomicBoolean resultIsDone,
                 final AtomicReference<Object> result,
                 final AtomicReference<Throwable> resultException) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(future != null);
        SST_ASSERT(resultIsDone != null);
        SST_ASSERT(result != null);
        SST_ASSERT(resultException != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    T x = null;
    try {
      x = future.sync().get();
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(x != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      result.set(x);
      resultIsDone.set(true);
      try {
        if (onSuccess != null) {
          onSuccess.accept(x);
        }
      } catch (final Throwable e2) {
      }
    } catch (final Throwable e) {
      resultException.set(e);
      resultIsDone.set(true);
      try {
        if (x instanceof AutoCloseable) {
          ((AutoCloseable)x).close();
        }
      } catch (final Throwable e2) {
      }
      try {
        if (onFailure != null) {
          onFailure.accept(e);
        }
      } catch (final Throwable e2) {
      }
    }
  }

  //
  // The first call to open() after construction or after any close()
  // call starts an asynchronous connection request via connectionPool.
  // When the request completes, whether by success or failure, either
  // onSuccess or onFailure is called. onFailure will not be called if
  // onSuccess throws an exception. All exceptions thrown by onFailure
  // are ignored. onSuccess and onFailure may be set to null to skip
  // their respective calls.
  //
  // open() returns true if and only if the connection is currently
  // open. It is possible for the first call to return true.
  //
  // A non-first call to open() ignores its parameters and simply
  // returns true or false to indicate the status.
  //

  public final boolean
  open(final Pool<io.netty.util.concurrent.Future<JdbcConnection>>
           connectionPool,
       final Consumer<JdbcConnection> onSuccess,
       final Consumer<Throwable> onFailure) {
    try {
      if (brokenForever_) {
        throw new RuntimeException();
      }
      if (connectionIsDone_ != null) {
        if (!connectionIsDone_.get()) {
          return false;
        }
        final Throwable e = connectionException_.get();
        if (e != null) {
          close(true);
          throw e;
        }
        return true;
      }
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(connectionPool != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final AtomicBoolean connectionIsDone = new AtomicBoolean(false);
      final AtomicReference<Object> connection =
          new AtomicReference<Object>(null);
      final AtomicReference<Throwable> connectionException =
          new AtomicReference<Throwable>(null);
      final PoolEntry<io.netty.util.concurrent.Future<JdbcConnection>>
          connectionEntry = connectionPool.acquire();
      try {
        connectionEntry.object().addListener(
            new GenericFutureListener<
                io.netty.util.concurrent.Future<JdbcConnection>>() {
              @Override
              public final void operationComplete(
                  final io.netty.util.concurrent
                      .Future<JdbcConnection> f) {
                if (!SST_NDEBUG) {
                  try {
                    SST_ASSERT(f != null);
                  } catch (final Throwable e) {
                    SST_ASSERT(e);
                  }
                }
                runAsyncHelper(onSuccess,
                               onFailure,
                               f,
                               connectionIsDone,
                               connection,
                               connectionException);
              }
            });
      } catch (final Throwable e) {
        runAsyncHelper(onSuccess,
                       onFailure,
                       connectionEntry.object(),
                       connectionIsDone,
                       connection,
                       connectionException);
      }
      connectionEntry_ = connectionEntry;
      connectionIsDone_ = connectionIsDone;
      connection_ = connection;
      connectionException_ = connectionException;
      return open(connectionPool, onSuccess, onFailure);
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  public final void close(final Statement x) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(x != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try {
      try {
        statements_.remove(x);
      } catch (final Throwable e) {
        brokenForever_ = true;
        close(true);
        throw e;
      }
      try {
        x.close();
      } catch (final Throwable e2) {
      }
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  public final void close(final ResultSet x) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(x != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try {
      try {
        resultSets_.remove(x);
      } catch (final Throwable e) {
        brokenForever_ = true;
        close(true);
        throw e;
      }
      try {
        x.close();
      } catch (final Throwable e2) {
      }
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  public final JdbcConnection connection() {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(connectionIsDone_ != null);
        SST_ASSERT(connectionIsDone_.get());
        SST_ASSERT(connectionException_.get() == null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (brokenForever_) {
      throw new RuntimeException();
    }
    @SuppressWarnings("unchecked")
    final JdbcConnection x = (JdbcConnection)connection_.get();
    return x;
  }

  private void track(final Object x) {
    try {
      if (x instanceof Statement) {
        try {
          statements_.add((Statement)x);
        } catch (final Throwable e) {
          brokenForever_ = true;
          close(true);
          throw e;
        }
      } else if (x instanceof ResultSet) {
        try {
          resultSets_.add((ResultSet)x);
        } catch (final Throwable e) {
          brokenForever_ = true;
          close(true);
          throw e;
        }
      }
    } catch (final Throwable e) {
      try {
        if (x instanceof AutoCloseable) {
          ((AutoCloseable)x).close();
        }
      } catch (final Throwable ignore) {
      }
      throw e;
    }
  }

  public final <T> T runAsync(final Callable<T> function,
                              final EventExecutorGroup executor,
                              final Consumer<T> onSuccess,
                              final Consumer<Throwable> onFailure) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(connectionIsDone_ != null);
        SST_ASSERT(connectionIsDone_.get());
        SST_ASSERT(connectionException_.get() == null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try {
      if (brokenForever_) {
        throw new RuntimeException();
      }
      if (resultIsDone_ != null) {
        if (!resultIsDone_.get()) {
          return null;
        }
        final Throwable e = resultException_.get();
        if (e != null) {
          close(true);
          throw e;
        }
        @SuppressWarnings("unchecked")
        final T x = (T)result_.get();
        track(x);
        resultIsDone_ = null;
        result_ = null;
        resultException_ = null;
        return x;
      }
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(function != null);
          SST_ASSERT(executor != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final AtomicBoolean resultIsDone = new AtomicBoolean(false);
      final AtomicReference<Object> result =
          new AtomicReference<Object>(null);
      final AtomicReference<Throwable> resultException =
          new AtomicReference<Throwable>(null);
      final io.netty.util.concurrent.Future<T> future =
          executor.submit(function);
      try {
        future.addListener(new GenericFutureListener<
                           io.netty.util.concurrent.Future<T>>() {
          @Override
          public final void operationComplete(
              final io.netty.util.concurrent.Future<T> f) {
            if (!SST_NDEBUG) {
              try {
                SST_ASSERT(f != null);
              } catch (final Throwable e) {
                SST_ASSERT(e);
              }
            }
            runAsyncHelper(onSuccess,
                           onFailure,
                           f,
                           resultIsDone,
                           result,
                           resultException);
          }
        });
      } catch (final Throwable e) {
        runAsyncHelper(onSuccess,
                       onFailure,
                       future,
                       resultIsDone,
                       result,
                       resultException);
      }
      resultIsDone_ = resultIsDone;
      result_ = result;
      resultException_ = resultException;
      return runAsync(function, executor, onSuccess, onFailure);
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  public final <T> T run(final Callable<T> function) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(connectionIsDone_ != null);
        SST_ASSERT(connectionIsDone_.get());
        SST_ASSERT(connectionException_.get() == null);
        SST_ASSERT(resultIsDone_ == null);
        SST_ASSERT(function != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (brokenForever_) {
      throw new RuntimeException();
    }
    try {
      final T x;
      try {
        x = function.call();
      } catch (final Throwable e) {
        close(true);
        throw e;
      }
      track(x);
      return x;
    } catch (final RuntimeException e) {
      throw e;
    } catch (final Error e) {
      throw e;
    } catch (final Throwable e) {
      throw new UncheckedException(e);
    }
  }

  //--------------------------------------------------------------------
  // Convenience methods
  //--------------------------------------------------------------------

  public final PreparedStatement
  prepareStatement(final CharSequence sql) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(sql != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return run(new Callable<PreparedStatement>() {
      @Override
      public final PreparedStatement call() throws Exception {
        return connection().connection().prepareStatement(
            sql.toString());
      }
    });
  }

  public final PreparedStatement
  prepareStreamingStatement(final CharSequence sql) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(sql != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    return run(new Callable<PreparedStatement>() {
      @Override
      public final PreparedStatement call() throws Exception {
        return connection().prepareStreamingStatement(sql.toString());
      }
    });
  }

  //--------------------------------------------------------------------
}

|}|}, {|{|

public final class JdbcRunner {
  private JdbcRunner() {
  }
}

|}|})|})
