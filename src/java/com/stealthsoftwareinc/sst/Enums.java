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

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

public final class Enums {
  private Enums() {
  }

  //--------------------------------------------------------------------
  // toIntMap
  //--------------------------------------------------------------------
  //
  // Returns the map {(x.toInt(), x) for all x in T}. The caller takes
  // ownership of the map.
  //

  public static final <T extends Enum<T> & ToInt> Map<Integer, T>
  toIntMap(final Class<T> type) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(type != null, "type != null");
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final T[] values = type.getEnumConstants();
    final Map<Integer, T> map = new HashMap<Integer, T>();
    for (int i = 0; i < values.length; ++i) {
      final T value = values[i];
      final T collision = map.put(value.toInt(), value);
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(
              collision == null,
              "Enum type must not contain duplicate toInt() values.");
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
    }
    return map;
  }

  //--------------------------------------------------------------------
  // toStringMap
  //--------------------------------------------------------------------

  public static final <T extends Enum<T>> Map<String, T>
  toStringMap(final Class<T> type) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(type != null);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    final List<T> values = Arrays.asList(type.getEnumConstants());
    final Map<String, T> map = new HashMap<String, T>();
    for (final T value : values) {
      final T collision = map.put(value.toString(), value);
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(collision == null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
    }
    return map;
  }

  //--------------------------------------------------------------------

  private static <T extends Enum<T>> void
  checkValues(final T[] values) {
    SST_ASSERT(values != null);
    SST_ASSERT(!Arrays.asList(values).contains(null));
    SST_ASSERT(new HashSet<T>(Arrays.asList(values)).size()
               == values.length);
  }

  private static <T extends Enum<T> & ToInt> void
  checkValuesToInt(final T[] values, final boolean useToInt) {
    checkValues(values);
    if (useToInt) {
      final HashSet<Integer> xs = new HashSet<Integer>();
      for (int i = 0; i != values.length; ++i) {
        SST_ASSERT(xs.add(values[i].toInt()));
      }
    }
  }

  private static <T extends Enum<T>> void
  checkValuesToString(final T[] values) {
    checkValues(values);
    final HashSet<String> xs = new HashSet<String>();
    for (int i = 0; i != values.length; ++i) {
      SST_ASSERT(xs.add(values[i].toString()));
    }
  }

  private static <T extends Enum<T>> void
  checkValues(final Map<?, T> values) {
    SST_ASSERT(values != null);
    SST_ASSERT(!values.values().contains(null));
  }

  //--------------------------------------------------------------------

  // TODO: Maybe CreateFromInt<T> wants to exist?

  public static final <T extends Enum<T>>
      T fromInt(final Class<T> type, final T[] values, final int src) {
    if (!SST_NDEBUG) {
      try {
        SST_ASSERT(type != null);
        checkValues(values);
      } catch (final Throwable e) {
        SST_ASSERT(e);
      }
    }
    if (src < 0 || src >= values.length) {
      throw new EnumConstantNotPresentException(type,
                                                String.valueOf(src));
    }
    return values[src];
  }

  public static final <T extends Enum<T>> T fromInt(final Class<T> type,
                                                    final int src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
    }
    return fromInt(type, type.getEnumConstants(), src);
  }

  public static final <T extends Enum<T> & ToInt>
      T fromInt(final Class<T> type,
                final T[] values,
                final int src,
                final boolean useToInt) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValuesToInt(values, useToInt);
    }
    if (!useToInt) {
      return fromInt(type, values, src);
    }
    for (int i = 0; i != values.length; ++i) {
      if (src == values[i].toInt()) {
        return values[i];
      }
    }
    throw new EnumConstantNotPresentException(type,
                                              String.valueOf(src));
  }

  public static final <T extends Enum<T> & ToInt> T
  fromInt(final Class<T> type, final int src, final boolean useToInt) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
    }
    return fromInt(type, type.getEnumConstants(), src, useToInt);
  }

  public static final <T extends Enum<T>>
      T fromInt(final Class<T> type,
                final Map<Integer, T> values,
                final int src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    final T dst = values.get(src);
    if (dst != null) {
      return dst;
    }
    throw new EnumConstantNotPresentException(type,
                                              String.valueOf(src));
  }

  //--------------------------------------------------------------------

  // TODO: Maybe CreateFromString<T> wants to exist?

  public static final <T extends Enum<T>>
      T fromString(final Class<T> type,
                   final CharSequence src,
                   final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      SST_ASSERT(src != null);
    }
    final String srcString = reverseAsciiCase ?
                                 Strings.reverseAsciiCase(src) :
                                 src.toString();
    try {
      return T.valueOf(type, srcString);
    } catch (final IllegalArgumentException e) {
      throw new EnumConstantNotPresentException(type, srcString);
    }
  }

  public static final <T extends Enum<T>>
      T fromString(final Class<T> type, final CharSequence src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      SST_ASSERT(src != null);
    }
    return fromString(type, src, false);
  }

  //--------------------------------------------------------------------

  public static final <T extends Enum<T>>
      T fromString(final Class<T> type,
                   final T[] values,
                   final CharSequence src,
                   final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValuesToString(values);
      SST_ASSERT(src != null);
    }
    final String srcString = reverseAsciiCase ?
                                 Strings.reverseAsciiCase(src) :
                                 src.toString();
    for (int i = 0; i != values.length; ++i) {
      if (srcString.equals(values[i].toString())) {
        return values[i];
      }
    }
    throw new EnumConstantNotPresentException(type, srcString);
  }

  public static final <T extends Enum<T>>
      T fromString(final Class<T> type,
                   final T[] values,
                   final CharSequence src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValuesToString(values);
      SST_ASSERT(src != null);
    }
    return fromString(type, values, src, false);
  }

  //--------------------------------------------------------------------

  public static final <T extends Enum<T>>
      T fromString(final Class<T> type,
                   final Map<String, T> values,
                   final CharSequence src,
                   final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
      SST_ASSERT(src != null);
    }
    final String srcString = reverseAsciiCase ?
                                 Strings.reverseAsciiCase(src) :
                                 src.toString();
    final T dst = values.get(srcString);
    if (dst != null) {
      return dst;
    }
    throw new EnumConstantNotPresentException(type, srcString);
  }

  public static final <T extends Enum<T>>
      T fromString(final Class<T> type,
                   final Map<String, T> values,
                   final CharSequence src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
      SST_ASSERT(src != null);
    }
    return fromString(type, values, src, false);
  }

  //--------------------------------------------------------------------

  public static final <T extends Enum<T>> CreateFromJson<T>
  fromJson(final Class<T> type, final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
    }
    return new CreateFromJson<T>() {
      @Override
      public final T createFromJson(final Object src) {
        try {
          // TODO: We could also accept an integer here via fromInt.
          return fromString(type,
                            Json.getAs(src, (String)null),
                            reverseAsciiCase);
        } catch (final JsonException e) {
          throw e;
        } catch (final Throwable e) {
          throw new JsonException(e);
        }
      }
    };
  }

  public static final <T extends Enum<T>> CreateFromJson<T>
  fromJson(final Class<T> type) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
    }
    return fromJson(type, false);
  }

  public static final <T extends Enum<T>>
      T fromJson(final Class<T> type,
                 final Object src,
                 final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
    }
    return fromJson(type, reverseAsciiCase).createFromJson(src);
  }

  public static final <T extends Enum<T>>
      T fromJson(final Class<T> type, final Object src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
    }
    return fromJson(type, src, false);
  }

  public static final <T extends Enum<T>> CreateFromJson<T>
  fromJson(final Class<T> type,
           final T[] values,
           final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return new CreateFromJson<T>() {
      @Override
      public final T createFromJson(final Object src) {
        try {
          // TODO: We could also accept an integer here via fromInt.
          return fromString(type,
                            values,
                            Json.getAs(src, (String)null),
                            reverseAsciiCase);
        } catch (final JsonException e) {
          throw e;
        } catch (final Throwable e) {
          throw new JsonException(e);
        }
      }
    };
  }

  public static final <T extends Enum<T>> CreateFromJson<T>
  fromJson(final Class<T> type, final T[] values) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return fromJson(type, false);
  }

  public static final <T extends Enum<T>>
      T fromJson(final Class<T> type,
                 final T[] values,
                 final Object src,
                 final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return fromJson(type, values, reverseAsciiCase).createFromJson(src);
  }

  public static final <T extends Enum<T>> T
  fromJson(final Class<T> type, final T[] values, final Object src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return fromJson(type, values, src, false);
  }

  public static final <T extends Enum<T>> CreateFromJson<T>
  fromJson(final Class<T> type,
           final Map<String, T> values,
           final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return new CreateFromJson<T>() {
      @Override
      public final T createFromJson(final Object src) {
        try {
          // TODO: We could also accept an integer here via fromInt.
          return fromString(type,
                            values,
                            Json.getAs(src, (String)null),
                            reverseAsciiCase);
        } catch (final JsonException e) {
          throw e;
        } catch (final Throwable e) {
          throw new JsonException(e);
        }
      }
    };
  }

  public static final <T extends Enum<T>> CreateFromJson<T>
  fromJson(final Class<T> type, final Map<String, T> values) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return fromJson(type, false);
  }

  public static final <T extends Enum<T>>
      T fromJson(final Class<T> type,
                 final Map<String, T> values,
                 final Object src,
                 final boolean reverseAsciiCase) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return fromJson(type, values, reverseAsciiCase).createFromJson(src);
  }

  public static final <T extends Enum<T>>
      T fromJson(final Class<T> type,
                 final Map<String, T> values,
                 final Object src) {
    if (!SST_NDEBUG) {
      SST_ASSERT(type != null);
      checkValues(values);
    }
    return fromJson(type, values, src, false);
  }

  //--------------------------------------------------------------------
}
