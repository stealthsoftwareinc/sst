/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_is_short_option_w</code>
 * function.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_IS_SHORT_OPTION_W_H
#define SST_SST_IS_SHORT_OPTION_W_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>
#include <stddef.h>

/* end_includes */

/**
 * Determines whether a string is a short option fragment with any name
 * or a specific name.
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
 * For example,
 * <code>-xfoo</code>
 * and
 * <code>-x</code>
 * are short option fragments, and
 * <code>-x</code>
 * is the name of both.
 * </p>
 *
 * @param arg
 * the string to check.
 * If
 * <code>arg</code>
 * is not a null pointer and does not point to a string, or if another
 * thread modifies the string while this function is being called, then
 * the behavior is undefined.
 * This function never modifies the string.
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
 * This function never modifies the string.
 *
 * @return
 * <ul>
 * <li>
 * <code>::SST_TRUE</code>
 * if and only if
 * <code>arg</code>
 * and
 * <code>opt</code>
 * point to strings that are short option fragments with the same name
 * </li>
 * <li>
 * <code>::SST_FALSE</code>
 * if and only if
 * <code>arg</code>
 * is a null pointer,
 * <code>arg</code>
 * or
 * <code>opt</code>
 * points to a string that is not a short option fragment, or the
 * fragments have different names
 * </li>
 * </ul>
 *
 * @modifies
 * nothing
 *
 * @available
 * always
 *
 * @see <code>::sst_is_short_option_a</code>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * <ol>
 * <li>
 * The following calls return
 * <code>::SST_TRUE</code>:
 * @code{.c}
 * sst_is_short_option_w(L"-x", NULL);
 * sst_is_short_option_w(L"-x", L"-x");
 * sst_is_short_option_w(L"-x", L"-xfoo");
 * sst_is_short_option_w(L"-xfoo", NULL);
 * sst_is_short_option_w(L"-xfoo", L"-x");
 * sst_is_short_option_w(L"-xfoo", L"-xfoo");
 * sst_is_short_option_w(L"-xfoo", L"-xbar");
 * @endcode
 * </li>
 * <li>
 * The following calls return
 * <code>::SST_FALSE</code>:
 * @code{.c}
 * sst_is_short_option_w(NULL, NULL);
 * sst_is_short_option_w(NULL, L"x");
 * sst_is_short_option_w(NULL, L"-x");
 * sst_is_short_option_w(NULL, L"-xfoo");
 * sst_is_short_option_w(L"x", NULL);
 * sst_is_short_option_w(L"x", L"x");
 * sst_is_short_option_w(L"x", L"-x");
 * sst_is_short_option_w(L"x", L"-xfoo");
 * sst_is_short_option_w(L"-x", L"x");
 * sst_is_short_option_w(L"-x", L"-y");
 * sst_is_short_option_w(L"-x", L"-yfoo");
 * sst_is_short_option_w(L"-xfoo", L"x");
 * sst_is_short_option_w(L"-xfoo", L"-y");
 * sst_is_short_option_w(L"-xfoo", L"-yfoo");
 * @endcode
 * </li>
 * </ol>
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION sst_bool (sst_is_short_option_w)(
  wchar_t const *,
  wchar_t const *
);

#else

sst_bool sst_is_short_option_w(
  wchar_t const * arg,
  wchar_t const * opt
);

#endif

#endif