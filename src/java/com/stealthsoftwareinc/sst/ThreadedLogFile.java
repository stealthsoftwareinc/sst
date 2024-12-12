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

package com.stealthsoftwareinc.sst;

import static com.stealthsoftwareinc.sst.Assert.SST_ASSERT;
import static com.stealthsoftwareinc.sst.Assert.SST_NDEBUG;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CodingErrorAction;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;

/**
 * A thread-safe log file with a background thread that flushes to file
 * periodically, recreates the file whenever necessary, and hides all
 * exceptions.
 */

public final class ThreadedLogFile implements AutoCloseable {

  //--------------------------------------------------------------------

  private final AtomicReference<Throwable> hardException_ =
      new AtomicReference<Throwable>(null);

  public final AtomicReference<Throwable> hardException() {
    return hardException_;
  }

  private void hardException(final Throwable e) {
    hardException_.set(e);
  }

  //--------------------------------------------------------------------

  private final AtomicReference<Throwable> softException_ =
      new AtomicReference<Throwable>(null);

  public final AtomicReference<Throwable> softException() {
    return softException_;
  }

  private void softException(final Throwable e) {
    softException_.set(e);
  }

  //--------------------------------------------------------------------

  private final AtomicReference<String> file_ =
      new AtomicReference<String>(null);

  public final String file() {
    return file_.get();
  }

  public final ThreadedLogFile file(final String f) {
    file_.set(f);
    return this;
  }

  public final ThreadedLogFile file(final File f) {
    return file(f != null ? f.toString() : null);
  }

  public final ThreadedLogFile file(final Path f) {
    return file(f != null ? f.toString() : null);
  }

  //--------------------------------------------------------------------

  private final AtomicLong flushCooldownCount_ = new AtomicLong(5);

  public final long flushCooldownCount() {
    return flushCooldownCount_.get();
  }

