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
#include <sst/catalog/wsa_error_string.hpp>
// Include twice to test idempotence.
#include <sst/catalog/wsa_error_string.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <string>

#include <windows.h>

#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/catalog/windows_langid.hpp>

namespace sst {

std::string wsa_error_string(int const code) {
  std::string s;
  char buf[1024] = {0};
  DWORD const r =
      FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
                     nullptr,
                     sst::checked_cast<DWORD>(code),
                     static_cast<LANGID>(windows_langid::en_us),
                     buf,
                     sizeof(buf) - 1,
                     nullptr);
  if (r != 0) {
    s += buf;
    while (!s.empty() && (s.back() == '\n' || s.back() == '\r')) {
      s.pop_back();
    }
    if (!s.empty() && s.back() == '.') {
      s.pop_back();
    }
  } else {
    s += "Unknown error";
  }
  s += " (Windows Sockets error code ";
  s += sst::to_string(code);
  s += ")";
  return s;
}

} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
