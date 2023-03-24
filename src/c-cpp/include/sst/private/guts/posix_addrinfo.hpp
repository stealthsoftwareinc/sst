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

#ifndef SST_PRIVATE_GUTS_POSIX_ADDRINFO_HPP
#define SST_PRIVATE_GUTS_POSIX_ADDRINFO_HPP

#include <sst/config.h>

#if SST_WITH_POSIX

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/private/guts/addrinfo_common.hpp>
#include <sst/private/guts/posix_sockaddr.hpp>

namespace sst {
namespace guts {

class SST_DLL_EXPORT posix_addrinfo
    : guts::addrinfo_common<guts::posix_sockaddr> {

  using base = guts::addrinfo_common<guts::posix_sockaddr>;

public:

  //--------------------------------------------------------------------
  // Inherited members
  //--------------------------------------------------------------------

  using address_t = typename base::address_t;

  using base::address;
  using base::family;
  using base::native;
  using base::native_family;
  using base::native_protocol;
  using base::native_size;
  using base::native_socktype;
  using base::protocol;
  using base::socktype;

  //--------------------------------------------------------------------
  // posix_addrinfo-xp7uf766
  //--------------------------------------------------------------------

  explicit posix_addrinfo(void const * info,
                          bool service_was_null = false);

  //--------------------------------------------------------------------
};

//----------------------------------------------------------------------
// explicit-p54mmp9p
//----------------------------------------------------------------------

extern template class SST_DLL_EXPORT
    addrinfo_common<guts::posix_sockaddr>;

//----------------------------------------------------------------------

} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // #ifndef SST_PRIVATE_GUTS_POSIX_ADDRINFO_HPP
