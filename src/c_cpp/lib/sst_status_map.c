/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <src/sst_status_map.h>
#include <src/sst_status_map.h>

#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/sst_status.h>

sst_status const sst_status_map[SST_STATUS_MAXVAL + 1] = {
  #include <src/sst_status_map.inc>
};
