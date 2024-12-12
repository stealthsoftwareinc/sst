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

import java.io.IOException;
import java.util.Locale;
import java.util.concurrent.ConcurrentHashMap;

/**
 * The JdbcSubprotocol enum indicates the RDBMS which is in use, and provides
 * helper functions for writing queries for this RDBMS.
 */

public enum JdbcSubprotocol {

  /**
   * The MYSQL subprotocol is intended to be compatible with MySQL 5.7,
   * MySQL 8.0, and MariaDB 10.x.
   *
   * Conforms to the requirements set out in the MySQL and MariaDB
   * documentation.
   * {@link https://dev.mysql.com/doc/refman/5.7/en/identifiers.html }
   * {@link https://dev.mysql.com/doc/refman/8.0/en/identifiers.html }
   * {@link https://mariadb.com/kb/en/library/identifier-names/ }
   */
  MYSQL {

    @Override
    public final boolean hasDefaultPort() {
      return true;
    }

    @Override
    public final int getDefaultPort() {
      return 3306;
    }

    @Override
    public final String getQuoteChar() {
      return "`";
    }

    @Override
    public final Appendable escapeIdentifier(final Appendable dst,
                                             final CharSequence src)
        throws IOException {
      if (dst == null) {
        return escapeIdentifier(new StringBuilder(), src);
      }
      if (src == null) {
        return escapeIdentifier(dst, "");
      }
      for (int i = 0; i != src.length(); ++i) {
        final char c = src.charAt(i);
        if (c == '`') {
          dst.append("``");
        } else {
          dst.append(c);
        }
      }
      return dst;
    }

  },

  /**
   * The ORACLE JdbcSubprotocol handles identifiers for Oracle's Database of
   * their same name. For MySQL, which is also an Oracle product use
   * @see MYSQL. This JdbcSubprotocol conforms to Oracle's own guidelines
   * set here:
   *
   * {@link https://docs.oracle.com/database/121/SQLRF/sql_elements008.htm }
   *
   * Note, that Oracle does not allow quotes within their quoted identifiers,
   * and that quoted identifiers are CASE SENSITIVE, while unquoted
   * identifiers are CASE INSENSITIVE, and Oracle recommends not to mix these.
   */
  ORACLE {

    @Override
    public final boolean hasDefaultPort() {
      return true;
    }

    @Override
    public final int getDefaultPort() {
      return 1521;
    }

    @Override
    public final String getQuoteChar() {
      return "\"";
    }

    @Override
    public final Appendable escapeIdentifier(final Appendable dst,
                                             final CharSequence src)
        throws IOException {
      if (dst == null) {
        return escapeIdentifier(new StringBuilder(), src);
      }
      if (src == null) {
        return escapeIdentifier(dst, "");
      }
      for (int i = 0; i != src.length(); ++i) {
        final char c = src.charAt(i);
        if (c == '"') {
          throw new RuntimeException("Invalid Oracle identifier: \""
                                     + JavaLex.escape(src) + "\"");
        } else {
          dst.append(c);
        }
      }
      return dst;
    }

  },

  /**
   * The POSTGRESQL subprotocol is for the PostgreSQL system. It should conform
   * to the Identifier section (4.1.1) in
   * {@link https://www.postgresql.org/docs/9.1/sql-syntax-lexical.html }
   */
  POSTGRESQL {

    @Override
    public final boolean hasDefaultPort() {
      return true;
    }

    @Override
    public final int getDefaultPort() {
      return 5432;
    }

    @Override
    public final String getQuoteChar() {
      return "\"";
    }

    @Override
    public final Appendable escapeIdentifier(final Appendable dst,
                                             final CharSequence src)
        throws IOException {
      if (dst == null) {
        return escapeIdentifier(new StringBuilder(), src);
      }
      if (src == null) {
        return escapeIdentifier(dst, "");
      }
      for (int i = 0; i != src.length(); ++i) {
        final char c = src.charAt(i);
        if (c == '"') {
          dst.append("\"\"");
        } else {
          dst.append(c);
        }
      }
      return dst;
    }

  },

  //--------------------------------------------------------------------
  // SQLITE
  //--------------------------------------------------------------------

  SQLITE {

    @Override
    public final boolean hasDefaultPort() {
      return false;
    }

    @Override
    public final int getDefaultPort() {
      throw new UnsupportedOperationException(
          "JdbcSubprotocol.SQLITE.getDefaultPort() is unsupported "
              + "because SQLite does not use networking.",
          null);
    }

    @Override
    public final String getQuoteChar() {
      return "\"";
    }

    @Override
    public final Appendable escapeIdentifier(final Appendable dst,
                                             final CharSequence src)
        throws IOException {
      if (!SST_NDEBUG) {
        try {
          SST_ASSERT(dst != null);
          SST_ASSERT(src != null);
        } catch (final Throwable e) {
          SST_ASSERT(e);
        }
      }
      final int n = src.length();
      for (int i = 0; i < n; ++i) {
        final char c = src.charAt(i);
        if (c == '"') {
          dst.append("\"\"");
        } else {
          dst.append(c);
        }
      }
      return dst;
    }

  },

  //--------------------------------------------------------------------

