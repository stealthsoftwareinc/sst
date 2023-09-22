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

#ifndef SST_CATALOG_SOCKET_FAMILY_HPP
#define SST_CATALOG_SOCKET_FAMILY_HPP

#include <sst/config.h>

namespace sst {

enum class socket_family {

  //--------------------------------------------------------------------

  unspec,

  //--------------------------------------------------------------------

  inet,

  //--------------------------------------------------------------------

  inet6,

  //--------------------------------------------------------------------
  //
  // We can't use "unix" for AF_UNIX because compilers commonly define
  // "unix" as an object-like macro. We use "local" instead, which is
  // from AF_LOCAL, a common alternative name for AF_UNIX.
  //

  local,

  //--------------------------------------------------------------------

  other,

  //--------------------------------------------------------------------

};

} // namespace sst

#endif // SST_CATALOG_SOCKET_FAMILY_HPP
