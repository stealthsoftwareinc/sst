/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.Args</code>
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

import com.stealthsoftwareinc.sst.AllocationImpossibleStatus;
import com.stealthsoftwareinc.sst.Memory;
import java.lang.String;

/* end_imports */

/**
 * Provides various static methods for working with command-line
 * arguments.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public final class Args
{

/**
 * Prevents objects of this class from being constructed.
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
 * @since SST&nbsp;0.1.0 (2016-05-11)
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

private Args(
) {
}

/**
 * Creates a copy of an array of strings with a null reference added to
 * the end.
 * <p>
 * An array of strings is called an
 * <i>argument vector</i>
 * if it contains one or more null references.
 * Any elements after the first null reference are usually considered to
 * be out of play.
 * This method can therefore be used to convert an array of strings that
 * is not already an argument vector to an argument vector with all
 * original elements in play.
 * </p>
 *
 * @param args
 * the array to copy.
 * If
 * <code>args</code>
 * is a null reference, then it is implicitly adjusted to a new empty
 * array.
 *
 * @return
 * a copy of
 * <code>args</code>
 * with a null reference added to the end
 *
 * @throws com.stealthsoftwareinc.sst.AllocationImpossibleStatus
 * if and only if
 * <code>args</code>
 * has
 * <code>{@link java.lang.Integer#MAX_VALUE}</code>
 * elements
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * the elements of
 * <code>args</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * are not modified while this method is being called
 *
 * @see com.stealthsoftwareinc.sst.Args#needNull(String[])
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @inheritancenotes
 * none
 *
 * @examples
 * <ol>
 * <li>
 * The
 * <code>{@link com.stealthsoftwareinc.sst.Args#needNull(String[])}</code>
 * and
 * <code>{@link com.stealthsoftwareinc.sst.Args#addNull(String[])}</code>
 * methods can be used in a
 * <code>main</code>
 * method to adjust the
 * <code>args</code>
 * array to an argument vector, as shown by the following code:
 *<!--code{.java}--><blockquote><pre>
 *public static void main(
 *  final String... args
 *) {
 *  if (Args.needNull(args)) {
 *    main(Args.addNull(args));
 *    return;
 *  }
 *  // ...
 *}
 *</pre></blockquote>
 * </li>
 * </ol>
 *
 * @notablechanges
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ul>
 * <li>
 * This method was changed to implicitly adjust
 * <code>args</code>
 * to a new empty array when it is a null reference instead of throwing
 * a
 * <code>{@link com.stealthsoftwareinc.sst.NullPointerStatus}</code>
 * exception.
 * </li>
 * <li>
 * This method was changed to throw an
 * <code>{@link com.stealthsoftwareinc.sst.AllocationImpossibleStatus}</code>
 * exception instead of an
 * <code>{@link com.stealthsoftwareinc.sst.OutOfRangeStatus}</code>
 * exception when
 * <code>args</code>
 * has
 * <code>{@link java.lang.Integer#MAX_VALUE}</code>
 * elements.
 * </li>
 * </ul>
 */

public static final String[] addNull(
  final String[] args
) {
  if (args == null) {
    return new String[] {null};
  }
  if (args.length == Integer.MAX_VALUE) {
    throw (AllocationImpossibleStatus)
      new AllocationImpossibleStatus(
        "args has Integer.MAX_VALUE elements"
      ).initCause(null)
    ;
  }
  final String[] a = new String[args.length + 1];
  Memory.copy(args, 0, a, 0, args.length);
  a[args.length] = null;
  return a;
}

