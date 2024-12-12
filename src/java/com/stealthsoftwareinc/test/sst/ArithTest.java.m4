dnl#
dnl# Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
dnl#
dnl# Permission is hereby granted, free of charge, to any person
dnl# obtaining a copy of this software and associated documentation
dnl# files (the "Software"), to deal in the Software without
dnl# restriction, including without limitation the rights to use,
dnl# copy, modify, merge, publish, distribute, sublicense, and/or
dnl# sell copies of the Software, and to permit persons to whom the
dnl# Software is furnished to do so, subject to the following
dnl# conditions:
dnl#
dnl# The above copyright notice and this permission notice (including
dnl# the next paragraph) shall be included in all copies or
dnl# substantial portions of the Software.
dnl#
dnl# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl# OTHER DEALINGS IN THE SOFTWARE.
dnl#
dnl# SPDX-License-Identifier: MIT
dnl#

include(`src/m4/config.m4')

changequote(`{|', `|}')

ifdef({|make_rules|}, {|{|
  |}make_target{|: src/m4/config.m4
|}|}, {|{|

package com.stealthsoftwareinc.test.sst;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

import com.stealthsoftwareinc.sst.Arith;
import java.math.BigInteger;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

@Execution(ExecutionMode.CONCURRENT)
public final class ArithTest {

  //--------------------------------------------------------------------
  // floorSqrt
  //--------------------------------------------------------------------

  @Test
  public final void floorSqrt() {
    assertEquals(0, Arith.floorSqrt(0));
    assertEquals(1, Arith.floorSqrt(1));
    assertEquals(1, Arith.floorSqrt(2));
    assertEquals(1, Arith.floorSqrt(3));
    assertEquals(2, Arith.floorSqrt(4));
    assertEquals(2, Arith.floorSqrt(5));
    assertEquals(2, Arith.floorSqrt(6));
    assertEquals(2, Arith.floorSqrt(7));
    assertEquals(2, Arith.floorSqrt(8));
    assertEquals(3, Arith.floorSqrt(9));
    assertEquals(3, Arith.floorSqrt(10));
    assertEquals(3, Arith.floorSqrt(11));
    assertEquals(3, Arith.floorSqrt(12));
    assertEquals(3, Arith.floorSqrt(13));
    assertEquals(3, Arith.floorSqrt(14));
    assertEquals(3, Arith.floorSqrt(15));
    assertEquals(4, Arith.floorSqrt(16));
    assertEquals(4, Arith.floorSqrt(17));
    assertEquals(4, Arith.floorSqrt(18));
    assertEquals(4, Arith.floorSqrt(19));
    assertEquals(4, Arith.floorSqrt(20));
    assertEquals(7842, Arith.floorSqrt(7843 * 7843 - 1));
    assertEquals(7843, Arith.floorSqrt(7843 * 7843 + 0));
    assertEquals(7843, Arith.floorSqrt(7843 * 7843 + 1));
    assertEquals(21097, Arith.floorSqrt(445115245));
    assertEquals(43919, Arith.floorSqrt(1928894012));

    assertEquals(0L, Arith.floorSqrt(0L));
    assertEquals(1L, Arith.floorSqrt(1L));
    assertEquals(1L, Arith.floorSqrt(2L));
    assertEquals(1L, Arith.floorSqrt(3L));
    assertEquals(2L, Arith.floorSqrt(4L));
    assertEquals(2L, Arith.floorSqrt(5L));
    assertEquals(2L, Arith.floorSqrt(6L));
    assertEquals(2L, Arith.floorSqrt(7L));
    assertEquals(2L, Arith.floorSqrt(8L));
    assertEquals(3L, Arith.floorSqrt(9L));
    assertEquals(3L, Arith.floorSqrt(10L));
    assertEquals(3L, Arith.floorSqrt(11L));
    assertEquals(3L, Arith.floorSqrt(12L));
    assertEquals(3L, Arith.floorSqrt(13L));
    assertEquals(3L, Arith.floorSqrt(14L));
    assertEquals(3L, Arith.floorSqrt(15L));
    assertEquals(4L, Arith.floorSqrt(16L));
    assertEquals(4L, Arith.floorSqrt(17L));
    assertEquals(4L, Arith.floorSqrt(18L));
    assertEquals(4L, Arith.floorSqrt(19L));
    assertEquals(4L, Arith.floorSqrt(20L));
    assertEquals(7842L, Arith.floorSqrt(7843L * 7843 - 1));
    assertEquals(7843L, Arith.floorSqrt(7843L * 7843 + 0));
    assertEquals(7843L, Arith.floorSqrt(7843L * 7843 + 1));
    assertEquals(21097L, Arith.floorSqrt(445115245L));
    assertEquals(43919L, Arith.floorSqrt(1928894012L));

    assertEquals(BigInteger.valueOf(0),
                 Arith.floorSqrt(BigInteger.valueOf(0)));
    assertEquals(BigInteger.valueOf(1),
                 Arith.floorSqrt(BigInteger.valueOf(1)));
    assertEquals(BigInteger.valueOf(1),
                 Arith.floorSqrt(BigInteger.valueOf(2)));
    assertEquals(BigInteger.valueOf(1),
                 Arith.floorSqrt(BigInteger.valueOf(3)));
    assertEquals(BigInteger.valueOf(2),
                 Arith.floorSqrt(BigInteger.valueOf(4)));
    assertEquals(BigInteger.valueOf(2),
                 Arith.floorSqrt(BigInteger.valueOf(5)));
    assertEquals(BigInteger.valueOf(2),
                 Arith.floorSqrt(BigInteger.valueOf(6)));
    assertEquals(BigInteger.valueOf(2),
                 Arith.floorSqrt(BigInteger.valueOf(7)));
    assertEquals(BigInteger.valueOf(2),
                 Arith.floorSqrt(BigInteger.valueOf(8)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(9)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(10)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(11)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(12)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(13)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(14)));
    assertEquals(BigInteger.valueOf(3),
                 Arith.floorSqrt(BigInteger.valueOf(15)));
    assertEquals(BigInteger.valueOf(4),
                 Arith.floorSqrt(BigInteger.valueOf(16)));
    assertEquals(BigInteger.valueOf(4),
                 Arith.floorSqrt(BigInteger.valueOf(17)));
    assertEquals(BigInteger.valueOf(4),
                 Arith.floorSqrt(BigInteger.valueOf(18)));
    assertEquals(BigInteger.valueOf(4),
                 Arith.floorSqrt(BigInteger.valueOf(19)));
    assertEquals(BigInteger.valueOf(4),
                 Arith.floorSqrt(BigInteger.valueOf(20)));
    assertEquals(BigInteger.valueOf(7842),
                 Arith.floorSqrt(BigInteger.valueOf(7843 * 7843 - 1)));
    assertEquals(BigInteger.valueOf(7843),
                 Arith.floorSqrt(BigInteger.valueOf(7843 * 7843 + 0)));
    assertEquals(BigInteger.valueOf(7843),
                 Arith.floorSqrt(BigInteger.valueOf(7843 * 7843 + 1)));
    assertEquals(BigInteger.valueOf(21097),
                 Arith.floorSqrt(BigInteger.valueOf(445115245)));
    assertEquals(BigInteger.valueOf(43919),
                 Arith.floorSqrt(BigInteger.valueOf(1928894012)));
    {
      final BigInteger x = new BigInteger("5723463874863");
      assertEquals(
          x.subtract(BigInteger.ONE),
          Arith.floorSqrt(x.multiply(x).subtract(BigInteger.ONE)));
      assertEquals(x, Arith.floorSqrt(x.multiply(x)));
      assertEquals(x,
                   Arith.floorSqrt(x.multiply(x).add(BigInteger.ONE)));
    }
    assertEquals(new BigInteger("312253124222788144"),
                 Arith.floorSqrt(new BigInteger(
                     "97502013586891963967025880669078061")));
  }

  //--------------------------------------------------------------------
  // promoteUnsigned
  //--------------------------------------------------------------------

  @Test
  public final void promoteUnsigned() {
    assertEquals(0xFF, Arith.promoteUnsigned((byte)0xFF));
    assertEquals(0x0F, Arith.promoteUnsigned((byte)0x0F));
    assertEquals(0x00, Arith.promoteUnsigned((byte)0x00));
    assertEquals(0xFFFF, Arith.promoteUnsigned((short)0xFFFF));
    assertEquals(0x0FFF, Arith.promoteUnsigned((short)0x0FFF));
    assertEquals(0x00FF, Arith.promoteUnsigned((short)0x00FF));
    assertEquals(0x000F, Arith.promoteUnsigned((short)0x000F));
    assertEquals(0x0000, Arith.promoteUnsigned((short)0x0000));
    assertEquals(-1, Arith.promoteUnsigned(-1));
    assertEquals(0, Arith.promoteUnsigned(0));
    assertEquals(1, Arith.promoteUnsigned(1));
    assertEquals(-1L, Arith.promoteUnsigned(-1L));
    assertEquals(0L, Arith.promoteUnsigned(0L));
    assertEquals(1L, Arith.promoteUnsigned(1L));
  }

  //--------------------------------------------------------------------
  // toUnsignedBig
  //--------------------------------------------------------------------

  @Test
  public final void toUnsignedBig() {

    |}

    pushdef({|F1|}, {|{|
      assertEquals(BigInteger.valueOf($2),
                   Arith.toUnsignedBig(($1)($2)));
    |}|})

    pushdef({|F2|}, {|{|
      assertEquals(new BigInteger(
                       Long.toHexString(Arith.toUnsignedLong(($1)($2))),
                       16),
                   Arith.toUnsignedBig(($1)($2)));
    |}|})

    pushdef({|F|}, {|

      F1({|$1|}, {|0|})
      F1({|$1|}, {|1|})
      F1({|$1|}, {|2|})
      F1({|$1|}, {|3|})
      F1({|$1|}, {|$2.MAX_VALUE - 3|})
      F1({|$1|}, {|$2.MAX_VALUE - 2|})
      F1({|$1|}, {|$2.MAX_VALUE - 1|})
      F1({|$1|}, {|$2.MAX_VALUE - 0|})

      F2({|$1|}, {|-1|})
      F2({|$1|}, {|-2|})
      F2({|$1|}, {|-3|})
      F2({|$1|}, {|-4|})
      F2({|$1|}, {|$2.MIN_VALUE + 3|})
      F2({|$1|}, {|$2.MIN_VALUE + 2|})
      F2({|$1|}, {|$2.MIN_VALUE + 1|})
      F2({|$1|}, {|$2.MIN_VALUE + 0|})

    |})

    F({|byte|}, {|Byte|})
    F({|short|}, {|Short|})
    F({|int|}, {|Integer|})
    F({|long|}, {|Long|})

    popdef({|F|})
    popdef({|F2|})
    popdef({|F1|})

    {|

    assertEquals(BigInteger.ZERO, Arith.toUnsignedBig(BigInteger.ZERO));
    assertEquals(BigInteger.ONE, Arith.toUnsignedBig(BigInteger.ONE));
    assertEquals(BigInteger.TEN, Arith.toUnsignedBig(BigInteger.TEN));

  }


  //--------------------------------------------------------------------
  // isPowerOfTwo
  //--------------------------------------------------------------------

  @Test
  public final void isPowerOfTwo() {

    |}pushdef({|F|}, {|{|

      assertTrue(Arith.isPowerOfTwo(($1)1));
      assertTrue(Arith.isPowerOfTwo(($1)2));
      assertTrue(Arith.isPowerOfTwo(($1)4));
      assertTrue(Arith.isPowerOfTwo(($1)8));
      assertTrue(Arith.isPowerOfTwo($2.MIN_VALUE >>> 1));

      assertFalse(Arith.isPowerOfTwo(($1)0));
      assertFalse(Arith.isPowerOfTwo(($1)3));
      assertFalse(Arith.isPowerOfTwo(($1)5));
      assertFalse(Arith.isPowerOfTwo(($1)6));
      assertFalse(Arith.isPowerOfTwo(($1)7));

      assertFalse(Arith.isPowerOfTwo(($1)-1));
      assertFalse(Arith.isPowerOfTwo(($1)-2));
      assertFalse(Arith.isPowerOfTwo(($1)-3));
      assertFalse(Arith.isPowerOfTwo(($1)-4));
      assertFalse(Arith.isPowerOfTwo(($1)-5));
      assertFalse(Arith.isPowerOfTwo(($1)-6));
      assertFalse(Arith.isPowerOfTwo(($1)-7));
      assertFalse(Arith.isPowerOfTwo(($1)-8));
      assertFalse(Arith.isPowerOfTwo($2.MIN_VALUE));

    |}|})

    F({|int|}, {|Integer|})
    F({|long|}, {|Long|})

    popdef({|F|}){|

    assertTrue(Arith.isPowerOfTwo(BigInteger.valueOf(1)));
    assertTrue(Arith.isPowerOfTwo(BigInteger.valueOf(2)));
    assertTrue(Arith.isPowerOfTwo(BigInteger.valueOf(4)));
    assertTrue(Arith.isPowerOfTwo(BigInteger.valueOf(8)));
    assertTrue(
        Arith.isPowerOfTwo(BigInteger.valueOf(1).shiftLeft(12345)));

    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(0)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(3)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(5)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(6)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(7)));

    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-1)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-2)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-3)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-4)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-5)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-6)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-7)));
    assertFalse(Arith.isPowerOfTwo(BigInteger.valueOf(-8)));
    assertFalse(Arith.isPowerOfTwo(
        BigInteger.valueOf(1).shiftLeft(12345).negate()));

  }

  //--------------------------------------------------------------------
  // unsignedCmp
  //--------------------------------------------------------------------

  @Test
  public final void unsignedCmp() {

    |}pushdef({|F|}, {|{|

      assertTrue(Arith.unsignedCmp(($1)0, ($1)0) == 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)1) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)2) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)($2.MAX_VALUE - 2)) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)($2.MAX_VALUE - 1)) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)($2.MAX_VALUE - 0)) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)($2.MIN_VALUE + 0)) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)($2.MIN_VALUE + 1)) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)($2.MIN_VALUE + 2)) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)-3) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)-2) < 0);
      assertTrue(Arith.unsignedCmp(($1)0, ($1)-1) < 0);

      assertTrue(Arith.unsignedCmp(($1)-1, ($1)0) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)1) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)2) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)($2.MAX_VALUE - 2)) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)($2.MAX_VALUE - 1)) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)($2.MAX_VALUE - 0)) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)($2.MIN_VALUE + 0)) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)($2.MIN_VALUE + 1)) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)($2.MIN_VALUE + 2)) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)-3) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)-2) > 0);
      assertTrue(Arith.unsignedCmp(($1)-1, ($1)-1) == 0);

    |}|}){|

    |}F({|byte|}, {|Byte|}){|
    |}F({|short|}, {|Short|}){|
    |}F({|int|}, {|Integer|}){|
    |}F({|long|}, {|Long|}){|

    |}popdef({|F|}){|

  }

  //--------------------------------------------------------------------
  // unsignedMod
  //--------------------------------------------------------------------

  @Test
  public final void unsignedMod() {

    |}pushdef({|F|}, {|{|

      assertEquals(($1)0, Arith.unsignedMod(($1)0, ($1)-1));
      assertEquals(($1)1, Arith.unsignedMod(($1)1, ($1)-1));
      assertEquals(($1)2, Arith.unsignedMod(($1)2, ($1)-1));
      assertEquals(($1)($2.MAX_VALUE - 2),
                   Arith.unsignedMod(($1)($2.MAX_VALUE - 2), ($1)-1));
      assertEquals(($1)($2.MAX_VALUE - 1),
                   Arith.unsignedMod(($1)($2.MAX_VALUE - 1), ($1)-1));
      assertEquals(($1)($2.MAX_VALUE - 0),
                   Arith.unsignedMod(($1)($2.MAX_VALUE - 0), ($1)-0));
      assertEquals(($1)($2.MIN_VALUE + 0),
                   Arith.unsignedMod(($1)($2.MIN_VALUE + 0), ($1)-0));
      assertEquals(($1)($2.MIN_VALUE + 1),
                   Arith.unsignedMod(($1)($2.MIN_VALUE + 1), ($1)-1));
      assertEquals(($1)($2.MIN_VALUE + 2),
                   Arith.unsignedMod(($1)($2.MIN_VALUE + 2), ($1)-1));
      assertEquals(($1)-3, Arith.unsignedMod(($1)-3, ($1)-1));
      assertEquals(($1)-2, Arith.unsignedMod(($1)-2, ($1)-1));
      assertEquals(($1)0, Arith.unsignedMod(($1)-1, ($1)-1));

    |}|}){|

    assertEquals(123L, Arith.unsignedMod(123L, 456L));
    assertEquals(123L, Arith.unsignedMod(579L, 456L));

    assertEquals(0L, Arith.unsignedMod(-1L, 1L));
    assertEquals(1L, Arith.unsignedMod(-1L, 2L));
    assertEquals(0L, Arith.unsignedMod(-1L, 3L));
    assertEquals(3L, Arith.unsignedMod(-1L, 4L));
    assertEquals(0L, Arith.unsignedMod(-1L, 5L));
    assertEquals(1L, Arith.unsignedMod(-1L, 7L));
    assertEquals(834183465L, Arith.unsignedMod(-1L, 1234567890L));

  }

  //--------------------------------------------------------------------
}

|}|})
