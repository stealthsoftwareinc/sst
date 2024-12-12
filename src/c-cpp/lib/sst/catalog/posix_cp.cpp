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
#include <sst/catalog/posix_cp.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_cp.hpp>
//

#include <sst/config.h>

#if SST_WITH_POSIX

#include <errno.h>
#include <stdio.h>

#include <cstring>
#include <stdexcept>

#include <sys/stat.h>
#include <sys/types.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/cp_options.hpp>
#include <sst/catalog/errno_exception.hpp>
#include <sst/catalog/mkdir.hpp>
#include <sst/catalog/posix_readdir.hpp>
#include <sst/catalog/size_max_v.hpp>

namespace sst {

namespace {

void my_stat(char const * const f,
             struct ::stat & f_stat,
             bool * const f_exists = nullptr) {
  SST_ASSERT((f != nullptr));
  struct ::stat x;
  if (::stat(f, &x) == 0) {
    f_stat = x;
    if (f_exists != nullptr) {
      *f_exists = true;
    }
  } else {
    int const e = errno;
    if (f_exists == nullptr || e != ENOENT) {
      throw sst::errno_exception("stat() failed on " + sst::c_quote(f),
                                 e);
    }
    *f_exists = false;
  }
}

void my_lstat(char const * const f,
              struct ::stat & f_stat,
              bool * const f_exists = nullptr) {
  SST_ASSERT((f != nullptr));
  struct ::stat x;
  if (::lstat(f, &x) == 0) {
    f_stat = x;
    if (f_exists != nullptr) {
      *f_exists = true;
    }
  } else {
    int const e = errno;
    if (f_exists == nullptr || e != ENOENT) {
      throw sst::errno_exception("lstat() failed on " + sst::c_quote(f),
                                 e);
    }
    *f_exists = false;
  }
}

void adjust_dst(char const * const src,
                char const *& dst,
                struct ::stat & dst_stat,
                bool & dst_exists,
                std::string & dst_buf) {
  SST_ASSERT((src != nullptr));
  SST_ASSERT((dst != nullptr));
  std::size_t i = sst::size_max_v;
  std::size_t j = 0;
  std::size_t k;
  for (k = 0; src[k] != '\0'; ++k) {
    if (src[k] != '/') {
      if (k == 0 || src[k - 1] == '/') {
        i = k;
      }
      j = k;
    }
  }
  if (i >= k || (j - i < 2 && src[i] == '.' && src[j] == '.')) {
    throw std::runtime_error("Path does not have a copiable basename: "
                             + sst::c_quote(src) + ".");
  }
  dst_buf = dst;
  if (dst_buf.back() != '/') {
    dst_buf += '/';
  }
  dst_buf.insert(dst_buf.end(), src + i, src + j + 1);
  dst = dst_buf.c_str();
  my_lstat(dst, dst_stat, &dst_exists);
}

bool same_file(struct ::stat const & a,
               struct ::stat const & b) noexcept {
  return a.st_dev == b.st_dev && a.st_ino == b.st_ino;
}

void copy_file(char const * const src, char const * const dst) {
  SST_ASSERT((src != nullptr));
  SST_ASSERT((dst != nullptr));
  FILE * src_f = ::fopen(src, "rb");
  if (src_f == nullptr) {
    int const e = errno;
    throw sst::errno_exception("Error opening file " + sst::c_quote(src)
                                   + " for reading",
                               e);
  }
  try {
    FILE * dst_f = ::fopen(dst, "wb");
    if (dst_f == nullptr) {
      int const e = errno;
      throw sst::errno_exception(
          "Error opening file " + sst::c_quote(dst) + " for writing",
          e);
    }
    try {
      unsigned char buf[BUFSIZ];
      static_cast<void>(::setvbuf(src_f, nullptr, _IONBF, 0));
      static_cast<void>(::setvbuf(dst_f, nullptr, _IONBF, 0));
      while (true) {
        size_t const src_n = ::fread(buf, 1, sizeof(buf), src_f);
        if (src_n < sizeof(buf) && ::ferror(src_f)) {
          int const e = errno;
          throw sst::errno_exception("Error while reading from file "
                                         + sst::c_quote(src),
                                     e);
        }
        size_t const dst_n = ::fwrite(buf, 1, src_n, dst_f);
        if (dst_n < src_n) {
          int const e = errno;
          throw sst::errno_exception("Error while writing to file "
                                         + sst::c_quote(dst),
                                     e);
        }
        if (src_n < sizeof(buf)) {
          break;
        }
      }
      static_cast<void>(::fclose(src_f));
      src_f = nullptr;
      if (::fclose(dst_f) != 0) {
        dst_f = nullptr;
        int const e = errno;
        throw sst::errno_exception("Error while writing to file "
                                       + sst::c_quote(dst),
                                   e);
      }
      dst_f = nullptr;
    } catch (...) {
      if (dst_f != nullptr) {
        static_cast<void>(::fclose(dst_f));
      }
      throw;
    }
  } catch (...) {
    if (src_f != nullptr) {
      static_cast<void>(::fclose(src_f));
    }
    throw;
  }
}

} // namespace

void posix_cp(char const * const src,
              char const * dst,
              sst::cp_options const & options) {
  SST_ASSERT((src != nullptr));
  SST_ASSERT((dst != nullptr));
  struct ::stat src_stat;
  if (options.follow_links()) {
    my_stat(src, src_stat);
  } else {
    my_lstat(src, src_stat);
  }
  struct ::stat dst_stat;
  bool dst_exists;
  my_lstat(dst, dst_stat, &dst_exists);
  std::string dst_buf;
  if (S_ISREG(src_stat.st_mode)) {
    if (dst_exists) {
      if (S_ISLNK(dst_stat.st_mode)) {
        my_stat(dst, dst_stat, &dst_exists);
      }
      if (dst_exists) {
        if (S_ISDIR(dst_stat.st_mode)) {
          adjust_dst(src, dst, dst_stat, dst_exists, dst_buf);
          if (dst_exists && S_ISLNK(dst_stat.st_mode)) {
            my_stat(dst, dst_stat, &dst_exists);
          }
        }
        if (dst_exists) {
          if (!S_ISREG(dst_stat.st_mode)) {
            throw std::runtime_error(
                "File " + sst::c_quote(src)
                + " cannot be copied onto non-file " + sst::c_quote(dst)
                + ".");
          }
          if (same_file(src_stat, dst_stat)) {
            return;
          }
        }
      }
    }
    copy_file(src, dst);
  } else if (S_ISDIR(src_stat.st_mode)) {
    if (!options.recursive()) {
      throw std::runtime_error(
          "sst::cp: Refusing to copy directory " + sst::c_quote(src)
          + " because options.recursive() is false.");
    }
    if (dst_exists) {
      if (S_ISLNK(dst_stat.st_mode)) {
        my_stat(dst, dst_stat);
      }
      if (!S_ISDIR(dst_stat.st_mode)) {
        throw std::runtime_error(
            "Directory " + sst::c_quote(src)
            + (options.contents() ? " contents " : "")
            + " cannot be copied into non-directory "
            + sst::c_quote(dst) + ".");
      }
      if (same_file(src_stat, dst_stat)) {
        if (!options.contents()) {
          throw std::runtime_error("Directory " + sst::c_quote(src)
                                   + " cannot be copied into itself.");
        }
        return;
      }
      if (!options.contents()) {
        adjust_dst(src, dst, dst_stat, dst_exists, dst_buf);
        if (dst_exists) {
          if (S_ISLNK(dst_stat.st_mode)) {
            my_stat(dst, dst_stat);
          }
          if (!S_ISDIR(dst_stat.st_mode)) {
            throw std::runtime_error(
                "Directory " + sst::c_quote(src)
                + " contents cannot be copied into non-directory "
                + sst::c_quote(dst) + ".");
          }
          if (same_file(src_stat, dst_stat)) {
            return;
          }
        } else {
          sst::mkdir(dst);
        }
      }
    } else {
      sst::mkdir(dst);
    }
    std::string src_buf(src);
    if (src_buf.back() != '/') {
      src_buf += '/';
    }
    auto const n = src_buf.size();
    sst::posix_readdir child(src);
    sst::cp_options options2 = options;
    options2.contents(false);
    while (child.next()) {
      if (std::strcmp(child.name(), ".") != 0
          && std::strcmp(child.name(), "..") != 0) {
        src_buf.resize(n);
        src_buf += child.name();
        sst::posix_cp(src_buf, dst, options2);
      }
    }
  } else {
    SST_THROW_UNIMPLEMENTED();
  }
}

} // namespace sst

#endif // #if SST_WITH_POSIX
