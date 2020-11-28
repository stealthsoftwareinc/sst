/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_jlongptr_to_ptr.h>
#include <sst/sst_jlongptr_to_ptr.h>

#include <sst/SST_HAVE_SST_JLONGPTR_TO_PTR.h>
#if SST_HAVE_SST_JLONGPTR_TO_PTR

#include <sst/sst_jlongptr.h>
#include <stdint.h>

void * (sst_jlongptr_to_ptr)(
  sst_jlongptr const p
) {
  return (void *)(intptr_t)p;
}

#endif

typedef int prevent_an_empty_translation_unit;
