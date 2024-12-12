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
#include <sst/private/guts/windows_addrinfo.hpp>
// Include twice to test idempotence.
#include <sst/private/guts/windows_addrinfo.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/sst_w32_ADDRINFOA.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrap.h>
#include <sst/catalog/sst_w32_ADDRINFOA_wrapper.h>

namespace sst {
namespace guts {

namespace {

sst_w32_ADDRINFOA_wrapper wrap(sst_w32_ADDRINFOA const * const info) {
  SST_ASSERT((info != nullptr));
  sst_w32_ADDRINFOA_wrapper wrapper;
  sst_w32_ADDRINFOA_wrap(info, &wrapper);
  return wrapper;
}

} // namespace

windows_addrinfo::windows_addrinfo(void const * const info,
                                   bool const service_was_null)
    : windows_addrinfo(
        info,
        wrap(static_cast<sst_w32_ADDRINFOA const *>(info)),
        service_was_null) {
}

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32
