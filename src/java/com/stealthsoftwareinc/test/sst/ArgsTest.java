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

import com.stealthsoftwareinc.sst.Args;
import com.stealthsoftwareinc.sst.OptArg;
import com.stealthsoftwareinc.sst.OptException;
import java.util.Arrays;
import java.util.LinkedList;
import org.junit.jupiter.api.*;
import org.junit.jupiter.api.function.*;

public final class ArgsTest {
  @Test
  public final void testAddNullNull() {
    final String[] args = Args.addNull(null);
    assertNotEquals(args, null);
    assertEquals(args.length, 1);
    assertEquals(args[0], null);
  }

  //
  // The following sections of code are similar:
  //
  //     * The main function in <src/c-cpp/test/sst/parse_opt.cpp>.
  //
  //     * The testParseOpt method in
  //       <src/java/com/stealthsoftwareinc/test/sst/ArgsTest.java>.
  //
  // If you edit one of these, you may need to edit the other.
  //

  private static final <T> LinkedList<T> asLinkedList(final T... args) {
    return new LinkedList<T>(Arrays.asList(args));
  }

  @Test
  public final void testParseOpt() {

    boolean ret;
    LinkedList<String> args;
    final boolean[] hasArg = new boolean[] {false};

    //------------------------------------------------------------------
    // Match with required argument
    //------------------------------------------------------------------

    ret = Args.parseOpt(args = asLinkedList("--x", "y"),
                        "--x",
                        OptArg.REQUIRED,
                        hasArg);
    assertTrue(ret);
    assertEquals(asLinkedList("y"), args);
    assertTrue(hasArg[0]);

    assertThrows(OptException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        Args.parseOpt(asLinkedList("--x"),
                      "--x",
                      OptArg.REQUIRED,
                      hasArg);
      }
    });

    ret = Args.parseOpt(args = asLinkedList("--x=y"),
                        "--x",
                        OptArg.REQUIRED,
                        hasArg);
    assertTrue(ret);
    assertEquals(asLinkedList("y"), args);
    assertTrue(hasArg[0]);

    ret = Args.parseOpt(args = asLinkedList("-x", "y"),
                        "-x",
                        OptArg.REQUIRED,
                        hasArg);
    assertTrue(ret);
    assertEquals(asLinkedList("y"), args);
    assertTrue(hasArg[0]);

    assertThrows(OptException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        Args.parseOpt(asLinkedList("-x"),
                      "-x",
                      OptArg.REQUIRED,
                      hasArg);
      }
    });

    ret = Args.parseOpt(args = asLinkedList("-xy"),
                        "-x",
                        OptArg.REQUIRED,
                        hasArg);
    assertTrue(ret);
    assertEquals(asLinkedList("y"), args);
    assertTrue(hasArg[0]);

    //------------------------------------------------------------------
  }

  //--------------------------------------------------------------------
  // Args.requireOpt
  //--------------------------------------------------------------------
  //
  // The following sections of code are similar:
  //
  //     * The main function in <src/c-cpp/test/sst/require_opt.cpp>.
  //
  //     * The testRequireOpt method in
  //       <src/java/com/stealthsoftwareinc/test/sst/ArgsTest.java>.
  //
  // If you edit one of these, you may need to edit the other(s).
  //

  @Test
  public final void testRequireOpt() {
    assertDoesNotThrow(new Executable() {
      @Override
      public final void execute() throws Throwable {
        Args.requireOpt("--foo", true);
      }
    });

    assertThrows(OptException.class, new Executable() {
      @Override
      public final void execute() throws Throwable {
        Args.requireOpt("--foo", false);
      }
    });
  }

  //--------------------------------------------------------------------
}