/**
 * Truncates a string that is a valued long option fragment with any
 * name to contain only the name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String cropLongOption(
  final String arg
) {
  return cropLongOption(arg, null);
}

/**
 * Truncates a string that is a valued long option fragment with any
 * name or a specific name to contain only the name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String cropLongOption(
  final String arg,
  final String opt
) {
  if (isValuedLongOption(arg, opt)) {
    return arg.substring(0, arg.indexOf('='));
  }
  return arg;
}

/**
 * Truncates a string that is a valued option fragment with any name to
 * contain only the name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String cropOption(
  final String arg
) {
  return cropOption(arg, null);
}

/**
 * Truncates a string that is a valued option fragment with any name or
 * a specific name to contain only the name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String cropOption(
  final String arg,
  final String opt
) {
  if (Args.isLongOption(arg, opt)) {
    return Args.cropLongOption(arg, opt);
  }
  return Args.cropShortOption(arg, opt);
}

/**
 * Truncates a string that is a valued short option fragment with any
 * name to contain only the name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String cropShortOption(
  final String arg
) {
  return cropShortOption(arg, null);
}

/**
 * Truncates a string that is a valued short option fragment with any
 * name or a specific name to contain only the name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String cropShortOption(
  final String arg,
  final String opt
) {
  if (isValuedShortOption(arg, opt)) {
    return arg.substring(0, 2);
  }
  return arg;
}

/**
 *
 * @param args
 *
 * @param argi
 *
 * @return
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not accessed while this method is being called
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

public static final OptionPair forbidOptionValue(
  final String[] args,
  final int argi
) {
  return forbidOptionValue(args, argi, null);
}

/**
 *
 * @param args
 *
 * @param argi
 *
 * @return
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not accessed while this method is being called
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

public static final OptionPair forbidOptionValue(
  final String[] args,
  final int argi,
  final String opt
) {
  Args.throwIfNeedNull(args, argi);
  final String name = cropOption(args[argi], opt);
  final String value = getOptionValue(args, argi, opt);
  final boolean valued = isValuedOption(args[argi], opt);
  final boolean combined = valued && Args.isShortOption(name);
  if (combined) {
    args[argi] = "-" + value;
  }
  return new OptionPair(
    argi + (name != null && !valued ? 1 : 0),
    name,
    combined ? null : (valued ? value : null)
  );
}

/**
 * Locates the ultimate value of a long option fragment with any name in
 * an argument vector.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String getLongOptionValue(
  final String[] args,
  final int argi
) {
  return getLongOptionValue(args, argi, null);
}

/**
 * Locates the ultimate value of a long option fragment with any name or
 * a specific name in an argument vector.
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * (priority&nbsp;5)
 * if and only if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String getLongOptionValue(
  final String[] args,
  final int argi,
  final String opt
) {
  Args.throwIfNeedNull(args, argi);
  if (isValuedLongOption(args[argi], opt)) {
    return args[argi].substring(args[argi].indexOf('=') + 1);
  }
  if (isUnvaluedLongOption(args[argi], opt)) {
    return args[argi + 1];
  }
  return null;
}

/**
 * Locates the ultimate value of an option fragment with any name in an
 * argument vector.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String getOptionValue(
  final String[] args,
  final int argi
) {
  return getOptionValue(args, argi, null);
}

/**
 * Locates the ultimate value of an option fragment with any name or a
 * specific name in an argument vector.
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * (priority&nbsp;5)
 * if and only if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String getOptionValue(
  final String[] args,
  final int argi,
  final String opt
) {
  Args.throwIfNeedNull(args, argi);
  {
    final String val = getLongOptionValue(args, argi, opt);
    if (val != null) {
      return val;
    }
  }
  {
    final String val = getShortOptionValue(args, argi, opt);
    if (val != null) {
      return val;
    }
  }
  return null;
}

/**
 * Locates the ultimate value of a short option fragment with any name
 * in an argument vector.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String getShortOptionValue(
  final String[] args,
  final int argi
) {
  return getShortOptionValue(args, argi, null);
}

/**
 * Locates the ultimate value of a short option fragment with any name
 * or a specific name in an argument vector.
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * (priority&nbsp;5)
 * if and only if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final String getShortOptionValue(
  final String[] args,
  final int argi,
  final String opt
) {
  Args.throwIfNeedNull(args, argi);
  if (isValuedShortOption(args[argi], opt)) {
    return args[argi].substring(2);
  }
  if (isUnvaluedShortOption(args[argi], opt)) {
    return args[argi + 1];
  }
  return null;
}

/**
 * Determines whether a string is a long option fragment with any name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isLongOption(
  final CharSequence arg
) {
  return Args.isLongOption(arg, (CharSequence)null);
}

/**
 * Determines whether a string is a long option fragment with any name
 * or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ol>
 * <li>
 * This method was changed to accept
 * <code>{@link java.lang.CharSequence}</code>
 * arguments instead of
 * <code>{@link java.lang.String}</code>
 * arguments.
 * </li>
 * </ol>
 */

