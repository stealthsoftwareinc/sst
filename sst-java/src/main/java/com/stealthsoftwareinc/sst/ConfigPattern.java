/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ConfigPattern</code>
 * Java class.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import java.lang.String;
import java.util.regex.Pattern;

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

public final class ConfigPattern
implements
  ConfigMapper
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

public static final Pattern DEFAULT_PATTERN;

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

public static final String DEFAULT_REGEX;

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

public static final String DEFAULT_REPLACEMENT;

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

public final Pattern pattern;

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

public final String replacement;

static {
  DEFAULT_REGEX = "(?s:.)*";
  DEFAULT_PATTERN = Pattern.compile(DEFAULT_REGEX);
  DEFAULT_REPLACEMENT = "$0";
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public ConfigPattern(
) {
  this(DEFAULT_PATTERN, DEFAULT_REPLACEMENT);
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public ConfigPattern(
  final CharSequence regex
) {
  this(regex, DEFAULT_REPLACEMENT);
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public ConfigPattern(
  final CharSequence regex,
  final CharSequence replacement
) {
  this(
    regex == null ? DEFAULT_PATTERN : Pattern.compile(regex.toString()),
    replacement
  );
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public ConfigPattern(
  final Pattern pattern
) {
  this(pattern, DEFAULT_REPLACEMENT);
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public ConfigPattern(
  final Pattern pattern,
  final CharSequence replacement
) {
  if (pattern == null) {
    this.pattern = DEFAULT_PATTERN;
  } else {
    this.pattern = pattern;
  }
  if (replacement == null) {
    this.replacement = DEFAULT_REPLACEMENT;
  } else {
    this.replacement = replacement.toString();
  }
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

@Override
public final String map(
  final CharSequence input
) {
  if (input == null) {
    return map("");
  }
  return pattern.matcher(input).replaceFirst(replacement);
}

/**
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

@Override
public final boolean test(
  final CharSequence input
) {
  if (input == null) {
    return test("");
  }
  return pattern.matcher(input).matches();
}

}
