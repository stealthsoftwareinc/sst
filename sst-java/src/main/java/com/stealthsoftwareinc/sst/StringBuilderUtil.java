/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

package com.stealthsoftwareinc.sst;

/**
 * The StringBuilderUtil static class is a collection of helper functions
 * to transform StringBuilders in ways that it does not natively support.
 */
public class StringBuilderUtil {
  
  /**
   * Replaces all occurences of a string with the given replacement, starting
   * at the given index, and going until the end. All parameters should not
   * be null, and the search key should not be an empty string.
   *
   * @param builder "this" StringBuilder.
   * @param search The string to search for.
   * @param repacement the string to replace instances of the search string.
   * @param from The index from which to start replacing.
   * @return "this" StringBuilder.
   */
  public static StringBuilder replaceAllFrom(StringBuilder builder,
    String search, String replacement, int from) {
    int idx = builder.indexOf(search, from);
    while(idx >= 0) {
      // StringBuilder handles differing lengths already.
      builder.replace(idx, idx + search.length(), replacement);
      idx = builder.indexOf(search, idx + replacement.length());
    }
    return builder;
  }

  /**
   * Replaces all occurences of a string with the given replacement.
   * All parameters should not be null, and the search key should not be an
   * empty string.
   *
   * This is a convenience for
   * {@code StringBuilderUtil.replaceAllFrom(builder, search, replacement, 0) }
   *
   * @param builder "this" StringBuilder.
   * @param search The string to search for.
   * @param repacement the string to replace instances of the search string.
   * @return "this" StringBuilder.
   */
  public static StringBuilder replaceAll(StringBuilder builder, String search,
    String replacement) {
      return StringBuilderUtil.replaceAllFrom(builder, search, replacement, 0);
  }
}