public static final boolean isLongOption(
  final CharSequence arg,
  final CharSequence opt
) {
  if (arg == null) {
    return false;
  }
  if (arg.length() < 2) {
    return false;
  }
  if (arg.charAt(0) != '-') {
    return false;
  }
  if (arg.charAt(1) != '-') {
    return false;
  }
  if (opt == null) {
    return true;
  }
  if (opt.length() < 2) {
    return false;
  }
  if (opt.charAt(0) != '-') {
    return false;
  }
  if (opt.charAt(1) != '-') {
    return false;
  }
  {
    int i;
    for (i = 2; i != arg.length() && arg.charAt(i) != '='; ++i) {
      if (i == opt.length()) {
        return false;
      }
      if (arg.charAt(i) != opt.charAt(i)) {
        return false;
      }
    }
    if (i != opt.length() && opt.charAt(i) != '=') {
      return false;
    }
  }
  return true;
}

/**
 * Determines whether a string is a long option fragment with one of
 * several specific names.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isLongOption(
  final CharSequence arg,
  final CharSequence... opts
) {
  if (opts != null) {
    int i;
    for (i = 0; i != opts.length; ++i) {
      if (opts[i] == null) {
        return false;
      }
      if (Args.isLongOption(arg, opts[i])) {
        return true;
      }
    }
  }
  return false;
}

/**
 * Determines whether a string is an option fragment with any name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isOption(
  final CharSequence arg
) {
  return isOption(arg, (CharSequence)null);
}

/**
 * Determines whether a string is an option fragment with any name or a
 * specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ol>
 * <li>
 * This method was changed to accept
 * <code>{@link java.lang.CharSequence}</code>
 * arguments instead of
 * <code>{@link java.lang.String}</code>
 * arguments.
 * </li>
 * </ol>
 */

public static final boolean isOption(
  final CharSequence arg,
  final CharSequence opt
) {
  if (Args.isLongOption(arg, opt)) {
    return true;
  }
  if (Args.isShortOption(arg, opt)) {
    return true;
  }
  return false;
}

/**
 * Determines whether a string is an option fragment with one of several
 * specific names.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isOption(
  final CharSequence arg,
  final CharSequence... opts
) {
  if (opts != null) {
    int i;
    for (i = 0; i != opts.length; ++i) {
      if (opts[i] == null) {
        return false;
      }
      if (isOption(arg, opts[i])) {
        return true;
      }
    }
  }
  return false;
}

/**
 * Determines whether a string is a short option fragment with any name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isShortOption(
  final CharSequence arg
) {
  return Args.isShortOption(arg, (CharSequence)null);
}

/**
 * Determines whether a string is a short option fragment with any name
 * or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ol>
 * <li>
 * This method was changed to accept
 * <code>{@link java.lang.CharSequence}</code>
 * arguments instead of
 * <code>{@link java.lang.String}</code>
 * arguments.
 * </li>
 * </ol>
 */

public static final boolean isShortOption(
  final CharSequence arg,
  final CharSequence opt
) {
  if (arg == null) {
    return false;
  }
  if (arg.length() < 2) {
    return false;
  }
  if (arg.charAt(0) != '-') {
    return false;
  }
  if (arg.charAt(1) == '-') {
    return false;
  }
  if (opt == null) {
    return true;
  }
  if (opt.length() < 2) {
    return false;
  }
  if (opt.charAt(0) != '-') {
    return false;
  }
  if (opt.charAt(1) == '-') {
    return false;
  }
  if (arg.charAt(1) != opt.charAt(1)) {
    return false;
  }
  return true;
}

