/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_STATUS_ITEM_UT_H
#define SRC_SST_STATUS_ITEM_UT_H

#include <sst/sst_status.h>

struct sst_status_item_ut {
  char const * name;
  sst_status value;

  char const * ec;

};

typedef struct sst_status_item_ut sst_status_item_ut;

#endif
