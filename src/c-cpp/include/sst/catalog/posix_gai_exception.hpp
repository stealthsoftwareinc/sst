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

#ifndef SST_CATALOG_POSIX_GAI_EXCEPTION_HPP
#define SST_CATALOG_POSIX_GAI_EXCEPTION_HPP

#include <sst/config.h>

#if SST_WITH_POSIX

#include <utility>

#include <sst/catalog/error_code_exception.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

namespace guts {
namespace posix_gai_exception {

using code_t = std::pair<int, int>;

struct SST_DLL_EXPORT code_to_string final {
  std::string operator()(code_t code) const;
};

using base = sst::error_code_exception<code_t, code_to_string>;

} // namespace posix_gai_exception
} // namespace guts

extern template class SST_DLL_EXPORT
    error_code_exception<guts::posix_gai_exception::code_t,
                         guts::posix_gai_exception::code_to_string>;

struct SST_DLL_EXPORT posix_gai_exception
    : guts::posix_gai_exception::base {
  using guts::posix_gai_exception::base::base;
};

} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // #ifndef SST_CATALOG_POSIX_GAI_EXCEPTION_HPP
