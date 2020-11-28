/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_get_short_option_value_a</code>
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

#ifndef SST_SST_GET_SHORT_OPTION_VALUE_A_H
#define SST_SST_GET_SHORT_OPTION_VALUE_A_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>

/* end_includes */

/**
 * Locates the ultimate value of a short option fragment with any name
 * or a specific name in an argument vector.
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
 * An array of pointers to characters is called an
 * <i>argument vector</i>
 * if it begins with zero or more elements that point to strings
 * followed by an element that is a null pointer.
 * If the first element points to a string that is a valued short option
 * fragment, then the trailing substring that consists of all characters
 * beyond the first two characters is called the
 * <i>ultimate value</i>
 * of the fragment.
 * If the first element points to a string that is an unvalued short
 * option fragment and the second element is not a null pointer, then
 * the string pointed to by the second element is called the
 * <i>ultimate value</i>
 * of the fragment.
 * If the first element points to a string that is an unvalued short
 * option fragment and the second element is a null pointer, then the
 * <i>ultimate value</i>
 * of the fragment is said to be
 * <i>absent</i>.
 * </p>
 *
 * @param argv
 * a pointer to the first element of an argument vector.
 * If
 * <code>argv</code>
 * is not a null pointer and does not point to the first element of an
 * argument vector, or if another thread modifies the vector or any of
 * its strings while this function is being called, then the behavior is
 * undefined.
 * This function never modifies the vector nor any of its strings.
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
 * <code>argv</code>
 * and
 * <code>argv[0]</code>
 * are not, then
 * <code>opt</code>
 * is implicitly adjusted to the value of
 * <code>argv[0]</code>.
 * This function never modifies the string.
 *
 * @return
 * <ul>
 * <li>
 * a pointer to the ultimate value of the short option fragment pointed
 * to by
 * <code>argv[0]</code>
 * if and only if
 * <code>argv</code>
 * is not a null pointer,
 * <code>argv[0]</code>
 * and
 * <code>opt</code>
 * point to strings that are short option fragments with the same name,
 * and the ultimate value of the
 * <code>argv[0]</code>
 * fragment is not absent
 * </li>
 * <li>
 * a null pointer if and only if
 * <code>argv</code>
 * is a null pointer,
 * <code>argv[0]</code>
 * is a null pointer,
 * <code>argv[0]</code>
 * or
 * <code>opt</code>
 * points to a string that is not a short option fragment, the fragments
 * have different names, or the ultimate value of the
 * <code>argv[0]</code>
 * fragment is absent
 * </li>
 * </ul>
 *
 * @available
 * always
 *
 * @see <code>::sst_get_short_option_value_w</code>
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

SST_PUBLIC_C_FUNCTION char * (sst_get_short_option_value_a)(
  char * const *,
  char const *
);

#else

char * sst_get_short_option_value_a(
  char * const * argv,
  char const * opt
);

#endif

#endif
