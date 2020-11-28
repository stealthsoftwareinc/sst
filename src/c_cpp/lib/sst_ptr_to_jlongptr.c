/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_ptr_to_jlongptr.h>
#include <sst/sst_ptr_to_jlongptr.h>

#include <sst/SST_HAVE_SST_PTR_TO_JLONGPTR.h>
#if SST_HAVE_SST_PTR_TO_JLONGPTR

#include <sst/sst_jlongptr.h>
#include <stdint.h>

sst_jlongptr (sst_ptr_to_jlongptr)(
  void const * const p
) {
  return (sst_jlongptr)(intptr_t)p;
}

#endif

typedef int prevent_an_empty_translation_unit;
