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

#ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_HPP
#define SST_PRIVATE_GUTS_POSIX_MKDIR_P_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <cstddef>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.hpp>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_zero.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/SST_DLL_EXPORT.h>

namespace sst {
namespace guts {
namespace posix_mkdir_p {

//----------------------------------------------------------------------

SST_DLL_EXPORT bool make_directory(char const * path);

template<class Byte, sst::enable_if_t<sst::is_byte<Byte>::value> = 0>
bool make_directory(Byte const * const path) {
  return make_directory(reinterpret_cast<char const *>(path));
}

//----------------------------------------------------------------------

template<class CharT>
std::size_t find_next_segment(CharT const * const path,
                              std::size_t i = 0) {
  SST_ASSERT((path != nullptr));
  while (path[i] != CharT('\0') && path[i] == CharT('/')) {
    ++i;
  }
  while (path[i] != CharT('\0') && path[i] != CharT('/')) {
    ++i;
  }
  return i;
}

template<class String,
         class CharT = typename String::value_type,
         class SizeT = typename String::size_type>
SizeT find_next_segment(String const & path, SizeT i = 0) {
  SST_ASSERT((i <= path.size()));
  while (i < path.size() && path[i] == CharT('/')) {
    ++i;
  }
  while (i < path.size() && path[i] != CharT('/')) {
    ++i;
  }
  return i;
}

//----------------------------------------------------------------------

enum class style_t {
  p,
  p_new,
  p_only,
};

//----------------------------------------------------------------------

template<class Byte, sst::enable_if_t<sst::is_byte<Byte>::value> = 0>
bool helper(Byte const * const path, style_t const style) {
  SST_ASSERT((path != nullptr));
  auto const i = find_next_segment(path);
  if (sst::is_zero(path[i])) {
    switch (style) {
      case style_t::p: {
        return make_directory(path);
      } break;
      case style_t::p_new: {
        if (!make_directory(path)) {
          throw std::runtime_error("Cannot create directory "
                                   + sst::c_quote(path)
                                   + " because it already exists.");
        }
        return true;
      } break;
      case style_t::p_only: {
        return false;
      } break;
    }
  }
  bool r = false;
  std::basic_string<Byte> p = path;
  auto j = static_cast<decltype(p.size())>(i);
  do {
    auto const x = p[j];
    p[j] = 0;
    if (make_directory(p.c_str())) {
      r = true;
    }
    p[j] = x;
    j = find_next_segment(p, j);
  } while (j < p.size());
  switch (style) {
    case style_t::p: {
      if (make_directory(p.c_str())) {
        r = true;
      }
    } break;
    case style_t::p_new: {
      if (!make_directory(p.c_str())) {
        throw std::runtime_error("Cannot create directory "
                                 + sst::c_quote(path)
                                 + " because it already exists.");
      }
      r = true;
    } break;
    case style_t::p_only: {
    } break;
  }
  return r;
}

//----------------------------------------------------------------------
//
// When the path parameter is an rvalue reference to a string class, we
// can avoid making any copies.
//

template<
    class String,
    sst::enable_if_t<std::is_class<sst::remove_cvref_t<String>>::value
                     && std::is_rvalue_reference<String &&>::value> = 0>
bool helper(String && path, style_t const style) {
  auto const i = find_next_segment(path);
  if (i == path.size()) {
    switch (style) {
      case style_t::p: {
        return make_directory(sst::c_str(path));
      } break;
      case style_t::p_new: {
        if (!make_directory(sst::c_str(path))) {
          throw std::runtime_error("Cannot create directory "
                                   + sst::c_quote(path)
                                   + " because it already exists.");
        }
        return true;
      } break;
      case style_t::p_only: {
        return false;
      } break;
    }
  }
  bool r = false;
  auto && p = path;
  auto j = static_cast<decltype(p.size())>(i);
  do {
    auto const x = p[j];
    p[j] = 0;
    if (make_directory(sst::c_str(p))) {
      r = true;
    }
    p[j] = x;
    j = find_next_segment(p, j);
  } while (j < p.size());
  switch (style) {
    case style_t::p: {
      if (make_directory(sst::c_str(p))) {
        r = true;
      }
    } break;
    case style_t::p_new: {
      if (!make_directory(sst::c_str(p))) {
        throw std::runtime_error("Cannot create directory "
                                 + sst::c_quote(path)
                                 + " because it already exists.");
      }
      r = true;
    } break;
    case style_t::p_only: {
    } break;
  }
  return r;
}

//----------------------------------------------------------------------

template<
    class String,
    sst::enable_if_t<std::is_class<sst::remove_cvref_t<String>>::value
                     && std::is_lvalue_reference<String &&>::value> = 0>
bool helper(String && path, style_t const style) {
  return helper(sst::c_str(std::forward<String>(path)), style);
}

//----------------------------------------------------------------------

} // namespace posix_mkdir_p
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // SST_PRIVATE_GUTS_POSIX_MKDIR_P_HPP
