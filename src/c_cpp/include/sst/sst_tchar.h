/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Defines the
 * <code>::sst_tchar</code>
 * macro.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_SST_TCHAR_H
#define SST_SST_TCHAR_H

/* begin_includes */

#include <stddef.h>

/* end_includes */

/**
 * Expands to
 * <code>wchar_t</code>
 * if the
 * <code>SST_UNICODE</code>
 * macro is defined, or to
 * <code>char</code>
 * if not.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * in SST&nbsp;X.X.X (XXXX-XX-XX):
 * <ul>
 * <li>
 * This identifier was changed from a type to a type-selecting macro.
 * </li>
 * </ul>
 *
 * @showinitializer
 */

#ifndef SST_DOXYGEN

#if (defined(SST_UNICODE))
  #define sst_tchar wchar_t
#else
  #define sst_tchar char
#endif

#else

#define sst_tchar ...

#endif

#endif
