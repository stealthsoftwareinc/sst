//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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
 * <code>com.stealthsoftwareinc.sst.ConfigBase</code>
 * Java class.
 *
 * @examples
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import com.stealthsoftwareinc.sst.ConfigMapper;
import com.stealthsoftwareinc.sst.ConfigPartition;
import com.stealthsoftwareinc.sst.InvalidOperationStatus;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.StringReader;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Dictionary;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Properties;

/* end_imports */

/**
 * Represents a configuration file.
 *
 * @examples
 * none
 */

public abstract class ConfigBase<T extends ConfigBase<T>>
{

  public static class InvalidName
  extends RuntimeException {

    InvalidName(
      final CharSequence name,
      final Throwable cause
    ) {
      super("invalid name: " + name, cause);
    }

    InvalidName(
      final CharSequence name
    ) {
      this(name, null);
    }

  }

  public static class InvalidValue
  extends RuntimeException {

    InvalidValue(
      final CharSequence name,
      final CharSequence value,
      final Throwable cause
    ) {
      super("invalid value for " + name + ": " + value, cause);
    }

    InvalidValue(
      final CharSequence name,
      final CharSequence value
    ) {
      this(name, value, null);
    }

  }

  /**
   *
   * @examples
   * none
   */

  public static final Iterable<? extends ConfigMapper> DEFAULT_ALIASES;

  /**
   *
   * @examples
   * none
   */

  public static final Charset DEFAULT_CHARSET;

  /**
   *
   * @examples
   * none
   */

  public static final String DEFAULT_CHARSET_NAME;

  /**
   *
   * @examples
   * none
   */

  public static final Iterable<ConfigPartition> DEFAULT_PARTITIONS;

  /**
   *
   * @examples
   * none
   */

  public static final File DEFAULT_PROPERTIES_FILE;

  /**
   *
   * @examples
   * none
   */

  public static final String DEFAULT_PROPERTIES_FILE_NAME;

  /**
   *
   * @examples
   * none
   */

  protected final Iterable<? extends ConfigMapper> aliases;

  /**
   * The explicit entries.
   * <p>
   * This variable is a null reference if and only if this configuration
   * is an unmodifiable view.
   * </p>
   *
   * @examples
   * none
   */

  private final HashMap<String, String> entries;

  /**
   * An unmodifiable view of the explicit entries.
   *
   * @examples
   * none
   */

  public final Map<String, String> map;

  /**
   * Indicates whether this configuration is mutable.
   *
   * @examples
   * none
   */

  private boolean mutable;

  /**
   *
   * @examples
   * none
   */

  protected final Iterable<ConfigPartition> partitions;

  /**
   * Indicates whether this configuration is an unmodifiable view.
   *
   * @examples
   * none
   */

  protected final T viewee;

