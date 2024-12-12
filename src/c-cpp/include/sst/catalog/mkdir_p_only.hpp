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

#ifndef SST_CATALOG_MKDIR_P_ONLY_HPP
#define SST_CATALOG_MKDIR_P_ONLY_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

//----------------------------------------------------------------------

#undef SST_F

#if 0

#elif SST_WITH_POSIX
#include <sst/catalog/posix_mkdir_p_only.hpp>
#define SST_F sst::posix_mkdir_p_only

#endif

//----------------------------------------------------------------------

#ifdef SST_F

namespace sst {

template<class... Args>
bool mkdir_p_only(Args &&... args) {
  return SST_F(std::forward<Args>(args)...);
}

} // namespace sst

#undef SST_F

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_MKDIR_P_ONLY_HPP
