/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

package com.stealthsoftwareinc.tests.sst;

/* begin_imports */

import com.stealthsoftwareinc.sst.Args;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

/* end_imports */

public final class ArgsTest
{

@Test
public final void testAddNullNull(
) {
  final String[] args = Args.addNull(null);
  assertNotEquals(args, null);
  assertEquals(args.length, 1);
  assertEquals(args[0], null);
}

}
