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

#ifndef SST_PRIVATE_GUTS_WINDOWS_SOCKADDR_HPP
#define SST_PRIVATE_GUTS_WINDOWS_SOCKADDR_HPP

#include <sst/config.h>

#if SST_WITH_WINDOWS_WS2_32

#include <cstddef>

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/guts/sockaddr_common.hpp>

namespace sst {
namespace guts {

class SST_DLL_EXPORT windows_sockaddr : guts::sockaddr_common {

  using base = guts::sockaddr_common;

public:

  //--------------------------------------------------------------------
  // Inherited members
  //--------------------------------------------------------------------

  using native_t = void;

  using base::family;
  using base::have_ip;
  using base::have_port;
  using base::ip;
  using base::native;
  using base::native_family;
  using base::native_size;
  using base::port;

  //--------------------------------------------------------------------
  // windows_sockaddr-hk5znx62
  //--------------------------------------------------------------------

  explicit windows_sockaddr(void const * address,
                            std::size_t address_size,
                            bool service_was_null = false);

  //--------------------------------------------------------------------

  bool operator==(windows_sockaddr const & other) const {
    return base::operator==(other);
  }

  //--------------------------------------------------------------------
  // native_family-xr04fbf0
  //--------------------------------------------------------------------

  static int native_family(void const * address);

  //--------------------------------------------------------------------
  // native_size_max
  //--------------------------------------------------------------------

  static std::size_t native_size_max() noexcept;

  //--------------------------------------------------------------------
};

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_WINDOWS_WS2_32

#endif // SST_PRIVATE_GUTS_WINDOWS_SOCKADDR_HPP
