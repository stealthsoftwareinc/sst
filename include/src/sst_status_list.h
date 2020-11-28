/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_STATUS_LIST_H
#define SRC_SST_STATUS_LIST_H

/* begin_includes */

#include <src/sst_status_item_ut.h>
#include <src/sst_status_item.h>
#include <sst/catalog/SST_PUBLIC_C_OBJECT.h>
#include <sst/SST_STATUS_MAXVAL.h>

/* end_includes */

SST_PUBLIC_C_OBJECT sst_status_item const sst_status_list[SST_STATUS_MAXVAL + 1];

#endif
