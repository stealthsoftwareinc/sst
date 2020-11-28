/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_crop_option_a</code>
 * function.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_CROP_OPTION_A_H
#define SST_SST_CROP_OPTION_A_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>

/* end_includes */

/**
 * Truncates a string that is a valued option fragment with any name or
 * a specific name to contain only the name.
 * <p>
 * A string is called a
 * <i>long option fragment</i>
 * if it begins with two
 * &ldquo;<code>-</code>&rdquo;&nbsp;characters.
 * The longest leading substring that does not contain an
 * &ldquo;<code>=</code>&rdquo;&nbsp;character
 * is called the
 * <i>name</i>
 * of the fragment.
 * The fragment is said to be
 * <i>valued</i>
 * if it contains an
 * &ldquo;<code>=</code>&rdquo;&nbsp;character,
 * or
 * <i>unvalued</i>
 * if not.
 * For example,
 * <code>-<b></b>-foo=bar</code>
 * and
 * <code>-<b></b>-foo</code>
 * are valued and unvalued long option fragments, respectively, and
 * <code>-<b></b>-foo</code>
 * is the name of both.
 * </p>
 * <p>
 * A string is called a
 * <i>short option fragment</i>
 * if it begins with one
 * &ldquo;<code>-</code>&rdquo;&nbsp;character
 * followed by one character except the
 * &ldquo;<code>-</code>&rdquo;&nbsp;character.
 * These two characters are called the
 * <i>name</i>
 * of the fragment.
 * The fragment is said to be
 * <i>valued</i>
 * if the name is followed by one or more characters, or
 * <i>unvalued</i>
 * if not.
 * For example,
 * <code>-xfoo</code>
 * and
 * <code>-x</code>
 * are valued and unvalued short option fragments, respectively, and
 * <code>-x</code>
 * is the name of both.
 * </p>
 * <p>
 * A string is called an
 * <i>option fragment</i>
 * if it is a long option fragment or a short option fragment.
 * Note that a string cannot be a long option fragment and a short
 * option fragment at the same time.
 * </p>
 *
 * @param arg
 * a pointer to a string to truncate.
 * If
 * <code>arg</code>
 * is not a null pointer and does not point to a string, or if another
 * thread modifies the string while this function is being called, then
 * the behavior is undefined.
 * If the string is a valued long option fragment and
 * <code>opt</code>
 * points to a string that is a long option fragment with the same name,
 * then this function sets the first
 * &ldquo;<code>=</code>&rdquo;&nbsp;character
 * of the string to a null character.
 * If the string is a valued short option fragment and
 * <code>opt</code>
 * points to a string that is a short option fragment with the same
 * name, then this function sets the third character of the string to a
 * null character.
 * This function never modifies the string in any other way.
 *
 * @param opt
 * the name to check for.
 * If
 * <code>opt</code>
 * is not a null pointer and does not point to a string, or if another
 * thread modifies the string while this function is being called, then
 * the behavior is undefined.
 * If
 * <code>opt</code>
 * is a null pointer and
 * <code>arg</code>
 * is not, then
 * <code>opt</code>
 * is implicitly adjusted to the value of
 * <code>arg</code>.
 * This function never modifies the string except incidentally through
 * the modification described for
 * <code>arg</code>
 * if the strings overlap and the intersection contains the modified
 * character.
 *
 * @return
 * the value of
 * <code>arg</code>
 *
 * @available
 * always
 *
 * @see <code>::sst_crop_option_w</code>
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION char * (sst_crop_option_a)(
  char *,
  char const *
);

#else

char * sst_crop_option_a(
  char * arg,
  char const * opt
);

#endif

#endif
