/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import java.io.IOException;
import java.util.Locale;

/* end_imports */

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
    public StringBuilder escapeIdentifier(StringBuilder sb, CharSequence id) {
      if(sb == null) { sb = new StringBuilder(); }
      if(id == null) { id = ""; }
      int startLen = sb.length();
      sb.append(id);
      return StringBuilderUtil.replaceAllFrom(sb, "`", "``", startLen);
    }

    @Override
    public String getQuoteChar() { return "`"; }
  },

  /**
   * The POSTGRESQL subprotocol is for the PostgreSQL system. It should conform
   * to the Identifier section (4.1.1) in
   * {@link https://www.postgresql.org/docs/9.1/sql-syntax-lexical.html }
   */
  POSTGRESQL {
    @Override
    public StringBuilder escapeIdentifier(StringBuilder sb, CharSequence id) {
      if(sb == null) { sb = new StringBuilder(); }
      if(id == null) { id = ""; }
      int startLen = sb.length();
      sb.append(id);
      return StringBuilderUtil.replaceAllFrom(sb, "\"", "\"\"", startLen);
    }
  },

  SQLSERVER {

    @Override
    public final String getQuoteChar(
    ) {
      return "\"";
    }

    @Override
    public final StringBuilder escapeIdentifier(
      final StringBuilder dst,
      final CharSequence src
    ) {
      throw new NotImplementedStatus();
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
    public StringBuilder escapeIdentifier(StringBuilder sb, CharSequence id) {
      if(id == null) { id = ""; }
      if(sb == null) { sb = new StringBuilder(); }
      int startLen = sb.length();
      sb.append(id);
      if(sb.indexOf("\"", startLen) >= 0) {
        throw new RuntimeException(String
          .format("ORACLE cannot handle quotes (\") in identifier \"%s\"",
          id));
      }
      else { return sb; }
    }
  };

  /**
   * Escape quotes in an identifier so that it may be later quoted.
   *
   * When escaping null or an empty string, the empty string is returned.
   *
   * @param id The identifier being escaped.
   * @return The escaped identifier.
   */
  public String escapeIdentifier(CharSequence id) {
    return this.escapeIdentifier(new StringBuilder(), id).toString();
  }

  /**
   * Quote an identifier and immediately return it.
   *
   * When quoting a qualified object (e.g.
   * {@code table_name.column_name }), quote the qualifier's identifier,
   * and the object's identifier separately.
   *
   * {@code subProto.quoteIdentifier("table_name") + "." + 
   *   subProto.quoteIdentifier("column_name") }
   *
   * When quoting null or an empty string, empty quotes are returned.
   *
   * @param id The identifier being quoted.
   * @return The identifier's value as quoted for this JdbcSubprotocol.
   */
  public String quoteIdentifier(CharSequence id) {
    return this.quoteIdentifier(new StringBuilder(), id).toString();
  }

  /**
   * Returns the character(s) that normally quotes an identifier.
   * Typically, but not always this is the double quote character (").
   *
   * @return The quotation character(s).
   */
  public String getQuoteChar() { return "\""; }

  /**
   * Escape an identifier to prepare it to be quoted, and then append it to
   * the given Appendable object.
   *
   * When escaping null or an empty string, a the empty string is used, and
   * when the destination is null, then a new StringBuilder is created.
   *
   * @param dest The Appendable buffer into which the identifier is returned.
   * @param src The identifier being escaped.
   * @return the dest param for reuse.
   *
   * @throws IOException if the underlying Appendable throws.
   */
  public Appendable escapeIdentifier(Appendable dest, CharSequence src)
    throws IOException {
    StringBuilder escape = this.escapeIdentifier(new StringBuilder(), src);
    if(dest == null) { return escape; } else { return dest.append(escape); }
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
  public Appendable quoteIdentifier(Appendable dest, CharSequence src)
    throws IOException {
    StringBuilder quote = this.quoteIdentifier(new StringBuilder(), src);
    if(dest == null) { return quote; } else { return dest.append(quote); }
  }

  /**
   * Escape an identifier to prepare it for quoting, and then append it to
   * the given StringBuilder object.
   *
   * When escaping null or an empty string, the empty string is used, and
   * when the destination is null, then a new StringBuilder is created.
   *
   * @param dest The StringBuilder into which the identifier is returned.
   * @param src The identifier being escaped.
   * @return the dest param for reuse.
   */
  public abstract StringBuilder escapeIdentifier(StringBuilder dest,
    CharSequence src);

  /**
   * Quote an identifier and then append it to the given StringBuilder object.
   *
   * When quoting a qualified object (e.g.
   * {@code table_name.column_name }), quote the qualifier's identifier,
   * and the object's identifier separately.
   *
   * {@code subProto.quoteIdentifier(stringbuilder, "table_name").append(".");
   *   subProto.quoteIdentifier(stringbuilder, "column_name"); }
   *
   * When quoting null or an empty string, empty quotes are used, and when the
   * destination is null, then a new StringBuilder is created.
   *
   * @param dest The StringBuilder into which the identifier is returned.
   * @param src The identifier being quoted.
   * @return the dest param for reuse.
   */
  public StringBuilder quoteIdentifier(StringBuilder dest, CharSequence src) {
    if(dest == null) { dest = new StringBuilder(); }
    dest.append(this.getQuoteChar());
    this.escapeIdentifier(dest, src);
    dest.append(this.getQuoteChar());
    return dest;
  }

  public static final JdbcSubprotocol fromString(
    final CharSequence s
  ) {
    if (s == null) {
      return null;
    }
    switch (s.toString().toLowerCase(Locale.ROOT)) {
      case "mysql":      return MYSQL;
      case "oracle":     return ORACLE;
      case "postgresql": return POSTGRESQL;
      case "sqlserver":  return SQLSERVER;
    }
    return null;
  }

}
