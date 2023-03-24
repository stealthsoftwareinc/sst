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
#include <sst/catalog/rm_f_r.hpp>
// Include twice to test idempotence.
#include <sst/catalog/rm_f_r.hpp>
//

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/errno_error_string.hpp>
#include <sst/config.h>

#if 0

//----------------------------------------------------------------------
#elif SST_WITH_POSIX
//----------------------------------------------------------------------

#include <cstdint>
#include <dirent.h>
#include <errno.h>
#include <stdexcept>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <utility>

#include <sst/catalog/posix_test_d.hpp>

namespace sst {

namespace {

// TODO: Use our existing posix_readdir class.

class dir final {
  DIR * const d_;

public:
  dir(std::string const & path) : d_(opendir(path.c_str())) {
    if (d_ == nullptr) {
      int const e = errno;
      throw std::runtime_error(
          "opendir() failed: " + sst::errno_error_string(e) + ": " + path);
    }
  }

  DIR * get() const noexcept {
    return d_;
  }

  ~dir() noexcept {
    static_cast<void>(closedir(d_));
  }

  dir(dir const &) = delete;
  dir(dir &&) = delete;
  dir & operator=(dir const &) = delete;
  dir & operator=(dir &&) = delete;
};

} // namespace

std::uintmax_t rm_f_r_helper(std::string & path,
                             bool const root_call = true) {
  std::uintmax_t count = 0;
  if (sst::posix_test_d(path, false)) {
    dir const d(path);
    while (true) {
      errno = 0;
      struct dirent const * const x = readdir(d.get());
      if (x == nullptr) {
        int const e = errno;
        if (e != 0) {
          throw std::runtime_error("readdir() failed: "
                                   + sst::errno_error_string(e) + ": "
                                   + path);
        }
        break;
      }
      if (strcmp(x->d_name, ".") != 0 && strcmp(x->d_name, "..") != 0) {
        auto const n = path.size();
        path += '/';
        path += x->d_name;
        count += rm_f_r_helper(path, false);
        path.resize(n);
      }
    }
    if (rmdir(path.c_str()) != 0) {
      int const e = errno;
      throw std::runtime_error("rmdir() failed: " + sst::errno_error_string(e)
                               + ": " + path);
    }
    count += 1;
  } else if (unlink(path.c_str()) == 0) {
    count += 1;
  } else {
    int const e = errno;
    if (!root_call || e != ENOENT) {
      throw std::runtime_error(
          "unlink() failed: " + sst::errno_error_string(e) + ": " + path);
    }
  }
  return count;
}

std::uintmax_t rm_f_r(char const * const path) {
  SST_ASSERT((path != nullptr));
  std::string x(path);
  return rm_f_r_helper(x);
}

std::uintmax_t rm_f_r(std::string const & path) {
  std::string x(path);
  return rm_f_r_helper(x);
}

std::uintmax_t rm_f_r(std::string && path) {
  std::string x(std::move(path));
  return rm_f_r_helper(x);
}

} // namespace sst

//----------------------------------------------------------------------
#elif SST_WITH_WINDOWS_KERNEL32
//----------------------------------------------------------------------

// TODO

//----------------------------------------------------------------------
#endif
