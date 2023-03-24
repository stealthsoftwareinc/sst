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

#ifndef SST_CATALOG_WINDOWS_PATH_REFRESH_CORE_HPP
#define SST_CATALOG_WINDOWS_PATH_REFRESH_CORE_HPP

#include <sst/catalog/SST_WITH_WINDOWS_KERNEL32.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <string>
#include <vector>

#include <windows.h>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/basic_ptr.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/checked_t.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/gle_exception.hpp>
#include <sst/catalog/unsigned_lt.hpp>
#include <sst/catalog/windows_path.hpp>

namespace sst {

template<class CharT>
template<class GetFileAttributesExFunc,
         class CreateFileFunc,
         class GetFinalPathNameByHandleFunc>
windows_path<CharT> & windows_path<CharT>::refresh_core(
    GetFileAttributesExFunc && GetFileAttributesEx_func,
    char const * const GetFileAttributesEx_name,
    CreateFileFunc && CreateFile_func,
    char const * const CreateFile_name,
    GetFinalPathNameByHandleFunc && GetFinalPathNameByHandle_func,
    char const * const GetFinalPathNameByHandle_name) {
  SST_ASSERT((!moved_from_));
  SST_ASSERT((GetFileAttributesEx_name != nullptr));
  SST_ASSERT((CreateFile_name != nullptr));
  SST_ASSERT((GetFinalPathNameByHandle_name != nullptr));
  bool have_data = false;
  WIN32_FILE_ATTRIBUTE_DATA data;
  BOOL const r = GetFileAttributesEx_func(str_.c_str(),
                                          GetFileExInfoStandard,
                                          &data);
  if (r == 0) {
    DWORD const e = GetLastError();
    if (e != ERROR_FILE_NOT_FOUND && e != ERROR_PATH_NOT_FOUND) {
      throw sst::gle_exception(std::string(GetFileAttributesEx_name)
                                   + "() failed on path "
                                   + sst::c_quote(str_),
                               e);
    }
  } else if (follow_links_
             && (data.dwFileAttributes
                 & FILE_ATTRIBUTE_REPARSE_POINT)) {
    HANDLE const h = CreateFile_func(
        str_.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ?
            FILE_FLAG_BACKUP_SEMANTICS :
            0,
        nullptr);
    if (h == INVALID_HANDLE_VALUE) {
      DWORD const e = GetLastError();
      if (e != ERROR_FILE_NOT_FOUND && e != ERROR_PATH_NOT_FOUND) {
        throw sst::gle_exception(std::string(CreateFile_name)
                                     + "() failed on path "
                                     + sst::c_quote(str_),
                                 e);
      }
    } else {
      try {
        std::vector<value_type> s(512);
        while (true) {
          DWORD const n = GetFinalPathNameByHandle_func(
              h,
              s.data(),
              sst::checked_cast<DWORD>(s.size()),
              0);
          if (n == 0) {
            DWORD const e = GetLastError();
            if (e != ERROR_FILE_NOT_FOUND
                && e != ERROR_PATH_NOT_FOUND) {
              throw sst::gle_exception(
                  std::string(GetFinalPathNameByHandle_name)
                      + "() failed on path " + sst::c_quote(str_),
                  e);
            }
            break;
          }
          if (sst::unsigned_lt(n, s.size())) {
            if (GetFileAttributesEx_func(s.data(),
                                         GetFileExInfoStandard,
                                         &data)
                == 0) {
              DWORD const e = GetLastError();
              if (e != ERROR_FILE_NOT_FOUND
                  && e != ERROR_PATH_NOT_FOUND) {
                throw sst::gle_exception(
                    std::string(GetFileAttributesEx_name)
                        + "() failed on path " + sst::c_quote(s.data()),
                    e);
              }
            } else {
              have_data = true;
            }
            break;
          }
          using sz = decltype(s.size());
          s.resize(sst::checked_cast<sz>(sst::checked_t<sz>(n) + 1));
        }
        static_cast<void>(CloseHandle(h));
      } catch (...) {
        static_cast<void>(CloseHandle(h));
        throw;
      }
    }
  } else {
    have_data = true;
  }
  return refresh_from_attr(have_data ? &data : nullptr);
}

} // namespace sst

#endif // #if SST_WITH_WINDOWS_KERNEL32

#endif // #ifndef SST_CATALOG_WINDOWS_PATH_REFRESH_CORE_HPP
