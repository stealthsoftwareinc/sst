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

#ifndef SST_CATALOG_REQUIRE_OPT_HPP
#define SST_CATALOG_REQUIRE_OPT_HPP

#include <string>

#include <sst/catalog/opt_exception.hpp>
#include <sst/catalog/string_to_string_options.hpp>
#include <sst/catalog/to_string.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {

template<class String>
void require_opt(String const & opt, bool const have) {
  if (!have) {
    throw opt_exception(
        "option is required: "
        + sst::to_string(
            opt,
            sst::string_to_string_options().replace_unrepresentable(
                true)));
  }
}

extern template SST_DLL_EXPORT void require_opt(std::string const & opt,
                                                bool have);

extern SST_DLL_EXPORT void require_opt(char const * opt, bool have);

} // namespace sst

#endif // #ifndef SST_CATALOG_REQUIRE_OPT_HPP
