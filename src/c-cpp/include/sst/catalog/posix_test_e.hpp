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

#ifndef SST_CATALOG_POSIX_TEST_E_HPP
#define SST_CATALOG_POSIX_TEST_E_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_NODISCARD.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/posix_path.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

template<class Path,
         class P = decltype(sst::c_str(std::declval<Path &&>())),
         sst::enable_if_t<
             !std::is_same<sst::remove_cvref_t<Path &&>,
                           sst::posix_path>::value
             && std::is_convertible<P, char const *>::value> = 0>
SST_NODISCARD()
bool posix_test_e(Path && path, bool const follow_links = true) {
  char const * const p = sst::c_str(std::forward<Path>(path));
  SST_ASSERT((p != nullptr));
  return sst::posix_path::wrap(p, follow_links).test_e();
}

SST_NODISCARD()
inline bool posix_test_e(sst::posix_path const & path,
                         bool const follow_links = true) {
  return follow_links == path.follow_links() ?
             path.test_e() :
             sst::posix_test_e(path.c_str(), follow_links);
}

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_CATALOG_POSIX_TEST_E_HPP
