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
#include <sst/catalog/windows_bcrypt_rng_core.hpp>
// Include twice to test idempotence.
#include <sst/catalog/windows_bcrypt_rng_core.hpp>
//

#include <sst/config.h>

#if SST_WITH_WINDOWS_BCRYPT

#include <cstddef>
#include <stdexcept>

#include <windows.h>

#include <bcrypt.h>
#include <ntdef.h>

namespace sst {

windows_bcrypt_rng_core::windows_bcrypt_rng_core()
    : windows_bcrypt_rng_core(1024) {
}

std::size_t windows_bcrypt_rng_core::buffer_size() const noexcept {
  return buffer_size_;
}

void windows_bcrypt_rng_core::read(unsigned char * const dst,
                                   read_size_t const n) {
  if (n > 0) {
    NTSTATUS const s = BCryptGenRandom(nullptr,
                                       dst,
                                       n,
                                       BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (!NT_SUCCESS(s)) {
      // TODO: Add more error information. We should have a system for
      //       converting NTSTATUS values into error messages.
      throw std::runtime_error("BCryptGenRandom() failed");
    }
  }
}

} // namespace sst

#endif // #if SST_WITH_WINDOWS_BCRYPT
