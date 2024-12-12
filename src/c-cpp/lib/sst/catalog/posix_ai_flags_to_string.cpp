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
#include <sst/catalog/posix_ai_flags_to_string.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_ai_flags_to_string.hpp>
//

#include <sst/config.h>

#if SST_WITH_POSIX

#include <iterator>
#include <string>

#include <netdb.h>

#include <sst/catalog/int_max_v.hpp>
#include <sst/catalog/integer_to_string_options.hpp>
#include <sst/catalog/to_string.hpp>

namespace sst {

std::string posix_ai_flags_to_string(int const flags) {
  std::string s;

  int known = 0;

#define F(x)                                                           \
  ([&] {                                                               \
    if (flags & x) {                                                   \
      if (!s.empty()) {                                                \
        s += " | ";                                                    \
      }                                                                \
      s += #x;                                                         \
    }                                                                  \
    known |= x;                                                        \
  }())

  F(AI_ADDRCONFIG);
  F(AI_ALL);
  F(AI_CANONNAME);
  F(AI_NUMERICHOST);
  F(AI_NUMERICSERV);
  F(AI_PASSIVE);
  F(AI_V4MAPPED);

#undef F

  int const unknown = flags & (sst::int_max_v ^ known);
  if (unknown) {
    if (!s.empty()) {
      s += " | ";
    }
    sst::to_string(
        unknown,
        std::back_inserter(s),
        sst::integer_to_string_options().base(16).prefix(true));
  }

  if (s.empty()) {
    s = "0";
  }

  return s;
}

} // namespace sst

#endif // #if SST_WITH_POSIX