  public final ThreadedLogFile flushCooldownCount(final long count) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(count >= 0);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    flushCooldownCount_.set(count);
    return this;
  }

  //--------------------------------------------------------------------

  private final AtomicReference<TimeUnit> flushCooldownUnit_ =
      new AtomicReference<TimeUnit>(TimeUnit.SECONDS);

  public final TimeUnit flushCooldownUnit() {
    return flushCooldownUnit_.get();
  }

  public final ThreadedLogFile flushCooldownUnit(final TimeUnit unit) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(unit != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    flushCooldownUnit_.set(unit);
    return this;
  }

  //--------------------------------------------------------------------

  public final ThreadedLogFile flushCooldown(final long count,
                                             final TimeUnit unit) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(count >= 0);
        SST_ASSERT(unit != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    flushCooldownCount_.set(count);
    flushCooldownUnit_.set(unit);
    return this;
  }

  //--------------------------------------------------------------------

  private final AtomicReference<TimeZone> timezone_ =
      new AtomicReference<TimeZone>(null);

  public final TimeZone timezone() {
    return timezone_.get();
  }

  public final ThreadedLogFile timezone(final TimeZone zone) {
    timezone_.set(zone);
    return this;
  }

  //--------------------------------------------------------------------

  private final AtomicReference<String> timestampPattern_ =
      new AtomicReference<String>("[yyyy-MM-dd'T'HH:mm:ss.SSSXXX] ");

  public final String timestampPattern() {
    return timestampPattern_.get();
  }

  public final ThreadedLogFile timestampPattern(final String pattern) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(pattern != null);
        new SimpleDateFormat(pattern, Locale.ROOT);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    timestampPattern_.set(pattern);
    return this;
  }

  //--------------------------------------------------------------------

  public final String timestamp() {
    return new SimpleDateFormat(timestampPattern(), Locale.ROOT)
        .format(new Date());
  }

  public final StringBuilder timestamp(final StringBuilder dst) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(dst != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    dst.append(timestamp());
    return dst;
  }

  //--------------------------------------------------------------------

  private final AtomicReference<ConcurrentLinkedQueue<String>>
      strings_ = new AtomicReference<ConcurrentLinkedQueue<String>>(
          new ConcurrentLinkedQueue<String>());
  private final CountDownLatch stop_ = new CountDownLatch(1);
  private final AtomicReference<Thread> thread_ =
      new AtomicReference<Thread>(null);

  public ThreadedLogFile() {
    thread_.set(new Thread(new Runnable() {
      @Override
      public final void run() {
        try {
          boolean stop = false;
          while (!stop) {
            try {
              stop = stop_.await(flushCooldownCount(),
                                 flushCooldownUnit());
            } catch (final InterruptedException e) {
              stop = true;
            }
            final ConcurrentLinkedQueue<String> strings =
                strings_.get();
            if (strings == null) {
              break;
            }
            final String f1 = file();
            if (f1 == null) {
              strings.clear();
              continue;
            }
            final String f2;
            {
              final TimeZone zone = timezone();
              final Calendar calendar =
                  zone != null ?
                      new GregorianCalendar(zone, Locale.ROOT) :
                      new GregorianCalendar(Locale.ROOT);
              final StringBuilder sb = new StringBuilder();
              char c1 = 0;
              for (int i = 0; i < f1.length(); ++i) {
                final char c2 = f1.charAt(i);
                if (c1 == '%') {
                  switch (c2) {
                    case 'Y': {
                      sb.append(
                          String.valueOf(calendar.get(Calendar.YEAR)));
                    } break;
                    case 'm': {
                      sb.append(String.format(
                          "%02d",
                          calendar.get(Calendar.MONTH) + 1));
                    } break;
                    case 'd': {
                      sb.append(String.format(
                          "%02d",
                          calendar.get(Calendar.DAY_OF_MONTH)));
                    } break;
                    default: {
                      sb.append(c2);
                    } break;
                  }
                } else if (c2 != '%') {
                  sb.append(c2);
                }
                c1 = c2;
              }
              if (c1 == '%') {
                sb.append(c1);
              }
              f2 = sb.toString();
            }
            final Path d = Paths.get(f2).getParent();
            if (d == null) {
              strings.clear();
              continue;
            }
            final CharsetEncoder encoder =
                StandardCharsets.UTF_8.newEncoder()
                    .onMalformedInput(CodingErrorAction.REPLACE)
                    .onUnmappableCharacter(CodingErrorAction.REPLACE);
            try {
              Files.createDirectories(d);
              try (final FileOutputStream x1 =
                       new FileOutputStream(f2, true);
                   final OutputStreamWriter x2 =
                       new OutputStreamWriter(x1, encoder);
                   final BufferedWriter writer =
                       new BufferedWriter(x2)) {
                while (true) {
                  final String string = strings.poll();
                  if (string == null) {
                    break;
                  }
                  writer.write(string, 0, string.length());
                }
              }
            } catch (final IOException e) {
              softException(e);
              strings.clear();
            }
          }
        } catch (final Throwable e) {
          hardException(e);
          strings_.set(null);
        }
      }
    }));
    thread_.get().start();
  }

  //--------------------------------------------------------------------

  @Override
  public final void close() {
    try {
      final Thread thread = thread_.getAndSet(null);
      if (thread != null) {
        strings_.set(null);
        stop_.countDown();
        thread.join();
      }
    } catch (final Throwable e) {
    }
  }

  //--------------------------------------------------------------------

  public final ThreadedLogFile write(final CharSequence string) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(string != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    try {
      final ConcurrentLinkedQueue<String> strings = strings_.get();
      if (strings != null) {
        strings.add(string.toString());
      }
    } catch (final Throwable e) {
      softException(e);
    }
    return this;
  }

  // TODO: Add giveWrite() functions for possible performance gains?
  //       E.g., if the caller has a StringBuilder that they want to
  //       write and they'll no longer need it later, they could call
  //       giveWrite() to give it to us, and perhaps we can avoid the
  //       .toString() to reduce GC pressure.

  //--------------------------------------------------------------------
}