/**
 * Determines whether a string is a short option fragment with one of
 * several specific names.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isShortOption(
  final CharSequence arg,
  final CharSequence... opts
) {
  if (opts != null) {
    int i;
    for (i = 0; i != opts.length; ++i) {
      if (opts[i] == null) {
        return false;
      }
      if (Args.isShortOption(arg, opts[i])) {
        return true;
      }
    }
  }
  return false;
}

/**
 * Determines whether a string is an unvalued long option fragment with
 * any name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isUnvaluedLongOption(
  final String arg
) {
  return isUnvaluedLongOption(arg, null);
}

/**
 * Determines whether a string is an unvalued long option fragment with
 * any name or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isUnvaluedLongOption(
  final String arg,
  final String opt
) {
  if (!Args.isLongOption(arg, opt)) {
    return false;
  }
  if (isValuedLongOption(arg, opt)) {
    return false;
  }
  return true;
}

/**
 * Determines whether a string is an unvalued option fragment with any
 * name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isUnvaluedOption(
  final String arg
) {
  return isUnvaluedOption(arg, null);
}

/**
 * Determines whether a string is an unvalued option fragment with any
 * name or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isUnvaluedOption(
  final String arg,
  final String opt
) {
  if (isUnvaluedLongOption(arg, opt)) {
    return true;
  }
  if (isUnvaluedShortOption(arg, opt)) {
    return true;
  }
  return false;
}

/**
 * Determines whether a string is an unvalued short option fragment with
 * any name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isUnvaluedShortOption(
  final String arg
) {
  return isUnvaluedShortOption(arg, null);
}

/**
 * Determines whether a string is an unvalued short option fragment with
 * any name or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isUnvaluedShortOption(
  final String arg,
  final String opt
) {
  if (!Args.isShortOption(arg, opt)) {
    return false;
  }
  if (isValuedShortOption(arg, opt)) {
    return false;
  }
  return true;
}

/**
 * Determines whether a string is a valued long option fragment with any
 * name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isValuedLongOption(
  final String arg
) {
  return isValuedLongOption(arg, null);
}

/**
 * Determines whether a string is a valued long option fragment with any
 * name or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isValuedLongOption(
  final String arg,
  final String opt
) {
  if (!Args.isLongOption(arg, opt)) {
    return false;
  }
  if (arg.indexOf('=') == -1) {
    return false;
  }
  return true;
}

/**
 * Determines whether a string is a valued option fragment with any
 * name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isValuedOption(
  final String arg
) {
  return isValuedOption(arg, null);
}

/**
 * Determines whether a string is a valued option fragment with any name
 * or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isValuedOption(
  final String arg,
  final String opt
) {
  if (isValuedLongOption(arg, opt)) {
    return true;
  }
  if (isValuedShortOption(arg, opt)) {
    return true;
  }
  return false;
}

/**
 * Determines whether a string is a valued short option fragment with
 * any name.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isValuedShortOption(
  final String arg
) {
  return isValuedShortOption(arg, null);
}

/**
 * Determines whether a string is a valued short option fragment with
 * any name or a specific name.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean isValuedShortOption(
  final String arg,
  final String opt
) {
  if (!Args.isShortOption(arg, opt)) {
    return false;
  }
  if (arg.length() == 2) {
    return false;
  }
  return true;
}

/**
 * Determines whether an array of strings does not contain a null
 * reference.
 * <p>
 * An array of strings is called an
 * <i>argument vector</i>
 * if it contains one or more null references.
 * This method therefore determines whether an array of strings is not
 * an argument vector.
 * </p>
 *
 * @param args
 * the array to check.
 * If
 * <code>args</code>
 * is a null reference, then it is implicitly adjusted to a new empty
 * array.
 *
 * @return
 * <code>false</code>
 * if
 * <code>args</code>
 * contains a null reference, or
 * <code>true</code>
 * if not
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 * <code>args</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if
 * <code>args</code>
 * is not modified while this method is being called
 *
 * @available
 * always
 *
 * @see com.stealthsoftwareinc.sst.Args#addNull(String[])
 * @see com.stealthsoftwareinc.sst.Args#needNull(String[], int)
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * <ol>
 * <li>
 * The
 * <code>{@link com.stealthsoftwareinc.sst.Args#needNull(String[])}</code>
 * and
 * <code>{@link com.stealthsoftwareinc.sst.Args#addNull(String[])}</code>
 * methods can be used in a
 * <code>main</code>
 * method to adjust the
 * <code>args</code>
 * array to an argument vector, as shown by the following code:
 *<!--code{.java}--><blockquote><pre>
 *public static void main(
 *  final String... args
 *) {
 *  if (Args.needNull(args)) {
 *    main(Args.addNull(args));
 *    return;
 *  }
 *  // ...
 *}
 *</pre></blockquote>
 * </li>
 * </ol>
 *
 * @notablechanges
 * none
 */

public static final boolean needNull(
  final String[] args
) {
  if (args == null) {
    return true;
  }
  if (args.length == 0) {
    return true;
  }
  return needNull(args, 0);
}

