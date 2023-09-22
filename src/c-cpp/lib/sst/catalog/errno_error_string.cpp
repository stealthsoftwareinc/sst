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
#include <sst/catalog/errno_error_string.hpp>
// Include twice to test idempotence.
#include <sst/catalog/errno_error_string.hpp>
//

#include <sst/catalog/c_locale.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/config.h>

#if 0

//----------------------------------------------------------------------
#elif SST_WITH_POSIX
//----------------------------------------------------------------------

#include <errno.h>
#include <string.h>

#include <string>
#include <type_traits>

#include <sst/catalog/SST_WITH_MACOS.h>

// TODO: These should maybe come from ./configure.
#define WITH_STRERROR_L (!SST_WITH_MACOS)
#define WITH_STRERROR_R 1

#if WITH_STRERROR_L

namespace sst {

std::string errno_error_string(int const code) {
  std::string s;
  char const * const p = strerror_l(code, sst::c_locale());
  if (p != nullptr) {
    s += p;
  } else {
    s += "Unknown error";
  }
  s += " (errno error code ";
  s += sst::to_string(code);
  s += ")";
  return s;
}

} // namespace sst

#elif WITH_STRERROR_R

namespace {

//
// Macro checks recommended by various strerror_r man pages tend to be
// insufficient to portably determine whether we have the POSIX variant
// or the GNU variant of strerror_r. Instead, we use SFINAE to inspect
// the return type. If we were writing this in C instead of C++, a
// ./configure check might be the right approach.
//

// POSIX variant
template<class T = decltype(strerror_r(0, 0, 0)),
         sst::enable_if_t<std::is_same<T, int>::value> = 0>
char const *
my_strerror_r(int const code, char * const buf, size_t const n) {
  return static_cast<T>(strerror_r(code, buf, n)) == 0 ? buf : nullptr;
}

// GNU variant
template<class T = decltype(strerror_r(0, 0, 0)),
         sst::enable_if_t<std::is_same<T, char *>::value> = 0>
char const *
my_strerror_r(int const code, char * const buf, size_t const n) {
  return static_cast<T>(strerror_r(code, buf, n));
}

} // namespace

namespace sst {

std::string errno_error_string(int const code) {
  std::string s;
  char buf[1024];
  char const * const p = my_strerror_r(code, buf, sizeof(buf));
  if (p != nullptr) {
    s += p;
  } else {
    s += "Unknown error";
  }
  s += " (errno error code ";
  s += sst::to_string(code);
  s += ")";
  return s;
}

} // namespace sst

#else

namespace sst {

std::string errno_error_string(int const code) {
  std::string s;
  char const * const p = strerror(code);
  if (p != nullptr) {
    s += p;
  } else {
    s += "Unknown error";
  }
  s += " (errno error code ";
  s += sst::to_string(code);
  s += ")";
  return s;
}

} // namespace sst

#endif

//----------------------------------------------------------------------
#elif SST_WITH_WINDOWS_KERNEL32
//----------------------------------------------------------------------

#include <errno.h>
#include <string.h>

#include <string>

namespace sst {

std::string errno_error_string(int const code) {
  std::string s;
  char buf[1024];
  if (strerror_s(buf, sizeof(buf), code) == 0) {
    s += buf;
  } else {
    s += "Unknown error";
  }
  s += " (errno error code ";
  s += sst::to_string(code);
  s += ")";
  return s;
}

} // namespace sst

//----------------------------------------------------------------------
#endif

namespace sst {

std::string errno_error_string() {
  return sst::errno_error_string(errno);
}

} // namespace sst
