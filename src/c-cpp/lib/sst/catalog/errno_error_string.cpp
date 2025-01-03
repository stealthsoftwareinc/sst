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
#include <sst/catalog/errno_error_string.hpp>
// Include twice to test idempotence.
#include <sst/catalog/errno_error_string.hpp>
//

#include <sst/catalog/SST_MAYBE_UNUSED.h>
#include <sst/catalog/c_locale.hpp>
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
// unreliable for determining whether we have the POSIX variant or the
// GNU variant of strerror_r. To resolve this, we simply use function
// overloading to distinguish the return type and convert the return
// value to the GNU variant. If we were writing this in C instead of
// C++, a ./configure check would probably be the best approach.
//

SST_MAYBE_UNUSED()
char const * to_gnu(int const r, char const * const buf) {
  return r == 0 ? buf : nullptr;
}

SST_MAYBE_UNUSED()
char const * to_gnu(char const * const r, char const *) {
  return r;
}

} // namespace

namespace sst {

std::string errno_error_string(int const code) {
  std::string s;
  char buf[1024];
  auto const r = strerror_r(code, buf, sizeof(buf));
  char const * const p = to_gnu(r, buf);
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