/**
 * Determines whether an array of strings does not contain a null
 * reference at or beyond a particular index.
 *
 * @param args
 * the array to check
 *
 * @param argi
 * the index at which to start checking
 *
 * @return
 * <code>false</code>
 * if
 * <code>args</code>
 * contains a null reference at or beyond index
 * <code>argi</code>,
 * or
 * <code>true</code>
 * if not
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not modified while this method is being called
 *
 * @available
 * always
 *
 * @see com.stealthsoftwareinc.sst.Args#needNull(String[])
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean needNull(
  final String[] args,
  final int argi
) {
  if (args == null) {
    throw (NullPointerStatus)
      new NullPointerStatus(
        "args is a null reference"
      ).initCause(null)
    ;
  }
  if (args.length == 0) {
    throw (ZeroArraySizeStatus)
      new ZeroArraySizeStatus(
        "args has zero elements"
      ).initCause(null)
    ;
  }
  if (argi < 0) {
    throw (NegativeArrayIndexStatus)
      new NegativeArrayIndexStatus(
        "argi is negative"
      ).initCause(null)
    ;
  }
  if (argi >= args.length) {
    throw (OversizeArrayIndexStatus)
      new OversizeArrayIndexStatus(
        "argi is not smaller than args.length"
      ).initCause(null)
    ;
  }
  /*
   * The most common location for a null reference is the last element,
   * so we'll check for that first. This is the normal structure of an
   * argument vector in practice.
   */
  if (args[args.length - 1] == null) {
    return false;
  }
  /*
   * The next most common location for a null reference is the element
   * at index argi + 1, so it suffices to check the remaining elements
   * in increasing order. This is the structure of an argument vector
   * after pulling a long option with a required but missing value at
   * the end of the argument vector.
   */
  for (int i = argi; i != args.length - 1; ++i) {
    if (args[i] == null) {
      return false;
    }
  }
  return true;
}

