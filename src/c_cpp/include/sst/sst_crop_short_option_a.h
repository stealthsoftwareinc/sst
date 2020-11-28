/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_crop_short_option_a</code>
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

#ifndef SST_SST_CROP_SHORT_OPTION_A_H
#define SST_SST_CROP_SHORT_OPTION_A_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>

/* end_includes */

/**
 * Truncates a string that is a valued short option fragment with any
 * name or a specific name to contain only the name.
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
 *
 * @param arg
 * a pointer to a string to truncate.
 * If
 * <code>arg</code>
 * is not a null pointer and does not point to a string, or if another
 * thread modifies the string while this function is being called, then
 * the behavior is undefined.
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
 * @see <code>::sst_crop_short_option_w</code>
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

SST_PUBLIC_C_FUNCTION char * (sst_crop_short_option_a)(
  char *,
  char const *
);

#else

char * sst_crop_short_option_a(
  char * arg,
  char const * opt
);

#endif

#endif
