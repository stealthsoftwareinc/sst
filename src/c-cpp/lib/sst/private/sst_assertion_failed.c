//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

// Include first to test independence.
#include <sst/private/sst_assertion_failed.h>
// Include twice to test idempotence.
#include <sst/private/sst_assertion_failed.h>
//

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <sst/private/sst_find_assertion_condition_length.h>

void sst_assertion_failed(char const * const file,
                          unsigned long const line,
                          char const * const argstr,
                          char const * const message) {
  if (argstr != NULL && message == NULL) {
    // In this case, argstr may include a second argument, which we
    // don't want to output. For example, SST_ASSERT(0, NULL) will set
    // argstr to "0, NULL", for which we only want to output "0". The
    // sst_find_assert_condition_length function resolves this.
    size_t const length = sst_find_assertion_condition_length(argstr);
    // We generally want to output the message using as few stdio calls
    // as possible to reduce the risk of concurrent output becoming
    // interleaved.
    if (length <= (unsigned int)INT_MAX) {
      (void)fprintf(stderr,
                    "%s:%lu: Assertion failed: %.*s.\n",
                    file != NULL ? file : "Unknown",
                    line,
                    (int)length,
                    argstr);
    } else {
      (void)fprintf(stderr,
                    "%s:%lu: Assertion failed: ",
                    file != NULL ? file : "Unknown",
                    line);
      (void)fwrite(argstr, 1, length, stderr);
      (void)fputs(".\n", stderr);
    }
  } else {
    (void)fprintf(stderr,
                  "%s:%lu: Assertion failed: %s.\n",
                  file != NULL ? file : "Unknown",
                  line,
                  message != NULL ? message :
                  argstr != NULL  ? argstr :
                                    "Unknown");
  }
  (void)fflush(stderr);
  abort();
}
