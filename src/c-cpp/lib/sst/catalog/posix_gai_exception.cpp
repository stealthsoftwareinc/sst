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
#include <sst/catalog/posix_gai_exception.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_gai_exception.hpp>
//

#include <sst/config.h>

#if SST_WITH_POSIX

#include <string>

#include <netdb.h>

#include <sst/catalog/errno_error_string.hpp>
#include <sst/catalog/posix_gai_error_string.hpp>

namespace sst {

namespace guts {
namespace posix_gai_exception {

std::string code_to_string::operator()(code_t const code) const {
  if (code.first == EAI_SYSTEM) {
    return sst::errno_error_string(code.second);
  }
  return sst::posix_gai_error_string(code.first);
}

} // namespace posix_gai_exception
} // namespace guts

template class error_code_exception<
    guts::posix_gai_exception::code_t,
    guts::posix_gai_exception::code_to_string>;

} // namespace sst

#endif // #if SST_WITH_POSIX
