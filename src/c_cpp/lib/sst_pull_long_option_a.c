/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_pull_long_option_a.h>
#include <sst/sst_pull_long_option_a.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_is_long_option_a.h>
#include <sst/sst_is_unvalued_long_option_a.h>
#include <sst/sst_is_unvalued_option_a.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_pull_long_option_a)(
  char * * const argv,
  char const * const * const otrv,
  char const * const * const otp
) {
  if (argv == NULL) {
    return SST_FALSE;
  }
  {
    char * * p = argv;
    for (;;) {
      if (*p == NULL) {
        return SST_FALSE;
      }
      if (otp == NULL) {
        if (sst_is_long_option_a(*p, NULL)) {
          break;
        }
      } else {
        {
          char const * const * q;
          for (q = otp; *q != NULL; ++q) {
            if (sst_is_long_option_a(*p, *q)) {
              break;
            }
          }
          if (*q != NULL) {
            break;
          }
        }
        if (otrv != NULL) {
          char const * const * q;
          for (q = otrv; *q != NULL; ++q) {
            if (sst_is_unvalued_option_a(*p, *q)) {
              break;
            }
          }
          if (*q != NULL) {
            ++p;
            if (*p == NULL) {
              return SST_FALSE;
            }
          }
        }
      }
      ++p;
    }
    if (p != argv) {
      sst_bool pull_two_arguments = SST_FALSE;
      if (otrv != NULL) {
        char const * const * q;
        for (q = otrv; *q != NULL; ++q) {
          if (sst_is_unvalued_long_option_a(*p, *q)) {
            pull_two_arguments = SST_TRUE;
            break;
          }
        }
      }
      if (pull_two_arguments) {
        char * const a0 = p[0];
        char * const a1 = p[1];
        while (p != argv) {
          --p;
          p[2] = p[0];
        }
        argv[0] = a0;
        argv[1] = a1;
      } else {
        char * const a0 = p[0];
        while (p != argv) {
          --p;
          p[1] = p[0];
        }
        argv[0] = a0;
      }
    }
  }
  return SST_TRUE;
}
