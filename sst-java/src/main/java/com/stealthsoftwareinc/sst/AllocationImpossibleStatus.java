/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/*!
 * @file
 *
 * Defines the
 * <code>com.stealthsoftwareinc.sst.AllocationImpossibleStatus</code>
 * Java class.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

package com.stealthsoftwareinc.sst;

/* begin_imports */

import com.stealthsoftwareinc.sst.LimitExceededStatus;
import java.lang.String;

/* end_imports */

/**
 * Thrown when a memory allocation fails because the size is too large
 * to make the underlying allocation request.
 * <p>
 * This class corresponds to the
 * <code>SST_ALLOCATION_IMPOSSIBLE</code>
 * status code.
 * For more information, see the Status Codes section of the SST manual.
 * </p>
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public class AllocationImpossibleStatus
extends LimitExceededStatus
{

/**
 * Constructs an
 * <code>AllocationImpossibleStatus</code>
 * exception without a detail message and with an uninitialized cause.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public AllocationImpossibleStatus(
) {
  this(null);
}

/**
 * Constructs an
 * <code>AllocationImpossibleStatus</code>
 * exception with or without a detail message and with an uninitialized
 * cause.
 *
 * @param message
 * the detail message, or
 * <code>null</code>
 * for no detail message
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

public AllocationImpossibleStatus(
  final String message
) {
  super(message);
}

}
