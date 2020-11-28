/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/**
 * @file
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SRC_SST_STATUS_MAP_H
#define SRC_SST_STATUS_MAP_H

/* begin_includes */

#include <sst/catalog/SST_PUBLIC_C_OBJECT.h>
#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/sst_status.h>

/* end_includes */

/**
 *
 * @available
 * always
 *
 * @since SST&nbsp;X.X.X (XXXX-XX-XX)
 *
 * @examples
 * none
 *
 * @notablechanges
 * none
 */

#ifndef SST_DOXYGEN

SST_PUBLIC_C_OBJECT sst_status const sst_status_map[SST_STATUS_MAXVAL + 1];

#else

extern sst_status const sst_status_map[SST_STATUS_MAXVAL + 1];

#endif

#endif
