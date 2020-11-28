/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Verifies that the
 * <code>sst_status_item_ut.h</code>
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

#include <src/sst_status_item_ut.h>
#include <src/sst_status_item_ut.h>

#ifndef SST_DOXYGEN

typedef int prevent_an_empty_translation_unit;

#endif
