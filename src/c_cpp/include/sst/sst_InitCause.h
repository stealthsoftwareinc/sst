/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Declares the
 * <code>::sst_InitCause</code>
 * function.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_INITCAUSE_H
#define SST_SST_INITCAUSE_H

#include <sst/SST_HAVE_SST_INITCAUSE.h>
#if SST_HAVE_SST_INITCAUSE

/* begin_includes */

#include <jni.h>
#include <sst/catalog/SST_PUBLIC_C_FUNCTION.h>
#include <sst/sst_bool.h>

/* end_includes */

/**
 * Initializes the cause of a Java object of class
 * <code>java.lang.Throwable</code>
 * or any subclass thereof.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_FUNCTION sst_bool (sst_InitCause)(
  JNIEnv *,
  jthrowable,
  jthrowable
);

#else

sst_bool sst_InitCause(
  JNIEnv * env,
  jthrowable obj,
  jthrowable cause
);

#endif

#endif

#endif
