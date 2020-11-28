/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

package com.stealthsoftwareinc.tests.sst;

/* begin_imports */

import com.stealthsoftwareinc.sst.HostNamePredicate;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

/* end_imports */

public class HostNamePredicateTest
{

  @Test
  public void testNull(
  ) {
    assertEquals(
      new HostNamePredicate().test(null),
      false
    );
  }

  @Test
  public void testIPv4Loopback(
  ) {
    assertEquals(
      new HostNamePredicate().test("127.0.0.1"),
      true
    );
  }

}
