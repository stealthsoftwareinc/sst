/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Verifies that the
 * <code>sst_wall_clock.h</code>
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

#include <sst/sst_wall_clock.h>
#include <sst/sst_wall_clock.h>

#ifndef SST_DOXYGEN

typedef int prevent_an_empty_translation_unit;

#endif