  SQLSERVER {

    @Override
    public final boolean hasDefaultPort() {
      return true;
    }

    @Override
    public final int getDefaultPort() {
      return 1433;
    }

    @Override
    public final String getQuoteChar() {
      return "\"";
    }

    @Override
    public final Appendable escapeIdentifier(final Appendable dst,
                                             final CharSequence src)
        throws IOException {
      if (dst == null) {
        return escapeIdentifier(new StringBuilder(), src);
      }
      if (src == null) {
        return escapeIdentifier(dst, "");
      }
      for (int i = 0; i != src.length(); ++i) {
        final char c = src.charAt(i);
        if (c == '"') {
          dst.append("\"\"");
        } else {
          dst.append(c);
        }
      }
      return dst;
    }
  };

  //--------------------------------------------------------------------

  private static final ConcurrentHashMap<String, JdbcSubprotocol>
      stringMap_ = new ConcurrentHashMap<String, JdbcSubprotocol>();

  static {
    for (final JdbcSubprotocol value : JdbcSubprotocol.values()) {
      {
        final JdbcSubprotocol collision =
            stringMap_.put(value.toString(), value);
        assert collision == null;
      }
    }
  }

  private final String string_;

  private JdbcSubprotocol() {
    string_ = name().toLowerCase(Locale.ROOT);
  }

  public abstract boolean hasDefaultPort();
  public abstract int getDefaultPort();

  /**
   * Returns the character(s) that quotes an identifier.
   *
   * @return The quotation character(s).
   */

  public abstract String getQuoteChar();

  /**
   * Escapes an identifier for quoting but does not append or prepend
   * the actual quotes.
   *
   * When escaping null or an empty string, the empty string is used, and
   * when the destination is null, then a new StringBuilder is created.
   *
   * @param dst The StringBuilder into which the identifier is returned.
   * @param src The identifier being escaped.
   * @return the dst param for reuse.
   */

  public abstract Appendable escapeIdentifier(Appendable dst,
                                              CharSequence src)
      throws IOException;

  public final StringBuilder escapeIdentifier(final StringBuilder dst,
                                              final CharSequence src) {
    try {
      return (StringBuilder)escapeIdentifier((Appendable)dst, src);
    } catch (final IOException e) {
      throw new InternalErrorStatus();
    }
  }

  public final String escapeIdentifier(final CharSequence src) {
    return escapeIdentifier(new StringBuilder(), src).toString();
  }

  /**
   * Quote an identifier and then append it to the given Appendable object.
   *
   * When quoting a qualified object (e.g.
   * {@code table_name.column_name }), quote the qualifier's identifier,
   * and the object's identifier separately.
   *
   * {@code subProto.quoteIdentifier(appendable, "table_name").append(".");
   *   subProto.quoteIdentifier(appendable, "column_name"); }
   *
   * When quoting null or an empty string, empty quotes are used, and when the
   * destination is null, then a new StringBuilder is created.
   *
   * @param dest The Appendable buffer into which the identifier is returned.
   * @param src The identifier being quoted.
   * @return the dest param for reuse.
   *
   * @throws IOException if the underlying Appendable throws.
   */

  public final Appendable quoteIdentifier(final Appendable dst,
                                          final CharSequence src)
      throws IOException {
    if (dst == null) {
      return quoteIdentifier(new StringBuilder(), src);
    }
    if (src == null) {
      return quoteIdentifier(dst, "");
    }
    dst.append(getQuoteChar());
    escapeIdentifier(dst, src);
    dst.append(getQuoteChar());
    return dst;
  }

  public final StringBuilder quoteIdentifier(final StringBuilder dst,
                                             final CharSequence src) {
    try {
      return (StringBuilder)quoteIdentifier((Appendable)dst, src);
    } catch (final IOException e) {
      throw new InternalErrorStatus();
    }
  }

  public final String quoteIdentifier(final CharSequence src) {
    return quoteIdentifier(new StringBuilder(), src).toString();
  }

  //--------------------------------------------------------------------
  // String conversions
  //--------------------------------------------------------------------

  @Override
  public final String toString() {
    return string_;
  }

  public static final JdbcSubprotocol
  fromString(final CharSequence src) {
    SST_ASSERT(src != null);
    final String srcString = src.toString();
    final JdbcSubprotocol dst = stringMap_.get(srcString);
    if (dst == null) {
      throw new EnumConstantNotPresentException(JdbcSubprotocol.class,
                                                srcString);
    }
    return dst;
  }

  //--------------------------------------------------------------------
  // JSON conversions
  //--------------------------------------------------------------------

  public final String toJson() {
    return toString();
  }

  private static final CreateFromJson<JdbcSubprotocol>
      CREATE_FROM_JSON = new CreateFromJson<JdbcSubprotocol>() {
        @Override
        public final JdbcSubprotocol createFromJson(final Object src) {
          try {
            return fromString(Json.getAs(src, (String)null));
          } catch (final JsonException e) {
            throw e;
          } catch (final Throwable e) {
            throw new JsonException(e);
          }
        }
      };

  public static final CreateFromJson<JdbcSubprotocol> fromJson() {
    return CREATE_FROM_JSON;
  }

  //--------------------------------------------------------------------
}
