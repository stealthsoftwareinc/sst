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
#include <sst/catalog/posix_readdir.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_readdir.hpp>
//

#include <sst/config.h>

#if SST_WITH_POSIX

#include <errno.h>

#include <dirent.h>
#include <sys/types.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/errno_exception.hpp>

namespace sst {

posix_readdir::posix_readdir(char const * const dir) {
  SST_ASSERT((dir != nullptr));
  dir_ = ::opendir(dir);
  if (dir_ == nullptr) {
    int const e = errno;
    throw sst::errno_exception("opendir() failed on path "
                                   + sst::c_quote(dir),
                               e);
  }
}

} // namespace sst

#endif // #if SST_WITH_POSIX
