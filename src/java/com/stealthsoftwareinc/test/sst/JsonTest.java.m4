changequote(`{|', `|}')
ifdef({|make_rules|}, {||}, {|{|
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

import static org.junit.jupiter.api.Assertions.*;

import com.stealthsoftwareinc.sst.Json;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.TreeMap;
import java.util.LinkedList;
import java.util.List;
import org.junit.jupiter.api.*;

public final class JsonTest {

  //--------------------------------------------------------------------

  // clang-format off
  |}

  pushdef({|f|}, {|{|

    @Test
    public final void test$3$2() {
      final List<$2> expected = Arrays.asList(
          new $2[] {$2.MIN_VALUE, ($1)-1, ($1)0, ($1)1, $2.MAX_VALUE});
      final $3<String> src = new $3<String>();
      for (final $2 x : expected) {
        src.add(x.toString());
      }
      $3<$2> actual = new $3<$2>();
      actual.add(($1)0);
      actual = Json.getAs(src, actual, actual.get(0));
      assertEquals(actual, expected);
    }

  |}|})

  pushdef({|g|}, {|
    f({|byte|}, {|Byte|}, {|$1|})
    f({|short|}, {|Short|}, {|$1|})
    f({|int|}, {|Integer|}, {|$1|})
    f({|long|}, {|Long|}, {|$1|})
  |})

  g({|ArrayList|})
  g({|LinkedList|})

  popdef({|g|})
  popdef({|f|})

  {|
  // clang-format on

  //--------------------------------------------------------------------

  @Test
  public final void testDump1() {
    assertEquals("null", Json.dump(null));
    assertEquals("false", Json.dump(Boolean.valueOf(false)));
    assertEquals("true", Json.dump(Boolean.valueOf(true)));
    assertEquals("\"-1\"", Json.dump(Byte.valueOf((byte)-1)));
    assertEquals("\"0\"", Json.dump(Byte.valueOf((byte)0)));
    assertEquals("\"1\"", Json.dump(Byte.valueOf((byte)1)));
    assertEquals("\"-1\"", Json.dump(Short.valueOf((short)-1)));
    assertEquals("\"0\"", Json.dump(Short.valueOf((short)0)));
    assertEquals("\"1\"", Json.dump(Short.valueOf((short)1)));
    assertEquals("\"-1\"", Json.dump(Integer.valueOf(-1)));
    assertEquals("\"0\"", Json.dump(Integer.valueOf(0)));
    assertEquals("\"1\"", Json.dump(Integer.valueOf(1)));
    assertEquals("\"-1\"", Json.dump(Long.valueOf(-1)));
    assertEquals("\"0\"", Json.dump(Long.valueOf(0)));
    assertEquals("\"1\"", Json.dump(Long.valueOf(1)));
    assertEquals("[]", Json.dump(Arrays.asList(new Object[] {})));
    assertEquals("[null]",
                 Json.dump(Arrays.asList(new Object[] {null})));
    assertEquals("[null,null]",
                 Json.dump(Arrays.asList(new Object[] {null, null})));
    assertEquals("{}", Json.dump(new TreeMap<String, Object>()));
    assertEquals("{\"x\":null}",
                 Json.dump(new TreeMap<String, Object>() {
                   { put("x", null); }
                 }));
  }

  //--------------------------------------------------------------------
}

|}|})
