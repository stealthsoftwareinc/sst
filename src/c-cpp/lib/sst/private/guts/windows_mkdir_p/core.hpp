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

#ifndef SST_PRIVATE_GUTS_WINDOWS_MKDIR_P_CORE_HPP
#define SST_PRIVATE_GUTS_WINDOWS_MKDIR_P_CORE_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/SST_THROW_UNIMPLEMENTED.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/gle_exception.hpp>

namespace sst {
namespace guts {
namespace windows_mkdir_p {

template<class CharT>
bool is_slash(CharT const c) {
  return c == CharT('\\') || c == CharT('/');
}

template<class Size = std::size_t, class CharT>
Size find_next_segment(CharT const * const path, Size i = 0) {
  SST_ASSERT((path != nullptr));
  while (path[i] != CharT('\0') && is_slash(path[i])) {
    ++i;
  }
  while (path[i] != CharT('\0') && !is_slash(path[i])) {
    ++i;
  }
  return i;
}

template<class String>
typename String::size_type
find_next_segment(String const & path,
                  typename String::size_type const i = 0) {
  return find_next_segment(path.c_str(), i);
}

template<class Size = std::size_t, class CharT>
bool is_drive_colon(CharT const * const path, Size const i) {
  SST_ASSERT((path != nullptr));
  return i == 2 && path[1] == CharT(':');
}

template<class Size = std::size_t, class CharT>
bool is_dos_device(CharT const * const path, Size const i) {
  SST_ASSERT((path != nullptr));
  return i == 3 && is_slash(path[0]) && is_slash(path[1])
         && (path[2] == CharT('?') || path[2] == CharT('.'));
}

template<class Size = std::size_t, class CharT>
bool is_network(CharT const * const path, Size const i) {
  SST_ASSERT((path != nullptr));
  return i >= 3 && is_slash(path[0]) && is_slash(path[1])
         && !is_dos_device(path, i);
}

template<class Size = std::size_t, class CharT>
Size find_first_segment(CharT const * const path) {
  SST_ASSERT((path != nullptr));
  Size const i = find_next_segment(path);
  if (is_drive_colon(path, i)) {
    return find_next_segment(path, i);
  }
  if (is_dos_device(path, i)) {
    SST_THROW_UNIMPLEMENTED();
  }
  if (is_network(path, i)) {
    return find_next_segment(path, find_next_segment(path, i));
  }
  return i;
}

template<class CharT,
         class CreateDirectoryFunc,
         class GetFileAttributesFunc>
bool make_directory(CharT const * const path,
                    CreateDirectoryFunc && CreateDirectory_func,
                    char const * const CreateDirectory_name,
                    GetFileAttributesFunc && GetFileAttributes_func,
                    char const * const GetFileAttributes_name) {
  SST_ASSERT((path != nullptr));
  if (CreateDirectory_func(path, nullptr) != 0) {
    return true;
  }
  {
    DWORD const e = ::GetLastError();
    if (e != ERROR_ALREADY_EXISTS) {
      throw sst::gle_exception(std::string(CreateDirectory_name)
                                   + "() failed on path "
                                   + sst::c_quote(path),
                               e);
    }
  }
  {
    DWORD const a = GetFileAttributes_func(path);
    if (a == INVALID_FILE_ATTRIBUTES) {
      DWORD const e = ::GetLastError();
      throw sst::gle_exception(std::string(GetFileAttributes_name)
                                   + "() failed on path "
                                   + sst::c_quote(path),
                               e);
    }
    if (a & FILE_ATTRIBUTE_DIRECTORY) {
      return false;
    }
  }
  throw std::runtime_error(
      "Cannot create directory " + sst::c_quote(path)
      + " because it already exists as a non-directory.");
}

template<class CharT,
         class CreateDirectoryFunc,
         class GetFileAttributesFunc>
bool core(CharT const * const path,
          CreateDirectoryFunc && CreateDirectory_func,
          char const * const CreateDirectory_name,
          GetFileAttributesFunc && GetFileAttributes_func,
          char const * const GetFileAttributes_name) {
  SST_ASSERT((path != nullptr));
  auto const i = find_first_segment(path);
  if (path[i] == 0) {
    return make_directory(path,
                          CreateDirectory_func,
                          CreateDirectory_name,
                          GetFileAttributes_func,
                          GetFileAttributes_name);
  }
  bool r = false;
  std::basic_string<CharT> p = path;
  auto j = static_cast<decltype(p.size())>(i);
  do {
    auto const x = p[j];
    p[j] = 0;
    if (make_directory(p.c_str(),
                       CreateDirectory_func,
                       CreateDirectory_name,
                       GetFileAttributes_func,
                       GetFileAttributes_name)) {
      r = true;
    }
    p[j] = x;
    j = find_next_segment(p, j);
  } while (j < p.size());
  if (make_directory(p.c_str(),
                     CreateDirectory_func,
                     CreateDirectory_name,
                     GetFileAttributes_func,
                     GetFileAttributes_name)) {
    r = true;
  }
  return r;
}

} // namespace windows_mkdir_p
} // namespace guts
} // namespace sst

#endif // #ifndef SST_PRIVATE_GUTS_WINDOWS_MKDIR_P_CORE_HPP
