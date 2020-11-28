/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/sst_pull_option_w.h>
#include <sst/sst_pull_option_w.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_is_option_w.h>
#include <sst/sst_is_unvalued_option_w.h>
#include <stddef.h>

/* end_includes */

sst_bool (sst_pull_option_w)(
  wchar_t * * const argv,
  wchar_t const * const * const otrv,
  wchar_t const * const * const otp
) {
  if (argv == NULL) {
    return SST_FALSE;
  }
  {
    wchar_t * * p = argv;
    for (;;) {
      if (*p == NULL) {
        return SST_FALSE;
      }
      if (otp == NULL) {
        if (sst_is_option_w(*p, NULL)) {
          break;
        }
      } else {
        {
          wchar_t const * const * q;
          for (q = otp; *q != NULL; ++q) {
            if (sst_is_option_w(*p, *q)) {
              break;
            }
          }
          if (*q != NULL) {
            break;
          }
        }
        if (otrv != NULL) {
          wchar_t const * const * q;
          for (q = otrv; *q != NULL; ++q) {
            if (sst_is_unvalued_option_w(*p, *q)) {
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
        wchar_t const * const * q;
        for (q = otrv; *q != NULL; ++q) {
          if (sst_is_unvalued_option_w(*p, *q)) {
            pull_two_arguments = SST_TRUE;
            break;
          }
        }
      }
      if (pull_two_arguments) {
        wchar_t * const a0 = p[0];
        wchar_t * const a1 = p[1];
        while (p != argv) {
          --p;
          p[2] = p[0];
        }
        argv[0] = a0;
        argv[1] = a1;
      } else {
        wchar_t * const a0 = p[0];
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
