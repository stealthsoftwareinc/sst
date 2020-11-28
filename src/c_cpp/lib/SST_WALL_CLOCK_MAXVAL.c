/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Verifies that the
 * <code>SST_WALL_CLOCK_MAXVAL.h</code>
 * header can be included multiple times and before any other headers.
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#include <sst/SST_WALL_CLOCK_MAXVAL.h>
#include <sst/SST_WALL_CLOCK_MAXVAL.h>

#ifndef SST_DOXYGEN

typedef int prevent_an_empty_translation_unit;

#endif