  static {
    {
      final ArrayList<ConfigMapper> aliases;
      aliases = new ArrayList<ConfigMapper>();
      DEFAULT_ALIASES = Collections.unmodifiableList(aliases);
    }
    DEFAULT_CHARSET_NAME = "UTF-8";
    DEFAULT_CHARSET = Charset.forName(DEFAULT_CHARSET_NAME);
    {
      final ArrayList<ConfigPartition> partitions;
      partitions = new ArrayList<ConfigPartition>();
      partitions.add(new ConfigPartition());
      DEFAULT_PARTITIONS = Collections.unmodifiableList(partitions);
    }
    DEFAULT_PROPERTIES_FILE_NAME = "default.properties";
    DEFAULT_PROPERTIES_FILE = new File(DEFAULT_PROPERTIES_FILE_NAME);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @inheritancenotes
   * <ol>
   * <li>
   * If you are implementing an abstract subclass of this class, then you
   * should wrap this constructor with a protected constructor.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public abstract class ConfigBase&lt;T extends ConfigBase&lt;T&gt;&gt;
   *extends com.stealthsoftwareinc.sst.ConfigBase&lt;T&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *protected ConfigBase(
   *) {
   *  super();
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * <li>
   * If you are implementing a non-abstract subclass of this class, then
   * your class should be final and you should wrap this constructor with
   * a public constructor.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public final class Config
   *extends ConfigBase&lt;Config&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *public Config(
   *) {
   *  super();
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * </ol>
   *
   * @examples
   * none
   */

  protected ConfigBase(
  ) {
    this(
      DEFAULT_PARTITIONS,
      DEFAULT_ALIASES
    );
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  protected ConfigBase(
    final Iterable<ConfigPartition> partitions
  ) {
    this(
      partitions,
      DEFAULT_ALIASES
    );
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  protected ConfigBase(
    final Iterable<ConfigPartition> partitions,
    final Iterable<? extends ConfigMapper> aliases
  ) {
    if (aliases == null) {
      this.aliases = ConfigBase.DEFAULT_ALIASES;
    } else {
      this.aliases = aliases;
    }
    this.entries = new HashMap<String, String>();
    this.map = Collections.unmodifiableMap(this.entries);
    this.mutable = true;
    if (partitions == null) {
      this.partitions = ConfigBase.DEFAULT_PARTITIONS;
    } else {
      this.partitions = partitions;
    }
    this.viewee = null;
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @inheritancenotes
   * <ol>
   * <li>
   * If you are implementing an abstract subclass of this class, then you
   * should wrap this constructor with a protected constructor.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public abstract class ConfigBase&lt;T extends ConfigBase&lt;T&gt;&gt;
   *extends com.stealthsoftwareinc.sst.ConfigBase&lt;T&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *protected ConfigBase(
   *  final T src,
   *  final boolean copy,
   *  final boolean empty
   *) {
   *  super(src, copy, empty);
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * <li>
   * If you are implementing a non-abstract subclass of this class, then
   * your class should be final and you should wrap this constructor with
   * a private constructor.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public final class Config
   *extends ConfigBase&lt;Config&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *private Config(
   *  final Config src,
   *  final boolean copy,
   *  final boolean empty
   *) {
   *  super(src, copy, empty);
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * </ol>
   *
   * @examples
   * none
   */

  protected ConfigBase(
    final T src,
    final boolean copy,
    final boolean empty
  ) {
    if (copy) {
      if (src == null) {
        this.aliases = ConfigBase.DEFAULT_ALIASES;
      } else {
        this.aliases = src.aliases;
      }
      this.entries = new HashMap<String, String>();
      this.map = Collections.unmodifiableMap(this.entries);
      this.mutable = true;
      if (src == null) {
        this.partitions = ConfigBase.DEFAULT_PARTITIONS;
      } else {
        this.partitions = src.partitions;
      }
      this.viewee = null;
      if (!empty) {
        this.add(src);
      }
    } else {
      if (src == null) {
        this.viewee = this.getNull();
      } else if (src.isView()) {
        this.viewee = src.viewee;
      } else {
        this.viewee = src;
      }
      this.aliases = this.viewee.aliases;
      this.entries = null;
      this.map = this.viewee.map;
      this.mutable = false;
      this.partitions = this.viewee.partitions;
    }
  }

  /**
   * Adds a variable to the explicit entries of this configuration.
   * <p>
   * The act of
   * <i>adding</i>
   * a variable to a configuration consists of checking whether its name
   * and value are valid for the configuration, and if so, adding it to
   * the explicit entries of the configuration, replacing any existing
   * explicit entry.
   * If the name is invalid, then an
   * <code>{@link #InvalidName}</code>
   * exception is thrown.
   * Otherwise, if the value is invalid for the name, then an
   * <code>{@link #InvalidValue}</code>
   * exception is thrown.
   * </p>
   *
   * @param name
   * the name of the variable.
   * If
   * <code>name</code>
   * is
   * <code>null</code>,
   * then it is adjusted to the empty string.
   *
   * @param resolve
   * indicates whether
   * <code>name</code>
   * should be resolved with the
   * <code>{@link #resolve(CharSequence)}</code>
   * method before being considered
   *
   * @param value
   * the value of the variable.
   * If
   * <code>value</code>
   * is
   * <code>null</code>,
   * then it is adjusted to the empty string.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable, then it is unknown whether the
   * variable was added.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * <li>
   * The underlying sequences of
   * <code>name</code>
   * and
   * <code>value</code>.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are
   * true while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not modified.
   * </li>
   * <li>
   * The explicit entries of this configuration are not accessed.
   * </li>
   * <li>
   * The underlying sequences of
   * <code>name</code>
   * and
   * <code>value</code>
   * are not modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T add(
    final CharSequence name,
    final boolean resolve,
    final CharSequence value
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (name == null) {
      return this.add("", resolve, value);
    }
    if (value == null) {
      return this.add(name, resolve, "");
    }
    if (resolve) {
      return this.add(this.resolve(name), false, value);
    }
    for (final ConfigPartition partition : this.partitions) {
      if (partition.namePredicate.test(name)) {
        if (!partition.valuePredicate.test(value)) {
          throw new InvalidValue(name, value);
        }
        this.entries.put(name.toString(), value.toString());
        return this.getThis();
      }
    }
    throw new InvalidName(name);
  }

  /**
   * Adds a variable to the explicit entries of this configuration.
   * <p>
   * Calling this method is the same as calling the
   * <code>{@link com.stealthsoftwareinc.sst.ConfigBase#add(CharSequence, boolean, CharSequence)}</code>
   * method with
   * <code>resolve&nbsp;=&nbsp;true</code>.
   */

  public final T add(
    final CharSequence name,
    final CharSequence value
  ) {
    return add(name, true, value);
  }

  /**
   * Adds variables to the explicit entries of this configuration from the
   * explicit entries of (the viewee of) another configuration.
   * <p>
   * The act of
   * <i>adding</i>
   * a variable consists of checking whether its name and value are valid
   * for this configuration, and if so, adding it to the explicit entries
   * of this configuration, replacing any existing entry for its name.
   * If the name or value is invalid, then there is no effect.
   * </p>
   *
   * @param src
   * the configuration (whose viewee) whose explicit entries from which to
   * add variables.
   * If
   * <code>src</code>
   * is a null reference, then it is implicitly adjusted to an immutable
   * configuration with no explicit entries.
   * Each variable is added as if by calling the
   * <code>{@link com.stealthsoftwareinc.sst.ConfigBase#add(CharSequence, CharSequence)}</code>
   * method.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable, then an unknown subset of variables
   * was added from the explicit entries of (the viewee of)
   * <code>src</code>.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * <li>
   * The explicit entries of (the viewee of)
   * <code>src</code>.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are true
   * while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not modified.
   * </li>
   * <li>
   * The explicit entries of this configuration are not accessed.
   * </li>
   * <li>
   * The explicit entries of (the viewee of)
   * <code>src</code>
   * are not modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T add(
    final ConfigBase<?> src
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return this.add(this.getNull());
    }
    if (src == this) {
      return this.getThis();
    }
    if (src.isView()) {
      return this.add(src.viewee);
    }
    if (aliases != src.aliases) {
      return this.add(src.map);
    }
    if (partitions != src.partitions) {
      return this.add(src.map);
    }
    this.entries.putAll(src.map);
    return this.getThis();
  }

  /**
   * Adds variables to the explicit entries of this configuration from a
   * dictionary.
   * <p>
   * The act of
   * <i>adding</i>
   * a variable consists of checking whether its name and value are valid
   * for this configuration, and if so, adding it to the explicit entries
   * of this configuration, replacing any existing entry for its name.
   * If the name or value is invalid, then there is no effect.
   * </p>
   *
   * @param src
   * the dictionary from which to add variables.
   * If
   * <code>src</code>
   * is a null reference, then it is implicitly adjusted to an immutable
   * empty dictionary.
   * Each variable is added as if by calling the
   * <code>{@link com.stealthsoftwareinc.sst.ConfigBase#add(CharSequence, CharSequence)}</code>
   * method.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable, then an unknown subset of variables
   * was added from
   * <code>src</code>.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * <li>
   * The structure and values of
   * <code>src</code>.
   * </li>
   * <li>
   * The underlying sequences of all keys and values in
   * <code>src</code>.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are true
   * while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not modified.
   * </li>
   * <li>
   * The explicit entries of this configuration are not accessed.
   * </li>
   * <li>
   * The structure and values of
   * <code>src</code>
   * are not modified.
   * </li>
   * <li>
   * The underlying sequences of all keys and values in
   * <code>src</code>
   * are not modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T add(
    final Dictionary<? extends CharSequence, ? extends CharSequence> src
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return this.getThis();
    }
    final Enumeration<? extends CharSequence> keys = src.keys();
    while (keys.hasMoreElements()) {
      final CharSequence key = keys.nextElement();
      final CharSequence value = src.get(key);
      add(key, value);
    }
    return this.getThis();
  }

  /**
   * Adds variables to the explicit entries of this configuration from a
   * map.
   * <p>
   * The act of
   * <i>adding</i>
   * a variable consists of checking whether its name and value are valid
   * for this configuration, and if so, adding it to the explicit entries
   * of this configuration, replacing any existing entry for its name.
   * If the name or value is invalid, then there is no effect.
   * </p>
   *
   * @param src
   * the map from which to add variables.
   * If
   * <code>src</code>
   * is a null reference, then it is implicitly adjusted to an immutable
   * empty map.
   * Each variable is added as if by calling the
   * <code>{@link com.stealthsoftwareinc.sst.ConfigBase#add(CharSequence, CharSequence)}</code>
   * method.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable, then an unknown subset of variables
   * was added from
   * <code>src</code>.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * <li>
   * The structure and values of
   * <code>src</code>.
   * </li>
   * <li>
   * The underlying sequences of all keys and values in
   * <code>src</code>.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are true
   * while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not modified.
   * </li>
   * <li>
   * The explicit entries of this configuration are not accessed.
   * </li>
   * <li>
   * The structure and values of
   * <code>src</code>
   * are not modified.
   * </li>
   * <li>
   * The underlying sequences of all keys and values in
   * <code>src</code>
   * are not modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T add(
    final Map<? extends CharSequence, ? extends CharSequence> src
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return this.getThis();
    }
    for (final Map.Entry<? extends CharSequence, ? extends CharSequence> entry : src.entrySet()) {
      add(entry.getKey(), entry.getValue());
    }
    return this.getThis();
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final Reader src
  ) throws
    IOException
  {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return this.getThis();
    }
    final Properties properties = new Properties();
    properties.load(src);
    final Enumeration keys = properties.keys();
    while (keys.hasMoreElements()) {
      final Object key = keys.nextElement();
      if (key instanceof CharSequence) {
        final Object value = properties.get(key);
        if (value instanceof CharSequence) {
          add((CharSequence)key, (CharSequence)value);
        }
      }
    }
    return this.getThis();
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final CharSequence src
  ) throws
    IOException
  {
    if (src == null) {
      return addProperties(DEFAULT_PROPERTIES_FILE);
    }
    return addProperties(new File(src.toString()));
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final CharSequence src,
    final CharSequence charsetName
  ) throws
    IOException
  {
    if (src == null) {
      return addProperties(DEFAULT_PROPERTIES_FILE, charsetName);
    }
    return addProperties(new File(src.toString()), charsetName);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final CharSequence src,
    final Charset charset
  ) throws
    IOException
  {
    if (src == null) {
      return addProperties(DEFAULT_PROPERTIES_FILE, charset);
    }
    return addProperties(new File(src.toString()), charset);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final CharSequence src,
    final CharsetDecoder decoder
  ) throws
    IOException
  {
    if (src == null) {
      return addProperties(DEFAULT_PROPERTIES_FILE, decoder);
    }
    return addProperties(new File(src.toString()), decoder);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final File src
  ) throws
    IOException
  {
    return addProperties(src, DEFAULT_CHARSET);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final File src,
    final CharSequence charsetName
  ) throws
    IOException
  {
    if (charsetName == null) {
      return addProperties(src, DEFAULT_CHARSET);
    }
    return addProperties(src, Charset.forName(charsetName.toString()));
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final File src,
    final Charset charset
  ) throws
    IOException
  {
    if (charset == null) {
      return addProperties(src, DEFAULT_CHARSET);
    }
    return addProperties(src, charset.newDecoder());
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final File src,
    final CharsetDecoder decoder
  ) throws
    IOException
  {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return addProperties(DEFAULT_PROPERTIES_FILE, decoder);
    }
    final FileInputStream stream = new FileInputStream(src);
    try {
      return addProperties(stream, decoder);
    } finally {
      try {
        stream.close();
      } catch (final Exception e) {
      }
    }
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final InputStream src
  ) throws
    IOException
  {
    return addProperties(src, DEFAULT_CHARSET);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final InputStream src,
    final CharSequence charsetName
  ) throws
    IOException
  {
    if (charsetName == null) {
      return addProperties(src, DEFAULT_CHARSET);
    }
    return addProperties(src, Charset.forName(charsetName.toString()));
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final InputStream src,
    final Charset charset
  ) throws
    IOException
  {
    if (charset == null) {
      return addProperties(src, DEFAULT_CHARSET);
    }
    return addProperties(src, charset.newDecoder());
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addProperties(
    final InputStream src,
    final CharsetDecoder decoder
  ) throws
    IOException
  {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return this.getThis();
    }
    if (decoder == null) {
      return addProperties(src, DEFAULT_CHARSET);
    }
    final InputStreamReader reader = new InputStreamReader(src, decoder);
    try {
      return addProperties(reader);
    } finally {
      try {
        reader.close();
      } catch (final Exception e) {
      }
    }
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @examples
   * none
   */

  public final T addPropertiesText(
    final CharSequence src
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (src == null) {
      return this.getThis();
    }
    final StringReader reader = new StringReader(src.toString());
    try {
      return addProperties(reader);
    } catch (final IOException e) {
      throw (InternalErrorStatus)
        new InternalErrorStatus(
          "StringReader threw an IOException"
        ).initCause(e)
      ;
    } finally {
      try {
        reader.close();
      } catch (final Exception e) {
      }
    }
  }

  /**
   * Removes all explicit entries.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable, then an unknown subset of its
   * explicit entries was removed.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are true
   * while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not modified.
   * </li>
   * <li>
   * The explicit entries of this configuration are not accessed.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T clear(
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    this.entries.clear();
    return this.getThis();
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final String get(
    final CharSequence name
  ) {
    return this.get(name, true);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final String get(
    final CharSequence name,
    final boolean resolve
  ) {
    if (this.isView()) {
      return this.viewee.get(name, resolve);
    }
    if (name == null) {
      return this.get("", resolve);
    }
    if (resolve) {
      return this.get(this.resolve(name), false);
    }
    final String value = this.entries.get(name.toString());
    if (value != null) {
      return value;
    }
    for (final ConfigPartition partition : this.partitions) {
      if (partition.namePredicate.test(name)) {
        return partition.defaultValue;
      }
    }
    return null;
  }

  /**
   * Gets an immutable configuration with no explicit entries.
   *
   * @return
   * an immutable configuration with no explicit entries
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
   * @inheritancenotes
   * <ol>
   * <li>
   * If you are implementing an abstract subclass of this class, then you
   * should not override this method.
   * </li>
   * <li>
   * If you are implementing a non-abstract subclass of this class, then
   * your subclass should be final and you should override this method to
   * return an immutable configuration with no explicit entries and with
   * the type of your subclass.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public final class Config
   *extends ConfigBase&lt;Config&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *public static final Config NULL_CONFIG;
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *static {
   *  // ...
   *  NULL_CONFIG = new Config().makeImmutable();
   *  // ...
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *&#64;Override
   *protected final Config getNull(
   *) {
   *  return Config.NULL_CONFIG;
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * </ol>
   *
   * @examples
   * none
   */

  protected abstract T getNull(
  );

  /**
   * Gets this configuration with the proper type.
   *
   * @return
   * this configuration with the proper type
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
   * @inheritancenotes
   * <ol>
   * <li>
   * If you are implementing an abstract subclass of this class, then you
   * should not override this method.
   * </li>
   * <li>
   * If you are implementing a non-abstract subclass of this class, then
   * your subclass should be final and you should override this method to
   * return the configuration with the type of your subclass.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public final class Config
   *extends ConfigBase&lt;Config&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *&#64;Override
   *protected final Config getThis(
   *) {
   *  return this;
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * </ol>
   *
   * @examples
   * none
   */

  protected abstract T getThis(
  );

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isExplicit(
    final CharSequence name
  ) {
    return this.isExplicit(name, true);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isExplicit(
    final CharSequence name,
    final boolean resolve
  ) {
    if (this.isView()) {
      return this.viewee.isExplicit(name, resolve);
    }
    if (name == null) {
      return this.isExplicit("", resolve);
    }
    if (resolve) {
      return this.isExplicit(this.resolve(name), false);
    }
    return this.entries.containsKey(name.toString());
  }

  /**
   * Determines whether this configuration is immutable.
   *
   * @return
   * <code>true</code>
   * if this configuration is immutable, or
   * <code>false</code>
   * if not
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * the mutability state of this configuration
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if this configuration is not mutable or its mutability state is not
   * modified while this method is being called
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isImmutable(
  ) {
    return !this.isMutable() && !this.isView();
  }

  /**
   * Determines whether this configuration is mutable.
   *
   * @return
   * <code>true</code>
   * if this configuration is mutable, or
   * <code>false</code>
   * if not
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * the mutability state of this configuration
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if this configuration is not mutable or its mutability state is not
   * modified while this method is being called
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isMutable(
  ) {
    return this.mutable;
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isValid(
    final CharSequence name
  ) {
    return this.isValid(name, true);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isValid(
    final CharSequence name,
    final CharSequence value
  ) {
    return this.isValid(name, true, value);
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isValid(
    final CharSequence name,
    final boolean resolve
  ) {
    if (this.isView()) {
      return this.viewee.isValid(name, resolve);
    }
    if (name == null) {
      return this.isValid("", resolve);
    }
    if (resolve) {
      return this.isValid(this.resolve(name), false);
    }
    for (final ConfigPartition partition : this.partitions) {
      if (partition.namePredicate.test(name)) {
        return true;
      }
    }
    return false;
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isValid(
    final CharSequence name,
    final boolean resolve,
    final CharSequence value
  ) {
    if (this.isView()) {
      return this.viewee.isValid(name, resolve, value);
    }
    if (name == null) {
      return this.isValid("", resolve, value);
    }
    if (value == null) {
      return this.isValid(name, resolve, "");
    }
    if (resolve) {
      return this.isValid(this.resolve(name), false, value);
    }
    for (final ConfigPartition partition : this.partitions) {
      if (partition.namePredicate.test(name)) {
        return partition.valuePredicate.test(value);
      }
    }
    return false;
  }

  /**
   * Determines whether this configuration is an unmodifiable view.
   *
   * @return
   * <code>true</code>
   * if this configuration is an unmodifiable view, or
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
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final boolean isView(
  ) {
    return this.viewee != null;
  }

  /**
   * Makes this configuration immutable.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable, then it is unknown whether it
   * became immutable.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are true
   * while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not accessed.
   * </li>
   * <li>
   * The explicit entries of this configuration are not modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T makeImmutable(
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    this.mutable = false;
    return this.getThis();
  }

  /**
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T remove(
    final CharSequence name
  ) {
    return this.remove(name, true);
  }

  /**
   * Removes an explicit entry.
   *
   * @param name
   * a possibly unresolved name of the explicit entry to remove.
   * If
   * <code>name</code>
   * is a null reference, then it is implicitly adjusted to an immutable
   * empty string.
   *
   * @return
   * this configuration
   *
   * @throws com.stealthsoftwareinc.sst.InvalidOperationStatus
   * if and only if this configuration is not mutable
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed.
   * If this configuration is mutable and contains an explicit entry for
   * <code>name</code>,
   * then it is unknown whether the explicit entry was removed.
   *
   * @accesses
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The mutability state of this configuration.
   * </li>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * <li>
   * The underlying sequence of
   * <code>name</code>.
   * </li>
   * </ol>
   *
   * @modifies
   * all of the following if this configuration is mutable:
   * <ol>
   * <li>
   * The explicit entries of this configuration.
   * </li>
   * </ol>
   *
   * @wellbehaved
   * if this configuration is not mutable or all of the following are true
   * while this method is being called:
   * <ol>
   * <li>
   * The mutability state of this configuration is not modified.
   * </li>
   * <li>
   * The explicit entries of this configuration are not accessed.
   * </li>
   * <li>
   * The underlying sequence of
   * <code>name</code>
   * is not modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T remove(
    final CharSequence name,
    final boolean resolve
  ) {
    if (!this.isMutable()) {
      throw (InvalidOperationStatus)
        new InvalidOperationStatus(
          "this configuration is not mutable"
        ).initCause(null)
      ;
    }
    if (name == null) {
      return this.remove("", resolve);
    }
    if (resolve) {
      return this.remove(this.resolve(name), false);
    }
    this.entries.remove(name.toString());
    return this.getThis();
  }

  /**
   * Resolves a variable name.
   *
   * @param name
   * the name to resolve.
   * If
   * <code>name</code>
   * is a null reference, then it is implicitly adjusted to an immutable
   * empty string.
   *
   * @return
   * the resolved name
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * the underlying sequence of
   * <code>name</code>
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if the underlying sequence of
   * <code>name</code>
   * is not modified while this method is being called
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final String resolve(
    final CharSequence name
  ) {
    if (name == null) {
      return resolve("");
    }
    final HashSet<String> seen = new HashSet<String>();
    String x = name.toString();
    seen.add(x);
    walk:
    for (;;) {
      for (final ConfigMapper alias : aliases) {
        if (alias.test(x)) {
          x = alias.map(x);
          if (seen.add(x)) {
            continue walk;
          }
          return x;
        }
      }
      return x;
    }
  }

  /**
   * Gets (the viewee of) this configuration if it is immutable, or a new
   * immutable copy that includes the explicit entries if not.
   *
   * @return
   * (the viewee of) this configuration if it is immutable, or a new
   * immutable copy that includes the explicit entries if not
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * all of the following if (the viewee of) this configuration is
   * mutable:
   * <ol>
   * <li>
   * The mutability state of (the viewee of) this configuration.
   * </li>
   * <li>
   * The explicit entries of (the viewee of) this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if (the viewee of) this configuration is immutable or all of the
   * following are true while this method is being called:
   * <ol>
   * <li>
   * The mutability state of (the viewee of) this configuration is not
   * modified.
   * </li>
   * <li>
   * The explicit entries of (the viewee of) this configuration are not
   * modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
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
   * Gets a new immutable copy of (the viewee of) this configuration that
   * includes the explicit entries.
   *
   * @return
   * a new immutable copy of (the viewee of) this configuration that
   * includes the explicit entries
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * all of the following if (the viewee of) this configuration is
   * mutable:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if (the viewee of) this configuration is immutable or all of the
   * following are true while this method is being called:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration are not
   * modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T toImmutableCopy(
  ) {
    return this.toImmutableCopy(false);
  }

  /**
   * Gets a new immutable copy of (the viewee of) this configuration that
   * includes or excludes the explicit entries.
   *
   * @param empty
   * <code>false</code>
   * to include the explicit entries, or
   * <code>true</code>
   * to exclude the explicit entries
   *
   * @return
   * a new immutable copy of (the viewee of) this configuration that
   * includes or excludes the explicit entries as indicated by
   * <code>empty</code>
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * all of the following if (the viewee of) this configuration is mutable
   * and
   * <code>empty</code>
   * is
   * <code>false</code>:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if (the viewee of) this configuration is immutable or
   * <code>empty</code>
   * is
   * <code>true</code>
   * or all of the following are true while this method is being called:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration are not
   * modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T toImmutableCopy(
    final boolean empty
  ) {
    return this.toMutable(empty).makeImmutable();
  }

  /**
   * Gets a new mutable copy of (the viewee of) this configuration that
   * includes the explicit entries.
   *
   * @return
   * a new mutable copy of (the viewee of) this configuration that
   * includes the explicit entries
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * all of the following if (the viewee of) this configuration is
   * mutable:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if (the viewee of) this configuration is immutable or all of the
   * following are true while this method is being called:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration are not
   * modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * none
   *
   * @examples
   * none
   */

  public final T toMutable(
  ) {
    return this.toMutable(false);
  }

  /**
   * Gets a new mutable copy of (the viewee of) this configuration that
   * includes or excludes the explicit entries.
   *
   * @param empty
   * <code>false</code>
   * to include the explicit entries, or
   * <code>true</code>
   * to exclude the explicit entries
   *
   * @return
   * a new mutable copy of (the viewee of) this configuration that
   * includes or excludes the explicit entries as indicated by
   * <code>empty</code>
   *
   * @throws java.lang.Throwable
   * (or a subclass thereof)
   * if and only if the operation failed
   *
   * @accesses
   * all of the following if (the viewee of) this configuration is mutable
   * and
   * <code>empty</code>
   * is
   * <code>false</code>:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration.
   * </li>
   * </ol>
   *
   * @modifies
   * nothing
   *
   * @wellbehaved
   * if (the viewee of) this configuration is immutable or
   * <code>empty</code>
   * is
   * <code>true</code>
   * or all of the following are true while this method is being called:
   * <ol>
   * <li>
   * The explicit entries of (the viewee of) this configuration are not
   * modified.
   * </li>
   * </ol>
   *
   * @available
   * always
   *
   * @inheritancenotes
   * <ol>
   * <li>
   * If you are implementing an abstract subclass of this class, then you
   * should not override this method.
   * </li>
   * <li>
   * If you are implementing a non-abstract subclass of this class, then
   * your subclass should be final and you should override this method to
   * use your constructor that wraps the
   * <code>{@link com.stealthsoftwareinc.sst.ConfigBase#ConfigBase(ConfigBase, boolean, boolean)}</code>
   * constructor.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public final class Config
   *extends ConfigBase&lt;Config&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *&#64;Override
   *public final Config toMutable(
   *  final boolean empty
   *) {
   *  return new Config(this, true, empty);
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * </ol>
   *
   * @examples
   * none
   */

  public abstract T toMutable(
    boolean empty
  );

  /**
   * Gets this configuration if it is an unmodifiable view, or a new
   * unmodifiable view of this configuration if not.
   *
   * @return
   * this configuration if it is an unmodifiable view, or a new
   * unmodifiable view of this configuration if not
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
   * @inheritancenotes
   * <ol>
   * <li>
   * If you are implementing an abstract subclass of this class, then you
   * should not override this method.
   * </li>
   * <li>
   * If you are implementing a non-abstract subclass of this class, then
   * your subclass should be final and you should override this method to
   * use your constructor that wraps the
   * <code>{@link com.stealthsoftwareinc.sst.ConfigBase#ConfigBase(ConfigBase, boolean, boolean)}</code>
   * constructor.
   * For example:
   *<!--code{.java}--><blockquote><pre>
   *public final class Config
   *extends ConfigBase&lt;Config&gt;
   *{
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *&#64;Override
   *public final Config toView(
   *) {
   *  if (this.isView()) {
   *    return this;
   *  }
   *  return new Config(this, false, false);
   *}
   *<b></b>
   *<b></b>// ...
   *<b></b>
   *}
   *</pre></blockquote>
   * </li>
   * </ol>
   *
   * @examples
   * none
   */

  public abstract T toView(
  );

}
