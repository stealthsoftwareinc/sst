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
#include <sst/catalog/mktemp_d.hpp>
// Include twice to test idempotence.
#include <sst/catalog/mktemp_d.hpp>
//

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/errno_error_string.hpp>
#include <sst/catalog/mkdir_p.hpp>
#include <sst/config.h>

#if 0

//----------------------------------------------------------------------
#elif SST_WITH_POSIX
//----------------------------------------------------------------------

//
// Note that POSIX says mkdtemp will replace "six or more" trailing X
// characters, but in practice, it's not uncommon for implementations to
// always replace exactly six, leaving any additional X's intact. No big
// deal.
//

#include <errno.h>
#include <stdlib.h>

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

#include <unistd.h>

namespace sst {

std::string mktemp_d(std::string && parent) {
  SST_ASSERT((!parent.empty()));
  sst::mkdir_p(parent);
  std::vector<char> v(parent.cbegin(), parent.cend());
  if (v.back() != '/') {
    v.push_back('/');
  }
  char const pattern[] = "tmp.XXXXXXXXXX";
  v.insert(v.end(), pattern, pattern + sizeof(pattern));
  if (::mkdtemp(v.data()) == nullptr) {
    int const e = errno;
    throw std::runtime_error("mkdtemp() failed: " + sst::errno_error_string(e)
                             + ": " + std::string(v.data()));
  }
  v.pop_back();
  parent.clear();
  parent.insert(parent.end(), v.cbegin(), v.cend());
  return std::move(parent);
}

std::string mktemp_d(std::string const & parent) {
  return sst::mktemp_d(std::string(parent));
}

std::string mktemp_d(char const * const parent) {
  SST_ASSERT((parent != nullptr));
  return sst::mktemp_d(std::string(parent));
}

std::string mktemp_d() {
  char const * const parent = std::getenv("TMPDIR");
  if (parent != nullptr && parent[0] != '\0') {
    return sst::mktemp_d(parent);
  }
  return sst::mktemp_d("/tmp");
}

} // namespace sst

//----------------------------------------------------------------------
#elif SST_WITH_WINDOWS_KERNEL32
//----------------------------------------------------------------------

// TODO

//----------------------------------------------------------------------
#endif
