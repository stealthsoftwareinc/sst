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
import static org.junit.jupiter.api.Assertions.assertThrows;

import com.stealthsoftwareinc.sst.FixedPointModContext;
import com.stealthsoftwareinc.sst.Modulus;
import java.math.BigDecimal;
import java.math.BigInteger;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.function.Executable;
import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;

@Execution(ExecutionMode.CONCURRENT)
public final class FixedPointModContextTest {
  //--------------------------------------------------------------------

  |}

  pushdef({|F1|}, {|{|

    @Test
    public final void testEncodeDecodeZeroModulus$1() {
      final FixedPointModContext c = new FixedPointModContext(
          new Modulus(BigInteger.ONE.shiftLeft($1.SIZE)),
          0);

      assertEquals($1.MIN_VALUE,
                   c.decode(c.encode($1.MIN_VALUE, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals($1.MIN_VALUE / 2,
                   c.decode(c.encode($1.MIN_VALUE / 2, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals(
          0,
          c.decode(c.encode(0, ($1)null, true), ($1)null, true));

      assertEquals($1.MAX_VALUE / 2,
                   c.decode(c.encode($1.MAX_VALUE / 2, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals($1.MAX_VALUE,
                   c.decode(c.encode($1.MAX_VALUE, ($1)null, true),
                            ($1)null,
                            true));
    }

    @Test
    public final void testEncodeDecodeNegativeModulus$1() {
      final FixedPointModContext c = new FixedPointModContext(
          new Modulus(BigInteger.ONE.shiftLeft($1.SIZE).subtract(
              BigInteger.ONE)),
          0);

      assertEquals($1.MIN_VALUE + 1,
                   c.decode(c.encode($1.MIN_VALUE + 1, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals($1.MIN_VALUE / 2,
                   c.decode(c.encode($1.MIN_VALUE / 2, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals(
          0,
          c.decode(c.encode(0, ($1)null, true), ($1)null, true));

      assertEquals($1.MAX_VALUE / 2,
                   c.decode(c.encode($1.MAX_VALUE / 2, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals($1.MAX_VALUE,
                   c.decode(c.encode($1.MAX_VALUE, ($1)null, true),
                            ($1)null,
                            true));

      assertThrows(RuntimeException.class, new Executable() {
        @Override
        public final void execute() throws Throwable {
          c.encode($1.MIN_VALUE, ($1)null, true);
        }
      });
    }

    @Test
    public final void testEncodeDecodePositiveModulus$1() {
      final FixedPointModContext c = new FixedPointModContext(
          new Modulus(BigInteger.ONE.shiftLeft($1.SIZE - 1)
                          .subtract(BigInteger.ONE)),
          0);

      assertEquals(
          $1.MIN_VALUE / 2 + 1,
          c.decode(c.encode($1.MIN_VALUE / 2 + 1, ($1)null, true),
                   ($1)null,
                   true));

      assertEquals($1.MIN_VALUE / 4,
                   c.decode(c.encode($1.MIN_VALUE / 4, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals(
          0,
          c.decode(c.encode(0, ($1)null, true), ($1)null, true));

      assertEquals($1.MAX_VALUE / 4,
                   c.decode(c.encode($1.MAX_VALUE / 4, ($1)null, true),
                            ($1)null,
                            true));

      assertEquals($1.MAX_VALUE / 2,
                   c.decode(c.encode($1.MAX_VALUE / 2, ($1)null, true),
                            ($1)null,
                            true));

      assertThrows(RuntimeException.class, new Executable() {
        @Override
        public final void execute() throws Throwable {
          c.encode($1.MIN_VALUE / 2, ($1)null, true);
        }
      });

      assertThrows(RuntimeException.class, new Executable() {
        @Override
        public final void execute() throws Throwable {
          c.encode($1.MAX_VALUE / 2 + 1, ($1)null, true);
        }
      });
    }

    @Test
    public final void testEncodeDecodeMax$1() {
      final BigInteger modulusBig = BigInteger.ONE.shiftLeft($1.SIZE);
      final BigInteger maxValueBig =
          modulusBig.subtract(BigInteger.ONE).shiftRight(1);
      final BigInteger badValueBig = maxValueBig.add(BigInteger.ONE);

      final FixedPointModContext c =
          new FixedPointModContext(new Modulus(modulusBig),
                                   maxValueBig.toString().length() - 1);

      {
        final BigDecimal x =
            new BigDecimal(new StringBuilder(maxValueBig.toString())
                               .insert(1, ".")
                               .toString());
        assertEquals(x, c.decode(c.encode(x, ($1)null, true), x, true));
      }

      {
        final BigDecimal x =
            new BigDecimal(new StringBuilder(badValueBig.toString())
                               .insert(1, ".")
                               .toString());
        assertThrows(RuntimeException.class, new Executable() {
          @Override
          public final void execute() throws Throwable {
            c.encode(x, ($1)null, true);
          }
        });
      }
    }

  |}|})

  F1({|Integer|})
  F1({|Long|})

  popdef({|F1|})

  {|

  //--------------------------------------------------------------------
}

|}|})
