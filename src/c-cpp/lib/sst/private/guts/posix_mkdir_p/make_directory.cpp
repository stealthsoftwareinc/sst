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
#include <sst/private/guts/posix_mkdir_p.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/posix_mkdir_p.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <errno.h>

#include <stdexcept>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/errno_exception.hpp>

namespace sst {
namespace guts {
namespace posix_mkdir_p {

bool make_directory(char const * const path) {
  SST_ASSERT((path != nullptr));
  if (::mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == 0) {
    return true;
  }
  {
    int const e = errno;
    if (e != EEXIST) {
      throw sst::errno_exception("mkdir() failed on path "
                                     + sst::c_quote(path),
                                 e);
    }
  }
  {
    struct stat st;
    if (::stat(path, &st) != 0) {
      int const e = errno;
      throw sst::errno_exception("stat() failed on path "
                                     + sst::c_quote(path),
                                 e);
    }
    if (S_ISDIR(st.st_mode)) {
      return false;
    }
  }
  throw std::runtime_error(
      "Cannot create directory " + sst::c_quote(path)
      + " because it already exists as a non-directory");
}

} // namespace posix_mkdir_p
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX
