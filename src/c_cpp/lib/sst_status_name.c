/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_status_name.h>
#include <sst/sst_status_name.h>

#include <src/sst_status_item_ut.h>
#include <src/sst_status_item.h>
#include <src/sst_status_list.h>
#include <src/sst_status_map.h>
#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/SST_UNKNOWN.h>
#include <sst/sst_status.h>

char const * (sst_status_name)(
  sst_status const s
) {
  if (s > SST_STATUS_MAXVAL) {
    return (sst_status_name)(SST_UNKNOWN);
  }
  return sst_status_list[sst_status_map[s]].name;
}