/**
 *
 * @param args
 *
 * @param argi
 *
 * @return
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not modified while this method is being called
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

public static final OptionPair permitOptionValue(
  final String[] args,
  final int argi
) {
  return permitOptionValue(args, argi, null);
}

/**
 *
 * @param args
 *
 * @param argi
 *
 * @return
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not modified while this method is being called
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

public static final OptionPair permitOptionValue(
  final String[] args,
  final int argi,
  final String opt
) {
  Args.throwIfNeedNull(args, argi);
  final String name = cropOption(args[argi], opt);
  final String value = getOptionValue(args, argi, opt);
  final boolean valued = isValuedOption(args[argi], opt);
  return new OptionPair(
    argi + (name != null ? 1 : 0),
    name,
    valued ? value : null
  );
}

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

public static final boolean pullLongOption(
  final String[] args,
  final int argi
) {
  return pullLongOption(args, argi, null, null);
}

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

public static final boolean pullLongOption(
  final String[] args,
  final int argi,
  final String[] otrv
) {
  return pullLongOption(args, argi, otrv, null);
}

/**
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * if
 * <code>args</code>
 * has zero elements
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean pullLongOption(
  final String[] args,
  final int argi,
  final String[] otrv,
  final String[] otp
) {
  Args.throwIfNeedNull(args, argi);
  {
    int i = argi;
    for (;;) {
      if (args[i] == null) {
        return false;
      }
      if (otp == null) {
        if (Args.isLongOption(args[i])) {
          break;
        }
      } else {
        {
          int j;
          for (j = 0; j != otp.length && otp[j] != null; ++j) {
            if (Args.isLongOption(args[i], otp[j])) {
              break;
            }
          }
          if (j != otp.length && otp[j] != null) {
            break;
          }
        }
        if (otrv != null) {
          int j;
          for (j = 0; j != otrv.length && otrv[j] != null; ++j) {
            if (isUnvaluedOption(args[i], otrv[j])) {
              break;
            }
          }
          if (j != otrv.length && otrv[j] != null) {
            ++i;
            if (args[i] == null) {
              return false;
            }
          }
        }
      }
      ++i;
    }
    if (i != argi) {
      boolean pullTwoArguments = false;
      if (otrv != null) {
        int j;
        for (j = 0; j != otrv.length && otrv[j] != null; ++j) {
          if (isUnvaluedLongOption(args[i], otrv[j])) {
            pullTwoArguments = true;
            break;
          }
        }
      }
      if (pullTwoArguments) {
        final String a0 = args[i + 0];
        final String a1 = args[i + 1];
        Memory.copy(args, argi, args, argi + 2, i - argi);
        args[argi + 0] = a0;
        args[argi + 1] = a1;
      } else {
        final String a0 = args[i + 0];
        Memory.copy(args, argi, args, argi + 1, i - argi);
        args[argi + 0] = a0;
      }
    }
  }
  return true;
}

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

public static final boolean pullOption(
  final String[] args,
  final int argi
) {
  return pullOption(args, argi, null, null);
}

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

public static final boolean pullOption(
  final String[] args,
  final int argi,
  final String[] otrv
) {
  return pullOption(args, argi, otrv, null);
}

/**
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * if
 * <code>args</code>
 * has zero elements
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean pullOption(
  final String[] args,
  final int argi,
  final String[] otrv,
  final String[] otp
) {
  Args.throwIfNeedNull(args, argi);
  {
    int i = argi;
    for (;;) {
      if (args[i] == null) {
        return false;
      }
      if (otp == null) {
        if (isOption(args[i])) {
          break;
        }
      } else {
        {
          int j;
          for (j = 0; j != otp.length && otp[j] != null; ++j) {
            if (isOption(args[i], otp[j])) {
              break;
            }
          }
          if (j != otp.length && otp[j] != null) {
            break;
          }
        }
        if (otrv != null) {
          int j;
          for (j = 0; j != otrv.length && otrv[j] != null; ++j) {
            if (isUnvaluedOption(args[i], otrv[j])) {
              break;
            }
          }
          if (j != otrv.length && otrv[j] != null) {
            ++i;
            if (args[i] == null) {
              return false;
            }
          }
        }
      }
      ++i;
    }
    if (i != argi) {
      boolean pullTwoArguments = false;
      if (otrv != null) {
        int j;
        for (j = 0; j != otrv.length && otrv[j] != null; ++j) {
          if (isUnvaluedOption(args[i], otrv[j])) {
            pullTwoArguments = true;
            break;
          }
        }
      }
      if (pullTwoArguments) {
        final String a0 = args[i + 0];
        final String a1 = args[i + 1];
        Memory.copy(args, argi, args, argi + 2, i - argi);
        args[argi + 0] = a0;
        args[argi + 1] = a1;
      } else {
        final String a0 = args[i + 0];
        Memory.copy(args, argi, args, argi + 1, i - argi);
        args[argi + 0] = a0;
      }
    }
  }
  return true;
}

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

public static final boolean pullShortOption(
  final String[] args,
  final int argi
) {
  return pullShortOption(args, argi, null, null);
}

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

public static final boolean pullShortOption(
  final String[] args,
  final int argi,
  final String[] otrv
) {
  return pullShortOption(args, argi, otrv, null);
}

/**
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * if
 * <code>args</code>
 * has zero elements
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final boolean pullShortOption(
  final String[] args,
  final int argi,
  final String[] otrv,
  final String[] otp
) {
  Args.throwIfNeedNull(args, argi);
  {
    int i = argi;
    for (;;) {
      if (args[i] == null) {
        return false;
      }
      if (otp == null) {
        if (Args.isShortOption(args[i])) {
          break;
        }
      } else {
        {
          int j;
          for (j = 0; j != otp.length && otp[j] != null; ++j) {
            if (Args.isShortOption(args[i], otp[j])) {
              break;
            }
          }
          if (j != otp.length && otp[j] != null) {
            break;
          }
        }
        if (otrv != null) {
          int j;
          for (j = 0; j != otrv.length && otrv[j] != null; ++j) {
            if (isUnvaluedOption(args[i], otrv[j])) {
              break;
            }
          }
          if (j != otrv.length && otrv[j] != null) {
            ++i;
            if (args[i] == null) {
              return false;
            }
          }
        }
      }
      ++i;
    }
    if (i != argi) {
      boolean pullTwoArguments = false;
      if (otrv != null) {
        int j;
        for (j = 0; j != otrv.length && otrv[j] != null; ++j) {
          if (isUnvaluedShortOption(args[i], otrv[j])) {
            pullTwoArguments = true;
            break;
          }
        }
      }
      if (pullTwoArguments) {
        final String a0 = args[i + 0];
        final String a1 = args[i + 1];
        Memory.copy(args, argi, args, argi + 2, i - argi);
        args[argi + 0] = a0;
        args[argi + 1] = a1;
      } else {
        final String a0 = args[i + 0];
        Memory.copy(args, argi, args, argi + 1, i - argi);
        args[argi + 0] = a0;
      }
    }
  }
  return true;
}

/**
 *
 * @param args
 *
 * @param argi
 *
 * @return
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not modified while this method is being called
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

public static final OptionPair requireOptionValue(
  final String[] args,
  final int argi
) {
  return requireOptionValue(args, argi, null);
}

/**
 *
 * @param args
 *
 * @param argi
 *
 * @return
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not modified while this method is being called
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

public static final OptionPair requireOptionValue(
  final String[] args,
  final int argi,
  final String opt
) {
  Args.throwIfNeedNull(args, argi);
  final String name = cropOption(args[argi], opt);
  final String value = getOptionValue(args, argi, opt);
  final boolean unvalued = isUnvaluedOption(args[argi], opt);
  return new OptionPair(
    argi + (value != null ? 1 : 0) + (unvalued ? 1 : 0),
    name,
    value
  );
}

/**
 *
 * @param arg
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
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

public static final String snipLongOption(
  final CharSequence arg
) {
  return Args.snipLongOption(arg, null);
}

/**
 *
 * @param arg
 *
 * @param opt
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
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

public static final String snipLongOption(
  final CharSequence arg,
  final CharSequence opt
) {
  if (Args.isLongOption(arg, opt)) {
    return arg.toString().substring(2);
  }
  if (arg == null) {
    return null;
  }
  return arg.toString();
}

/**
 *
 * @param arg
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
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

public static final String snipOption(
  final CharSequence arg
) {
  return Args.snipOption(arg, null);
}

/**
 *
 * @param arg
 *
 * @param opt
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
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

public static final String snipOption(
  final CharSequence arg,
  final CharSequence opt
) {
  if (Args.isLongOption(arg, opt)) {
    return Args.snipLongOption(arg, opt);
  }
  return Args.snipShortOption(arg, opt);
}

/**
 *
 * @param arg
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
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

public static final String snipShortOption(
  final CharSequence arg
) {
  return Args.snipShortOption(arg, null);
}

/**
 *
 * @param arg
 *
 * @param opt
 *
 * @return
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @accesses
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
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

public static final String snipShortOption(
  final CharSequence arg,
  final CharSequence opt
) {
  if (Args.isShortOption(arg, opt)) {
    return arg.toString().substring(1);
  }
  if (arg == null) {
    return null;
  }
  return arg.toString();
}

/**
 * Throws an exception if an array of strings does not contain a null
 * reference at or beyond a particular index.
 *
 * @param args
 * the array to check
 *
 * @param argi
 * the index at which to start checking
 *
 * @throws com.stealthsoftwareinc.sst.MissingArraySentinelStatus
 * (priority&nbsp;5)
 * if and only if
 * <code>args</code>
 * does not contain a null reference at or beyond index
 * <code>argi</code>
 *
 * @throws com.stealthsoftwareinc.sst.NegativeArrayIndexStatus
 * (priority&nbsp;3)
 * if and only if
 * <code>argi</code>
 * is negative
 *
 * @throws com.stealthsoftwareinc.sst.NullPointerStatus
 * (priority&nbsp;1)
 * if and only if
 * <code>args</code>
 * is a null reference
 *
 * @throws com.stealthsoftwareinc.sst.OversizeArrayIndexStatus
 * (priority&nbsp;4)
 * if and only if
 * <code>argi</code>
 * is not smaller than
 * <code>args.length</code>
 *
 * @throws java.lang.Throwable
 * (or a subclass thereof)
 * if and only if the operation failed
 *
 * @throws com.stealthsoftwareinc.sst.ZeroArraySizeStatus
 * (priority&nbsp;2)
 * if and only if
 * <code>args</code>
 * has zero elements
 *
 * @accesses
 * the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 *
 * @modifies
 * nothing
 *
 * @wellbehaved
 * if the elements of
 * <code>args</code>
 * at or beyond index
 * <code>argi</code>
 * are not modified while this method is being called
 *
 * @available
 * always
 *
 * @see com.stealthsoftwareinc.sst.Args#needNull(String[], int)
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public static final void throwIfNeedNull(
  final String[] args,
  final int argi
) {
  if (needNull(args, argi)) {
    throw (MissingArraySentinelStatus)
      new MissingArraySentinelStatus(
        "args does not contain a null reference at or beyond index " +
        "argi"
      ).initCause(null)
    ;
  }
}

}
