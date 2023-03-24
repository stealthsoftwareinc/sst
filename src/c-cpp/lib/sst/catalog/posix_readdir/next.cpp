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

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/errno_exception.hpp>

namespace sst {

bool posix_readdir::next() {
  SST_ASSERT((dir_ != nullptr));
  if (done_) {
    return false;
  }
  errno = 0;
  auto const ent = ::readdir(static_cast<DIR *>(dir_));
  if (ent != nullptr) {
    ent_ = ent;
    return true;
  }
  int const e = errno;
  if (e != 0) {
    throw sst::errno_exception("readdir()", e);
  }
  ent_ = nullptr;
  done_ = true;
  return false;
}

} // namespace sst

#endif // #if SST_WITH_POSIX
