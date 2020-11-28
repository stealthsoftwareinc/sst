/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * Verifies that the
 * <code>SST_HAVE_AES_NI.h</code>
 * header can be included multiple times and before any other headers.
 */

#include <sst/SST_HAVE_AES_NI.h>
#include <sst/SST_HAVE_AES_NI.h>

#ifndef SST_DOXYGEN

typedef int prevent_an_empty_translation_unit;

#endif
