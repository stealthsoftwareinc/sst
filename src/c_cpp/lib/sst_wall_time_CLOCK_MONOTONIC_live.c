/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_wall_time_CLOCK_MONOTONIC_live.h>
#include <sst/sst_wall_time_CLOCK_MONOTONIC_live.h>

#include <sst/SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC.h>
#if SST_HAVE_SST_WALL_CLOCK_CLOCK_MONOTONIC

unsigned int const sst_wall_time_CLOCK_MONOTONIC_live = (unsigned int)0xB15CB0A1U;

#endif

typedef int prevent_an_empty_translation_unit;
