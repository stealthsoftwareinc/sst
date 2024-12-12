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

#ifndef SST_PRIVATE_GUTS_WINDOWS_MKDIR_CORE_HPP
#define SST_PRIVATE_GUTS_WINDOWS_MKDIR_CORE_HPP

#include <string>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/gle_exception.hpp>

namespace sst {
namespace guts {
namespace windows_mkdir {

template<class CharT, class CreateDirectoryFunc>
void core(CharT const * const path,
          CreateDirectoryFunc && CreateDirectory_func,
          char const * const CreateDirectory_name) {
  SST_ASSERT((path != nullptr));
  if (CreateDirectory_func(path, nullptr) == 0) {
    DWORD const e = ::GetLastError();
    throw sst::gle_exception(std::string(CreateDirectory_name)
                                 + "() failed on path "
                                 + sst::c_quote(path),
                             e);
  }
}

} // namespace windows_mkdir
} // namespace guts
} // namespace sst

#endif // SST_PRIVATE_GUTS_WINDOWS_MKDIR_CORE_HPP
