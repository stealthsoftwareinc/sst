/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/* begin_includes */

#include <src/sst_status_item.h>
#include <src/sst_status_item_ut.h>
#include <src/sst_status_list.h>
#include <sst/SST_STATUS_MAXVAL.h>
#include <sst/sst_status.h>
#include <stdio.h>
#include <stdlib.h>

/* end_includes */

int (main)(
  void
) {
  {
    sst_status i;
    for (i = 0; i != SST_STATUS_MAXVAL + 1; ++i) {
      sst_status j;
      for (j = 0; j != SST_STATUS_MAXVAL + 1; ++j) {
        if (sst_status_list[j].value == i) {
          if (printf("%lu,\n", j) < 0) {
            (void)fprintf(stderr,
              "sst_status_map_generator! "
              "error writing to standard output\n"
            );
            return EXIT_FAILURE;
          }
          break;
        }
      }
    }
  }
  if (fflush(stdout) != 0) {
    (void)fprintf(stderr,
      "sst_status_map_generator! "
      "error writing to standard output\n"
    );
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
