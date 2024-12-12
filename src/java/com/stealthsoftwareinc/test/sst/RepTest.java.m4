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

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import com.stealthsoftwareinc.sst.IntegerRep;
import com.stealthsoftwareinc.sst.Json;
import com.stealthsoftwareinc.sst.Rep;
import com.stealthsoftwareinc.sst.RepException;
import java.math.BigInteger;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.concurrent.Callable;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.function.Executable;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

|}ifelse(WITH_NETTY, 1, {|{|
import io.netty.buffer.Unpooled;
|}|}){|

@Execution(ExecutionMode.CONCURRENT)
public final class RepTest {
  @Test
  public final void testByteMethods() {
    final Byte T = null;

    assertEquals(Rep.toInteger(false, T), 0);
    assertEquals(Rep.toInteger(true, T), 1);

    assertEquals(Rep.toInteger("+0", T), +0);
    assertEquals(Rep.toInteger("+1", T), +1);
    assertEquals(Rep.toInteger("-0", T), -0);
    assertEquals(Rep.toInteger("-1", T), -1);
    assertEquals(Rep.toInteger("0", T), 0);
    assertEquals(Rep.toInteger("1", T), 1);
  }

  @Test
  public final void testFromHexChar() {
    assertEquals((byte)0, Rep.fromHex('0'));
    assertEquals((byte)1, Rep.fromHex('1'));
    assertEquals((byte)2, Rep.fromHex('2'));
    assertEquals((byte)3, Rep.fromHex('3'));
    assertEquals((byte)4, Rep.fromHex('4'));
    assertEquals((byte)5, Rep.fromHex('5'));
    assertEquals((byte)6, Rep.fromHex('6'));
    assertEquals((byte)7, Rep.fromHex('7'));
    assertEquals((byte)8, Rep.fromHex('8'));
    assertEquals((byte)9, Rep.fromHex('9'));
    assertEquals((byte)10, Rep.fromHex('A'));
    assertEquals((byte)11, Rep.fromHex('B'));
    assertEquals((byte)12, Rep.fromHex('C'));
    assertEquals((byte)13, Rep.fromHex('D'));
    assertEquals((byte)14, Rep.fromHex('E'));
    assertEquals((byte)15, Rep.fromHex('F'));
    assertEquals((byte)10, Rep.fromHex('a'));
    assertEquals((byte)11, Rep.fromHex('b'));
    assertEquals((byte)12, Rep.fromHex('c'));
    assertEquals((byte)13, Rep.fromHex('d'));
    assertEquals((byte)14, Rep.fromHex('e'));
    assertEquals((byte)15, Rep.fromHex('f'));
    for (final char c : Arrays.asList('x',
                                      '\u0100',
                                      '\uFF21',
                                      '\uFF22',
                                      '\uFF23',
                                      '\uFF24',
                                      '\uFF25',
                                      '\uFF26',
                                      '\uFF41',
                                      '\uFF42',
                                      '\uFF43',
                                      '\uFF44',
                                      '\uFF45',
                                      '\uFF46')) {
      assertThrows(RepException.class, new Executable() {
        @Override
        public final void execute() throws Throwable {
          Rep.fromHex(c);
        }
      }, Json.quote(c));
    }
  }

  //--------------------------------------------------------------------
  // fromBytes
  //--------------------------------------------------------------------

  // expected must be the exact value specified by the rest of the
  // parameters. No overflow testing.
  private final void testFromBytesNoOverflow(
      final String expected,
      final byte[] src,
      final int srcPos,
      final int srcLen,
      final IntegerRep integerRep,
      final ByteOrder byteOrder) {
    |}

    pushdef({|F|}, {|{|{
      $1 x;
      try {
        x = $2(expected);
      } catch (final NumberFormatException e) {
        x = null;
      }
      if (x != null) {
        assertEquals(x,
                     Rep.fromBytes(src,
                                   srcPos,
                                   srcLen,
                                   ($1)null,
                                   integerRep,
                                   byteOrder,
                                   false));
        |}ifelse(WITH_NETTY, 1, {|{|{
          assertEquals(
              x,
              Rep.fromBytes(
                  Unpooled.wrappedBuffer(src),
                  srcPos,
                  srcLen,
                  ($1)null,
                  integerRep,
                  byteOrder,
                  false));
        }|}|}){|
      }
    }|}|})

    F({|Byte|}, {|Byte.valueOf|})
    F({|Short|}, {|Short.valueOf|})
    F({|Integer|}, {|Integer.valueOf|})
    F({|Long|}, {|Long.valueOf|})
    F({|BigInteger|}, {|new BigInteger|})

    popdef({|F|})

    {|
  }

  @Test
  public final void testFromBytes() {
    //------------------------------------------------------------------

    testFromBytesNoOverflow("0",
                            new byte[] {
                                (byte)0x00,
                                (byte)0x00,
                                (byte)0x00,
                            },
                            1,
                            1,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.BIG_ENDIAN);

    testFromBytesNoOverflow("-1",
                            new byte[] {
                                (byte)0x00,
                                (byte)0xFF,
                                (byte)0x00,
                            },
                            1,
                            1,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.BIG_ENDIAN);

    testFromBytesNoOverflow("-1",
                            new byte[] {
                                (byte)0xFF,
                                (byte)0xFF,
                                (byte)0xFF,
                                (byte)0xFF,
                                (byte)0xFF,
                            },
                            0,
                            5,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.LITTLE_ENDIAN);

    testFromBytesNoOverflow("4660",
                            new byte[] {
                                (byte)0x00,
                                (byte)0x12,
                                (byte)0x34,
                                (byte)0x00,
                            },
                            1,
                            2,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.BIG_ENDIAN);

    testFromBytesNoOverflow("1192960",
                            new byte[] {
                                (byte)0x00,
                                (byte)0x12,
                                (byte)0x34,
                                (byte)0x00,
                            },
                            1,
                            3,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.BIG_ENDIAN);

    testFromBytesNoOverflow("13330",
                            new byte[] {
                                (byte)0x00,
                                (byte)0x12,
                                (byte)0x34,
                                (byte)0x00,
                            },
                            1,
                            2,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.LITTLE_ENDIAN);

    testFromBytesNoOverflow("13330",
                            new byte[] {
                                (byte)0x00,
                                (byte)0x12,
                                (byte)0x34,
                                (byte)0x00,
                            },
                            1,
                            3,
                            IntegerRep.TWOS_COMPLEMENT,
                            ByteOrder.LITTLE_ENDIAN);

    assertEquals(-256,
                 Rep.fromBytes(
                     new byte[] {
                         (byte)0xFF,
                         (byte)0xFF,
                         (byte)0xFF,
                         (byte)0xFF,
                         (byte)0x00,
                     },
                     0,
                     5,
                     (Integer)null,
                     IntegerRep.TWOS_COMPLEMENT,
                     ByteOrder.BIG_ENDIAN,
                     false));

    assertEquals(-1,
                 Rep.fromBytes(
                     new byte[] {
                         (byte)0xFF,
                         (byte)0xFF,
                         (byte)0xFF,
                         (byte)0xFF,
                         (byte)0x00,
                     },
                     0,
                     5,
                     (Integer)null,
                     IntegerRep.TWOS_COMPLEMENT,
                     ByteOrder.LITTLE_ENDIAN,
                     false));

    assertEquals((byte)0,
                 Rep.fromBytes(
                     new byte[] {
                         (byte)0xFF,
                         (byte)0x00,
                     },
                     0,
                     2,
                     (Byte)null,
                     IntegerRep.PURE_UNSIGNED,
                     ByteOrder.BIG_ENDIAN,
                     false));

    assertThrows(RepException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        Rep.fromBytes(
            new byte[] {
                (byte)0xFF,
                (byte)0x00,
            },
            0,
            2,
            (Byte)null,
            IntegerRep.PURE_UNSIGNED,
            ByteOrder.BIG_ENDIAN,
            true);
      }
    });

    //------------------------------------------------------------------
  }

  //--------------------------------------------------------------------
  // toBytes
  //--------------------------------------------------------------------

  @Test
  public final void toBytes() {

    |}

    pushdef({|F|}, {|{|

      assertArrayEquals(Rep.fromHex("AA00BB"), new Callable<byte[]>() {
        @Override
        public final byte[] call() {
          final byte[] dst = Rep.fromHex("AA11BB");
          Rep.toBytes($1(0),
                      dst,
                      1,
                      1,
                      IntegerRep.TWOS_COMPLEMENT,
                      ByteOrder.BIG_ENDIAN,
                      false);
          return dst;
        }
      }.call());

      assertArrayEquals(Rep.fromHex("AA01BB"), new Callable<byte[]>() {
        @Override
        public final byte[] call() {
          final byte[] dst = Rep.fromHex("AA11BB");
          Rep.toBytes($1(1),
                      dst,
                      1,
                      1,
                      IntegerRep.TWOS_COMPLEMENT,
                      ByteOrder.BIG_ENDIAN,
                      false);
          return dst;
        }
      }.call());

      assertArrayEquals(Rep.fromHex("AAFFBB"), new Callable<byte[]>() {
        @Override
        public final byte[] call() {
          final byte[] dst = Rep.fromHex("AA11BB");
          Rep.toBytes($1(-1),
                      dst,
                      1,
                      1,
                      IntegerRep.TWOS_COMPLEMENT,
                      ByteOrder.BIG_ENDIAN,
                      false);
          return dst;
        }
      }.call());

      assertArrayEquals(Rep.fromHex("AA0000BB"),
                        new Callable<byte[]>() {
                          @Override
                          public final byte[] call() {
                            final byte[] dst = Rep.fromHex("AA1111BB");
                            Rep.toBytes($1(0),
                                        dst,
                                        1,
                                        2,
                                        IntegerRep.TWOS_COMPLEMENT,
                                        ByteOrder.BIG_ENDIAN,
                                        false);
                            return dst;
                          }
                        }.call());

      assertArrayEquals(Rep.fromHex("AA0000BB"),
                        new Callable<byte[]>() {
                          @Override
                          public final byte[] call() {
                            final byte[] dst = Rep.fromHex("AA1111BB");
                            Rep.toBytes($1(0),
                                        dst,
                                        1,
                                        2,
                                        IntegerRep.TWOS_COMPLEMENT,
                                        ByteOrder.LITTLE_ENDIAN,
                                        false);
                            return dst;
                          }
                        }.call());

      assertArrayEquals(Rep.fromHex("AA0001BB"),
                        new Callable<byte[]>() {
                          @Override
                          public final byte[] call() {
                            final byte[] dst = Rep.fromHex("AA1111BB");
                            Rep.toBytes($1(1),
                                        dst,
                                        1,
                                        2,
                                        IntegerRep.TWOS_COMPLEMENT,
                                        ByteOrder.BIG_ENDIAN,
                                        false);
                            return dst;
                          }
                        }.call());

      assertArrayEquals(Rep.fromHex("AA0100BB"),
                        new Callable<byte[]>() {
                          @Override
                          public final byte[] call() {
                            final byte[] dst = Rep.fromHex("AA1111BB");
                            Rep.toBytes($1(1),
                                        dst,
                                        1,
                                        2,
                                        IntegerRep.TWOS_COMPLEMENT,
                                        ByteOrder.LITTLE_ENDIAN,
                                        false);
                            return dst;
                          }
                        }.call());

      assertArrayEquals(Rep.fromHex("AAFFFFBB"),
                        new Callable<byte[]>() {
                          @Override
                          public final byte[] call() {
                            final byte[] dst = Rep.fromHex("AA1111BB");
                            Rep.toBytes($1(-1),
                                        dst,
                                        1,
                                        2,
                                        IntegerRep.TWOS_COMPLEMENT,
                                        ByteOrder.BIG_ENDIAN,
                                        false);
                            return dst;
                          }
                        }.call());

      assertArrayEquals(Rep.fromHex("AAFFFFBB"),
                        new Callable<byte[]>() {
                          @Override
                          public final byte[] call() {
                            final byte[] dst = Rep.fromHex("AA1111BB");
                            Rep.toBytes($1(-1),
                                        dst,
                                        1,
                                        2,
                                        IntegerRep.TWOS_COMPLEMENT,
                                        ByteOrder.LITTLE_ENDIAN,
                                        false);
                            return dst;
                          }
                        }.call());

    |}|})

    F({|(byte)|})
    F({|(short)|})
    F({|(int)|})
    F({|(long)|})
    F({|BigInteger.valueOf|})

    {|

    assertArrayEquals(Rep.fromHex("AA4BAE2576DEC10500BB"),
                      new Callable<byte[]>() {
                        @Override
                        public final byte[] call() {
                          final byte[] dst =
                              Rep.fromHex("AA1111111111111111BB");
                          Rep.toBytes(1620536092634699L,
                                      dst,
                                      1,
                                      8,
                                      IntegerRep.TWOS_COMPLEMENT,
                                      ByteOrder.LITTLE_ENDIAN,
                                      false);
                          return dst;
                        }
                      }.call());

    assertArrayEquals(
        Rep.fromHex("AA4BAE2576DEC10500BB"),
        new Callable<byte[]>() {
          @Override
          public final byte[] call() {
            final byte[] dst = Rep.fromHex("AA1111111111111111BB");
            Rep.toBytes(BigInteger.valueOf(1620536092634699L),
                        dst,
                        1,
                        8,
                        IntegerRep.TWOS_COMPLEMENT,
                        ByteOrder.LITTLE_ENDIAN,
                        false);
            return dst;
          }
        }.call());

  }

  //--------------------------------------------------------------------
  // toHex
  //--------------------------------------------------------------------

  @Test
  public final void toHex() {
    assertEquals("", Rep.toHex(new byte[] {}));
    assertEquals("00",
                 Rep.toHex(new byte[] {
                     (byte)0x00,
                 }));
    assertEquals("FF",
                 Rep.toHex(new byte[] {
                     (byte)0xFF,
                 }));
    assertEquals("AB",
                 Rep.toHex(new byte[] {
                     (byte)0xAB,
                 }));
    assertEquals("ABCD",
                 Rep.toHex(new byte[] {
                     (byte)0xAB,
                     (byte)0xCD,
                 }));
    assertEquals("0123456789abcdef",
                 Rep.toHex(
                     new byte[] {
                         (byte)0x01,
                         (byte)0x23,
                         (byte)0x45,
                         (byte)0x67,
                         (byte)0x89,
                         (byte)0xAB,
                         (byte)0xCD,
                         (byte)0xEF,
                     },
                     false));
  }

  //--------------------------------------------------------------------
}

|}|})
