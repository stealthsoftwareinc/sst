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

#ifndef SST_CATALOG_WINDOWS_PATH_REFRESH_FROM_ATTR_HPP
#define SST_CATALOG_WINDOWS_PATH_REFRESH_FROM_ATTR_HPP

#include <sst/catalog/SST_WITH_WINDOWS_KERNEL32.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <windows.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/windows_path.hpp>

namespace sst {

template<class CharT>
windows_path<CharT> &
windows_path<CharT>::refresh_from_attr(void const * const data) {
  SST_ASSERT((!moved_from_));
  if (data == nullptr) {
    have_test_d_ = true;
    test_d_ = false;
    have_test_e_ = true;
    test_e_ = false;
    have_test_f_ = true;
    test_f_ = false;
  } else {
    WIN32_FILE_ATTRIBUTE_DATA const & d =
        *static_cast<WIN32_FILE_ATTRIBUTE_DATA const *>(data);
    have_test_d_ = true;
    test_d_ = !(d.dwFileAttributes & FILE_ATTRIBUTE_DEVICE)
              && (d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
              && !(d.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT);
    have_test_e_ = true;
    test_e_ = true;
    have_test_f_ = true;
    test_f_ = !(d.dwFileAttributes & FILE_ATTRIBUTE_DEVICE)
              && !(d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
              && !(d.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT);
  }
  will_refresh_ = false;
  return *this;
}

} // namespace sst

#endif // #if SST_WITH_WINDOWS_KERNEL32

#endif // #ifndef SST_CATALOG_WINDOWS_PATH_REFRESH_FROM_ATTR_HPP
