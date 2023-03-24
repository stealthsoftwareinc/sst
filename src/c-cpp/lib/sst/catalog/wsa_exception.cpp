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
#include <sst/catalog/wsa_exception.hpp>
// Include twice to test idempotence.
#include <sst/catalog/wsa_exception.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <string>

#include <sst/catalog/sst_w32_WSAGetLastError.h>
#include <sst/catalog/wsa_error_string.hpp>

namespace sst {

namespace guts {
namespace wsa_exception {

std::string code_to_string::operator()(code_t const code) const {
  return sst::wsa_error_string(code);
}

code_t default_code::operator()() const {
  return sst_w32_WSAGetLastError();
}

} // namespace wsa_exception
} // namespace guts

template class error_code_exception<
    sst::guts::wsa_exception::code_t,
    sst::guts::wsa_exception::code_to_string,
    sst::guts::wsa_exception::default_code>;

} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
