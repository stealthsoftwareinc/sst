/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

package com.stealthsoftwareinc.tests.sst;

import com.stealthsoftwareinc.sst.JdbcSubprotocol;

import java.io.StringWriter;
import java.io.IOException;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Note that as of 2019-10-10, this has only been tested against
 * each system's documentation, it has not been tested live against
 * any of these RDBMS systems.
 */
public class JdbcSubprotocolTest {

  @Test
  public void testMYSQL() {
    JdbcSubprotocol sp = JdbcSubprotocol.MYSQL;

    assertEquals("`", sp.getQuoteChar());

    assertEquals("abc", sp.escapeIdentifier("abc"));
    assertEquals("`abc`", sp.quoteIdentifier("abc"));

    assertEquals("ab\"c", sp.escapeIdentifier("ab\"c"));
    assertEquals("`ab\"c`", sp.quoteIdentifier("ab\"c"));

    assertEquals("ab``c", sp.escapeIdentifier("ab`c"));
    assertEquals("`ab``c`", sp.quoteIdentifier("ab`c"));

    assertEquals("``abc``", sp.escapeIdentifier("`abc`"));
    assertEquals("```abc```", sp.quoteIdentifier("`abc`"));

    assertEquals("\"abc\"", sp.escapeIdentifier("\"abc\""));
    assertEquals("`\"abc\"`", sp.quoteIdentifier("\"abc\""));

    assertEquals("", sp.escapeIdentifier(null));
    assertEquals("``", sp.quoteIdentifier(null));

    assertEquals("", sp.escapeIdentifier(""));
    assertEquals("``", sp.quoteIdentifier(""));
  }

  @Test
  public void testPOSTGRESQL() {
    JdbcSubprotocol sp = JdbcSubprotocol.POSTGRESQL;

    assertEquals("\"", sp.getQuoteChar());

    assertEquals("abc", sp.escapeIdentifier("abc"));
    assertEquals("\"abc\"", sp.quoteIdentifier("abc"));

    assertEquals("ab\"\"c", sp.escapeIdentifier("ab\"c"));
    assertEquals("\"ab\"\"c\"", sp.quoteIdentifier("ab\"c"));

    assertEquals("\"\"abc\"\"", sp.escapeIdentifier("\"abc\""));
    assertEquals("\"\"\"abc\"\"\"", sp.quoteIdentifier("\"abc\""));

    assertEquals("", sp.escapeIdentifier(null));
    assertEquals("\"\"", sp.quoteIdentifier(null));

    assertEquals("", sp.escapeIdentifier(""));
    assertEquals("\"\"", sp.quoteIdentifier(""));
  }

  @Test
  public void testORACLE() {
    JdbcSubprotocol sp = JdbcSubprotocol.ORACLE;

    assertEquals("\"", sp.getQuoteChar());

    assertEquals("abc", sp.escapeIdentifier("abc"));
    assertEquals("\"abc\"", sp.quoteIdentifier("abc"));

    assertThrows(RuntimeException.class, () -> {
      sp.escapeIdentifier("ab\"c");
    });
    assertThrows(RuntimeException.class, () -> {
      sp.quoteIdentifier("ab\"c");
    });

    assertThrows(RuntimeException.class, () -> {
      sp.escapeIdentifier("\"abc\"");
    });
    assertThrows(RuntimeException.class, () -> {
      sp.quoteIdentifier("\"abc\"");
    });

    assertEquals("", sp.escapeIdentifier(null));
    assertEquals("\"\"", sp.quoteIdentifier(null));

    assertEquals("", sp.escapeIdentifier(""));
    assertEquals("\"\"", sp.quoteIdentifier(""));
  }

  @Test
  public void testCommon() throws IOException {
    JdbcSubprotocol sp = JdbcSubprotocol.MYSQL;

    assertEquals("abc", sp.escapeIdentifier(new StringBuilder(), "abc")
      .toString());
    assertEquals("`abc`", sp.quoteIdentifier(new StringBuilder(), "abc")
      .toString());

    assertEquals("abc", sp.escapeIdentifier(null, "abc").toString());
    assertEquals("`abc`", sp.quoteIdentifier(null, "abc").toString());

    assertEquals("`abc`.`def`", sp.quoteIdentifier(
      sp.quoteIdentifier(new StringBuilder(), "abc").append("."), "def")
      .toString());
    assertEquals("`abc`.`def`", sp.quoteIdentifier(
      sp.quoteIdentifier(null, "abc").append("."), "def").toString());

    assertEquals("abc", sp.escapeIdentifier(new StringWriter(), "abc")
      .toString());
    assertEquals("`abc`", sp.quoteIdentifier(new StringWriter(), "abc")
      .toString());

    assertEquals("abc", sp.escapeIdentifier(null, "abc").toString());
    assertEquals("`abc`", sp.quoteIdentifier(null, "abc").toString());

    assertEquals("`abc`.`def`", sp.quoteIdentifier(
      sp.quoteIdentifier(new StringWriter(), "abc").append("."), "def")
      .toString());
    assertEquals("`abc`.`def`", sp.quoteIdentifier(
      sp.quoteIdentifier(null, "abc").append("."), "def").toString());

    StringBuilder sb = new StringBuilder("SELECT ");
    sp.quoteIdentifier(sb, "abc`def");
    sb.append(" FROM ");
    sb.append(sp.getQuoteChar());
    sp.escapeIdentifier(sb, "`ghi`");
    sb.append(sp.getQuoteChar());
    sb.append(";");
    assertEquals("SELECT `abc``def` FROM ```ghi```;", sb.toString());
  }
}
