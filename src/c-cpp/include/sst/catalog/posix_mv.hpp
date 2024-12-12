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

#ifndef SST_CATALOG_POSIX_MV_HPP
#define SST_CATALOG_POSIX_MV_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_COMPILES.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/posix_path.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

template<class Src,
         class Dst,
         class P = decltype(sst::c_str(std::declval<Src &&>())),
         sst::enable_if_t<
             !std::is_same<sst::remove_cvref_t<Src &&>,
                           sst::posix_path>::value
             && std::is_convertible<P, char const *>::value
             && SST_COMPILES(
                 sst::posix_path::wrap(std::declval<char const *>())
                     .mv(std::declval<Dst &&>()))> = 0>
void posix_mv(Src && src, Dst && dst) {
  char const * const p = sst::c_str(std::forward<Src>(src));
  SST_ASSERT((p != nullptr));
  sst::posix_path::wrap(p).mv(std::forward<Dst>(dst));
}

template<class Src,
         class Dst,
         sst::enable_if_t<std::is_same<sst::remove_cvref_t<Src &&>,
                                       sst::posix_path>::value
                          && SST_COMPILES(std::declval<Src &&>().mv(
                              std::declval<Dst &&>()))> = 0>
void posix_mv(Src && src, Dst && dst) {
  std::forward<Src>(src).mv(std::forward<Dst>(dst));
}

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_CATALOG_POSIX_MV_HPP
