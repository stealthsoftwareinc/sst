//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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
#include <sst/private/guts/posix_test_e.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/posix_test_e.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <errno.h>

#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/errno_exception.hpp>

namespace sst {
namespace guts {

bool posix_test_e(char const * const path, bool const follow_links) {
  SST_ASSERT((path != nullptr));
  struct stat st;
  int const s = follow_links ? ::stat(path, &st) : ::lstat(path, &st);
  if (s == 0) {
    return true;
  }
  int const e = errno;
  if (e == ENOENT || e == ENOTDIR) {
    return false;
  }
  throw sst::errno_exception((follow_links ? "stat" : "lstat")
                                 + std::string("() failed on ")
                                 + sst::c_quote(path),
                             e);
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
