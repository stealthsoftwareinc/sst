/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.ConfigPartition</code>
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

import com.stealthsoftwareinc.sst.ConfigPredicate;
import com.stealthsoftwareinc.sst.InvalidArgumentStatus;
import java.lang.CharSequence;
import java.lang.String;

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

public final class ConfigPartition
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

public static final String DEFAULT_DEFAULT_VALUE;

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

public static final ConfigPredicate DEFAULT_NAME_PREDICATE;

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

public static final ConfigPredicate DEFAULT_VALUE_PREDICATE;

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

public final String defaultValue;

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

public final ConfigPredicate namePredicate;

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

public final ConfigPredicate valuePredicate;

static {
  DEFAULT_DEFAULT_VALUE = "";
  DEFAULT_NAME_PREDICATE =
    new ConfigPredicate() {
      @Override
      public final boolean test(
        final CharSequence input
      ) {
        return true;
      }
    }
  ;
  DEFAULT_VALUE_PREDICATE =
    new ConfigPredicate() {
      @Override
      public final boolean test(
        final CharSequence input
      ) {
        return true;
      }
    }
  ;
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

public ConfigPartition(
) {
  this(
    ConfigPartition.DEFAULT_NAME_PREDICATE,
    ConfigPartition.DEFAULT_VALUE_PREDICATE,
    ConfigPartition.DEFAULT_DEFAULT_VALUE
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

public ConfigPartition(
  final CharSequence defaultValue
) {
  this(
    ConfigPartition.DEFAULT_NAME_PREDICATE,
    ConfigPartition.DEFAULT_VALUE_PREDICATE,
    defaultValue
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

public ConfigPartition(
  final ConfigPredicate namePredicate
) {
  this(
    namePredicate,
    ConfigPartition.DEFAULT_VALUE_PREDICATE,
    ConfigPartition.DEFAULT_DEFAULT_VALUE
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

public ConfigPartition(
  final ConfigPredicate namePredicate,
  final CharSequence defaultValue
) {
  this(
    namePredicate,
    ConfigPartition.DEFAULT_VALUE_PREDICATE,
    defaultValue
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

public ConfigPartition(
  final ConfigPredicate namePredicate,
  final ConfigPredicate valuePredicate
) {
  this(
    namePredicate,
    valuePredicate,
    ConfigPartition.DEFAULT_DEFAULT_VALUE
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

public ConfigPartition(
  final ConfigPredicate namePredicate,
  final ConfigPredicate valuePredicate,
  final CharSequence defaultValue
) {
  if (namePredicate == null) {
    this.namePredicate = ConfigPartition.DEFAULT_NAME_PREDICATE;
  } else {
    this.namePredicate = namePredicate;
  }
  if (valuePredicate == null) {
    this.valuePredicate = ConfigPartition.DEFAULT_VALUE_PREDICATE;
  } else {
    this.valuePredicate = valuePredicate;
  }
  if (defaultValue == null) {
    this.defaultValue = ConfigPartition.DEFAULT_DEFAULT_VALUE;
  } else {
    this.defaultValue = defaultValue.toString();
  }
  if (!this.valuePredicate.test(this.defaultValue)) {
    throw (InvalidArgumentStatus)
      new InvalidArgumentStatus(
        "defaultValue does not satisfy valuePredicate"
      ).initCause(null)
    ;
  }
}

}
