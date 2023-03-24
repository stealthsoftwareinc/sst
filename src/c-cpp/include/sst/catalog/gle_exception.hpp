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

#ifndef SST_CATALOG_GLE_EXCEPTION_HPP
#define SST_CATALOG_GLE_EXCEPTION_HPP

#include <sst/config.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <string>

#include <sst/private/SST_DLL_EXPORT.h>
#include <sst/catalog/error_code_exception.hpp>
#include <sst/catalog/sst_w32_DWORD.h>

namespace sst {

namespace guts {
namespace gle_exception {

using code_t = sst_w32_DWORD;

struct SST_DLL_EXPORT code_to_string final {
  std::string operator()(code_t const code) const;
};

struct SST_DLL_EXPORT default_code final {
  code_t operator()() const;
};

using base =
    sst::error_code_exception<code_t, code_to_string, default_code>;

} // namespace gle_exception
} // namespace guts

extern template class SST_DLL_EXPORT error_code_exception<
    sst::guts::gle_exception::code_t,
    sst::guts::gle_exception::code_to_string,
    sst::guts::gle_exception::default_code>;

class SST_DLL_EXPORT gle_exception
    : public sst::guts::gle_exception::base {

public:
  using sst::guts::gle_exception::base::base;
};

} // namespace sst

#endif // #if SST_WITH_WINDOWS_KERNEL32

#endif // #ifndef SST_CATALOG_GLE_EXCEPTION_HPP
