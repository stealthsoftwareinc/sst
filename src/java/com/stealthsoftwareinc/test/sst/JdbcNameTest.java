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

package com.stealthsoftwareinc.test.sst;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.stealthsoftwareinc.sst.JdbcName;
import com.stealthsoftwareinc.sst.Json;
import com.stealthsoftwareinc.sst.JsonException;
import java.util.HashMap;
import java.util.Map;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.function.Executable;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

@Execution(ExecutionMode.CONCURRENT)
public final class JdbcNameTest {
  @Test
  public final void testStringSource() {
    final String src = "a";
    JdbcName dst = null;
    dst = Json.getAs(src, dst.fromJson());
    assertNotNull(dst.name());
    assertNotNull(dst.underlyingName());
    assertTrue(dst.name().equals(src));
    assertTrue(dst.underlyingName().equals(src));
  }

  @Test
  public final void testObjectSource1() {
    final Map<String, Object> src = new HashMap<String, Object>();
    src.put("name", "a");
    JdbcName dst = null;
    dst = Json.getAs(src, dst.fromJson());
    assertNotNull(dst.name());
    assertNotNull(dst.underlyingName());
    assertTrue(dst.name().equals("a"));
    assertTrue(dst.underlyingName().equals("a"));
  }

  @Test
  public final void testObjectSource2() {
    final Map<String, Object> src = new HashMap<String, Object>();
    src.put("underlying_name", "a");
    JdbcName dst = null;
    dst = Json.getAs(src, dst.fromJson());
    assertNotNull(dst.name());
    assertNotNull(dst.underlyingName());
    assertTrue(dst.name().equals("a"));
    assertTrue(dst.underlyingName().equals("a"));
  }

  @Test
  public final void testObjectSource3() {
    final Map<String, Object> src = new HashMap<String, Object>();
    src.put("name", "a");
    src.put("underlying_name", "b");
    JdbcName dst = null;
    dst = Json.getAs(src, dst.fromJson());
    assertNotNull(dst.name());
    assertNotNull(dst.underlyingName());
    assertTrue(dst.name().equals("a"));
    assertTrue(dst.underlyingName().equals("b"));
  }

  @Test
  public final void testExceptions1() {
    assertThrows(JsonException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        JdbcName dst = null;
        dst = Json.getAs(null, dst.fromJson());
      }
    });
  }

  @Test
  public final void testExceptions2() {
    assertThrows(JsonException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        JdbcName dst = null;
        dst = Json.getAs(0, dst.fromJson());
      }
    });
  }

  @Test
  public final void testExceptions3() {
    assertThrows(JsonException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        JdbcName dst = null;
        dst = Json.getAs((String)null, dst.fromJson());
      }
    });
  }

  @Test
  public final void testExceptions4() {
    assertThrows(JsonException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        final Map<String, Object> src = new HashMap<String, Object>();
        JdbcName dst = null;
        dst = Json.getAs(src, dst.fromJson());
      }
    });
  }

  @Test
  public final void testExceptions5() {
    assertThrows(JsonException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        final Map<String, Object> src = new HashMap<String, Object>();
        src.put("name", 0);
        JdbcName dst = null;
        dst = Json.getAs(src, dst.fromJson());
      }
    });
  }

  @Test
  public final void testExceptions6() {
    assertThrows(JsonException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        final Map<String, Object> src = new HashMap<String, Object>();
        src.put("name", "a");
        src.put("underlying_name", "b");
        src.put("foo", "c");
        JdbcName dst = null;
        dst = Json.getAs(src, dst.fromJson());
      }
    });
  }
}
