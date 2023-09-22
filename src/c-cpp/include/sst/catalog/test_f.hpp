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

#ifndef SST_CATALOG_TEST_F_HPP
#define SST_CATALOG_TEST_F_HPP

#undef SST_f

//----------------------------------------------------------------------

#ifndef SST_f
#include <sst/catalog/SST_WITH_POSIX.h>
#if SST_WITH_POSIX
#include <sst/catalog/posix_test_f.hpp>
#define SST_f sst::posix_test_f
#endif
#endif

//----------------------------------------------------------------------

#ifndef SST_f
#include <sst/catalog/SST_WITH_WINDOWS_KERNEL32.h>
#if SST_WITH_WINDOWS_KERNEL32
#include <sst/catalog/windows_test_f.hpp>
#define SST_f sst::windows_test_f
#endif
#endif

//----------------------------------------------------------------------

#ifdef SST_f

#include <utility>

#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/SST_NOEXCEPT.hpp>
#include <sst/catalog/enable_if_t.hpp>

namespace sst {

#define SST_r (SST_f(std::forward<Args>(args)...))

template<class... Args,
         sst::enable_if_t<
             SST_COMPILES(SST_f(std::declval<Args &&>()...))> = 0>
SST_NODISCARD()
constexpr auto test_f(Args &&... args) SST_NOEXCEPT(noexcept(SST_r))
    -> decltype(SST_r) {
  return SST_r;
}

#undef SST_r

} // namespace sst

#undef SST_f

#endif

//----------------------------------------------------------------------

#endif // SST_CATALOG_TEST_F_HPP
