dnl
dnl Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
dnl
dnl Permission is hereby granted, free of charge, to any person
dnl obtaining a copy of this software and associated documentation
dnl files (the "Software"), to deal in the Software without
dnl restriction, including without limitation the rights to use,
dnl copy, modify, merge, publish, distribute, sublicense, and/or
dnl sell copies of the Software, and to permit persons to whom the
dnl Software is furnished to do so, subject to the following
dnl conditions:
dnl
dnl The above copyright notice and this permission notice (including
dnl the next paragraph) shall be included in all copies or
dnl substantial portions of the Software.
dnl
dnl THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
dnl OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
dnl NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
dnl HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
dnl WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
dnl OTHER DEALINGS IN THE SOFTWARE.
dnl
dnl SPDX-License-Identifier: MIT
dnl

include(`src/m4/config.m4')

changequote(`{|', `|}')

ifdef({|make_rules|}, {|{|
  |}make_target{|: src/m4/config.m4
|}|}, {|{|

package com.stealthsoftwareinc.test.sst;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.stealthsoftwareinc.sst.Modulus;
import java.math.BigInteger;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

@Execution(ExecutionMode.CONCURRENT)
public final class ModulusTest {

  //--------------------------------------------------------------------
  // get
  //--------------------------------------------------------------------

  @Test
  public final void get() {

    assertEquals(1, new Modulus(1).get((Integer)null));
    assertEquals(2, new Modulus(2).get((Integer)null));
    assertEquals(3, new Modulus(3).get((Integer)null));

    assertEquals(0, new Modulus(1L << 32).get((Integer)null));
    assertEquals(
        0,
        new Modulus(BigInteger.ONE.shiftLeft(64)).get((Long)null));

  }

  //--------------------------------------------------------------------
  // topMask
  //--------------------------------------------------------------------

  @Test
  public final void topMask() {

    assertEquals((byte)0x00, new Modulus(1).topMask());
    assertEquals((byte)0x01, new Modulus(2).topMask());
    assertEquals((byte)0x03, new Modulus(3).topMask());
    assertEquals((byte)0x03, new Modulus(4).topMask());
    assertEquals((byte)0x07, new Modulus(5).topMask());
    assertEquals((byte)0x07, new Modulus(6).topMask());
    assertEquals((byte)0x07, new Modulus(7).topMask());
    assertEquals((byte)0x07, new Modulus(8).topMask());
    assertEquals((byte)0x0F, new Modulus(9).topMask());
    assertEquals((byte)0xFF, new Modulus(255).topMask());
    assertEquals((byte)0xFF, new Modulus(256).topMask());
    assertEquals((byte)0x01, new Modulus(257).topMask());
    assertEquals((byte)0x01, new Modulus(258).topMask());
    assertEquals((byte)0x01, new Modulus(512).topMask());
    assertEquals((byte)0x03, new Modulus(513).topMask());

  }

  //--------------------------------------------------------------------
  // valueSize
  //--------------------------------------------------------------------

  @Test
  public final void valueSize() {

    assertEquals(1, Modulus.valueSize(1));
    assertEquals(1, Modulus.valueSize(2));
    assertEquals(1, Modulus.valueSize(3));
    assertEquals(1, Modulus.valueSize(254));
    assertEquals(1, Modulus.valueSize(255));
    assertEquals(1, Modulus.valueSize(256));
    assertEquals(2, Modulus.valueSize(257));
    assertEquals(2, Modulus.valueSize(258));
    assertEquals(2, Modulus.valueSize(259));
    assertEquals(2, Modulus.valueSize(65534));
    assertEquals(2, Modulus.valueSize(65535));
    assertEquals(2, Modulus.valueSize(65536));
    assertEquals(3, Modulus.valueSize(65537));
    assertEquals(3, Modulus.valueSize(65538));
    assertEquals(3, Modulus.valueSize(65539));

    assertEquals(1, Modulus.valueSize(BigInteger.valueOf(1)));
    assertEquals(1, Modulus.valueSize(BigInteger.valueOf(2)));
    assertEquals(1, Modulus.valueSize(BigInteger.valueOf(3)));
    assertEquals(1, Modulus.valueSize(BigInteger.valueOf(254)));
    assertEquals(1, Modulus.valueSize(BigInteger.valueOf(255)));
    assertEquals(1, Modulus.valueSize(BigInteger.valueOf(256)));
    assertEquals(2, Modulus.valueSize(BigInteger.valueOf(257)));
    assertEquals(2, Modulus.valueSize(BigInteger.valueOf(258)));
    assertEquals(2, Modulus.valueSize(BigInteger.valueOf(259)));
    assertEquals(2, Modulus.valueSize(BigInteger.valueOf(65534)));
    assertEquals(2, Modulus.valueSize(BigInteger.valueOf(65535)));
    assertEquals(2, Modulus.valueSize(BigInteger.valueOf(65536)));
    assertEquals(3, Modulus.valueSize(BigInteger.valueOf(65537)));
    assertEquals(3, Modulus.valueSize(BigInteger.valueOf(65538)));
    assertEquals(3, Modulus.valueSize(BigInteger.valueOf(65539)));

    assertEquals(1, new Modulus(1).valueSize());
    assertEquals(1, new Modulus(2).valueSize());
    assertEquals(1, new Modulus(3).valueSize());
    assertEquals(1, new Modulus(4).valueSize());
    assertEquals(1, new Modulus(5).valueSize());
    assertEquals(1, new Modulus(255).valueSize());
    assertEquals(1, new Modulus(256).valueSize());
    assertEquals(2, new Modulus(257).valueSize());
    assertEquals(2, new Modulus(258).valueSize());
    assertEquals(2, new Modulus(65535).valueSize());
    assertEquals(2, new Modulus(65536).valueSize());
    assertEquals(3, new Modulus(65537).valueSize());
    assertEquals(3, new Modulus(65538).valueSize());

  }

  //--------------------------------------------------------------------
  // valuesFit
  //--------------------------------------------------------------------

  @Test
  public final void valuesFit() {

    |}

    pushdef({|F1|}, {|{|
      assertEquals(
          new BigInteger($1).compareTo(BigInteger.valueOf($2.MAX_VALUE)
                                           .shiftLeft(1)
                                           .add(BigInteger.valueOf(2)))
              <= 0,
          new Modulus(new BigInteger($1)).valuesFit(($2)null));
    |}|})

    pushdef({|F|}, {|{|
      |}
      F1({|$1|}, {|Byte|})
      F1({|$1|}, {|Short|})
      F1({|$1|}, {|Integer|})
      F1({|$1|}, {|Long|})
      {|
      assertTrue(
          new Modulus(new BigInteger($1)).valuesFit((BigInteger)null));
    |}|})

    F({|"1"|})
    F({|"2"|})
    F({|"3"|})
    F({|"254"|})
    F({|"255"|})
    F({|"256"|})
    F({|"257"|})
    F({|"258"|})
    F({|"65534"|})
    F({|"65535"|})
    F({|"65536"|})
    F({|"65537"|})
    F({|"65538"|})
    F({|"4294967294"|})
    F({|"4294967295"|})
    F({|"4294967296"|})
    F({|"4294967297"|})
    F({|"4294967298"|})
    F({|"18446744073709551614"|})
    F({|"18446744073709551615"|})
    F({|"18446744073709551616"|})
    F({|"18446744073709551617"|})
    F({|"18446744073709551618"|})

    popdef({|F|})
    popdef({|F1|})

    {|

  }

  //--------------------------------------------------------------------
}

|}|})
