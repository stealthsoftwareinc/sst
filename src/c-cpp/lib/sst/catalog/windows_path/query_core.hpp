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

#ifndef SST_CATALOG_WINDOWS_PATH_QUERY_CORE_HPP
#define SST_CATALOG_WINDOWS_PATH_QUERY_CORE_HPP

// Include first to test independence.
#include <sst/catalog/windows_path.hpp>
// Include twice to test idempotence.
#include <sst/catalog/windows_path.hpp>
//

#include <sst/catalog/SST_WITH_WINDOWS_KERNEL32.h>

#if SST_WITH_WINDOWS_KERNEL32

#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include <windows.h>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/SST_STATIC_ASSERT.h>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/checked.hpp>
#include <sst/catalog/checked_cast.hpp>
#include <sst/catalog/checked_resize.hpp>
#include <sst/catalog/gle_exception.hpp>
#include <sst/catalog/pointer_eq.hpp>
#include <sst/catalog/unsigned_ge.hpp>

namespace sst {

#define SST_F(F)                                                       \
  SST_ASSERT((F##_func != nullptr));                                   \
  SST_ASSERT((F##_name != nullptr));                                   \
  if (std::is_same<CharT, char>::value) {                              \
    SST_ASSERT((sst::pointer_eq(F##_func, &F##A)));                    \
    SST_ASSERT((std::strcmp(F##_name, #F "A") == 0));                  \
  } else {                                                             \
    SST_ASSERT((sst::pointer_eq(F##_func, &F##W)));                    \
    SST_ASSERT((std::strcmp(F##_name, #F "W") == 0));                  \
  }

template<class CharT>
template<class GetFileAttributesExFunc,
         class CreateFileFunc,
         class GetFinalPathNameByHandleFunc>
void windows_path<CharT>::query_core(
    GetFileAttributesExFunc * const GetFileAttributesEx_func,
    char const * const GetFileAttributesEx_name,
    CreateFileFunc * const CreateFile_func,
    char const * const CreateFile_name,
    GetFinalPathNameByHandleFunc * const GetFinalPathNameByHandle_func,
    char const * const GetFinalPathNameByHandle_name) const {
  SST_STATIC_ASSERT((std::is_same<CharT, char>::value
                     || std::is_same<CharT, wchar_t>::value));
  SST_ASSERT((!this->moved_from_));
  SST_F(GetFileAttributesEx);
  SST_F(CreateFile);
  SST_F(GetFinalPathNameByHandle);
  bool have_data = false;
  WIN32_FILE_ATTRIBUTE_DATA data;
  BOOL const r = GetFileAttributesEx_func(this->c_str(),
                                          GetFileExInfoStandard,
                                          &data);
  if (r == 0) {
    DWORD const e = GetLastError();
    if (e != ERROR_FILE_NOT_FOUND && e != ERROR_PATH_NOT_FOUND) {
      throw sst::gle_exception(std::string(GetFileAttributesEx_name)
                                   + "() failed on path "
                                   + sst::c_quote(this->c_str()),
                               e);
    }
  } else if (this->follow_links()
             && (data.dwFileAttributes
                 & FILE_ATTRIBUTE_REPARSE_POINT)) {
    HANDLE const h = CreateFile_func(
        this->c_str(),
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
                                     + sst::c_quote(this->c_str()),
                                 e);
      }
    } else {
      try {
        std::vector<char_t> s;
        sst::checked_resize(s, 512);
        while (true) {
          DWORD const n = GetFinalPathNameByHandle_func(
              h,
              s.data(),
              sst::checked_cast<DWORD>(s.size()),
              static_cast<DWORD>(0));
          if (n == 0) {
            DWORD const e = GetLastError();
            if (e != ERROR_FILE_NOT_FOUND
                && e != ERROR_PATH_NOT_FOUND) {
              throw sst::gle_exception(
                  std::string(GetFinalPathNameByHandle_name)
                      + "() failed on path "
                      + sst::c_quote(this->c_str()),
                  e);
            }
            break;
          }
          if (sst::unsigned_ge(n, s.size())) {
            sst::checked_resize(s, sst::checked(n) + 1);
            continue;
          }
          if (!GetFileAttributesEx_func(s.data(),
                                        GetFileExInfoStandard,
                                        &data)) {
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
        static_cast<void>(CloseHandle(h));
      } catch (...) {
        static_cast<void>(CloseHandle(h));
        throw;
      }
    }
  } else {
    have_data = true;
  }
  this->query_from_attr(have_data ? &data : nullptr);
}

#undef SST_F

} // namespace sst

#endif // #if SST_WITH_WINDOWS_KERNEL32

#endif // SST_CATALOG_WINDOWS_PATH_QUERY_CORE_HPP
