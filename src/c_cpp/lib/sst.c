/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Verifies that the
 * <code>sst.h</code>
 * header can be included multiple times and before any other headers.
 *
 * @since SST&nbsp;0.1.0 (2016-05-11)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#include <sst.h>
#include <sst.h>

#ifndef SST_DOXYGEN

typedef int prevent_an_empty_translation_unit;

#endif
