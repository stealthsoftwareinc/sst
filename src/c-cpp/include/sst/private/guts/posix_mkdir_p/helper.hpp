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

#ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_HELPER_HPP
#define SST_PRIVATE_GUTS_POSIX_MKDIR_P_HELPER_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include <sst/catalog/SST_ASSERT.h>
#include <sst/catalog/c_quote.hpp>
#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/is_byte.hpp>
#include <sst/catalog/is_zero.hpp>
#include <sst/catalog/remove_cvref_t.hpp>
#include <sst/private/guts/posix_mkdir_p/find_first_segment.hpp>
#include <sst/private/guts/posix_mkdir_p/find_next_segment.hpp>
#include <sst/private/guts/posix_mkdir_p/helper.hpp>
#include <sst/private/guts/posix_mkdir_p/make_directory.hpp>
#include <sst/private/guts/posix_mkdir_p/style.hpp>

namespace sst {
namespace guts {
namespace posix_mkdir_p {

//----------------------------------------------------------------------

template<class Byte, sst::enable_if_t<sst::is_byte<Byte>::value> = 0>
bool helper(Byte const * const path,
            sst::guts::posix_mkdir_p::style const style) {
  SST_ASSERT((path != nullptr));
  auto const i = sst::guts::posix_mkdir_p::find_first_segment(path);
  if (sst::is_zero(path[i])) {
    switch (style) {
      case sst::guts::posix_mkdir_p::style::p: {
        return sst::guts::posix_mkdir_p::make_directory(path);
      } break;
      case sst::guts::posix_mkdir_p::style::p_new: {
        if (!sst::guts::posix_mkdir_p::make_directory(path)) {
          throw std::runtime_error("Cannot create directory "
                                   + sst::c_quote(path)
                                   + " because it already exists.");
        }
      } break;
      case sst::guts::posix_mkdir_p::style::p_only: {
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
    if (sst::guts::posix_mkdir_p::make_directory(p.c_str())) {
      r = true;
    }
    p[j] = x;
    j = sst::guts::posix_mkdir_p::find_next_segment(p, j);
  } while (j < p.size());
  switch (style) {
    case sst::guts::posix_mkdir_p::style::p: {
      if (sst::guts::posix_mkdir_p::make_directory(p.c_str())) {
        r = true;
      }
    } break;
    case sst::guts::posix_mkdir_p::style::p_new: {
      if (!sst::guts::posix_mkdir_p::make_directory(p.c_str())) {
        throw std::runtime_error("Cannot create directory "
                                 + sst::c_quote(path)
                                 + " because it already exists.");
      }
      r = true;
    } break;
    case sst::guts::posix_mkdir_p::style::p_only: {
    } break;
  }
  return r;
}

//----------------------------------------------------------------------

template<
    class String,
    sst::enable_if_t<std::is_class<sst::remove_cvref_t<String>>::value
                     && std::is_rvalue_reference<String &&>::value> = 0>
bool helper(String && path,
            sst::guts::posix_mkdir_p::style const style) {
  auto const i = sst::guts::posix_mkdir_p::find_first_segment(path);
  if (i == path.size()) {
    switch (style) {
      case sst::guts::posix_mkdir_p::style::p: {
        return sst::guts::posix_mkdir_p::make_directory(
            sst::c_str(path));
      } break;
      case sst::guts::posix_mkdir_p::style::p_new: {
        if (!sst::guts::posix_mkdir_p::make_directory(
                sst::c_str(path))) {
          throw std::runtime_error("Cannot create directory "
                                   + sst::c_quote(path)
                                   + " because it already exists.");
        }
      } break;
      case sst::guts::posix_mkdir_p::style::p_only: {
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
    if (sst::guts::posix_mkdir_p::make_directory(sst::c_str(p))) {
      r = true;
    }
    p[j] = x;
    j = sst::guts::posix_mkdir_p::find_next_segment(p, j);
  } while (j < p.size());
  switch (style) {
    case sst::guts::posix_mkdir_p::style::p: {
      if (sst::guts::posix_mkdir_p::make_directory(sst::c_str(p))) {
        r = true;
      }
    } break;
    case sst::guts::posix_mkdir_p::style::p_new: {
      if (!sst::guts::posix_mkdir_p::make_directory(sst::c_str(p))) {
        throw std::runtime_error("Cannot create directory "
                                 + sst::c_quote(path)
                                 + " because it already exists.");
      }
      r = true;
    } break;
    case sst::guts::posix_mkdir_p::style::p_only: {
    } break;
  }
  return r;
}

//----------------------------------------------------------------------

template<
    class String,
    sst::enable_if_t<std::is_class<sst::remove_cvref_t<String>>::value
                     && std::is_lvalue_reference<String &&>::value> = 0>
bool helper(String && path,
            sst::guts::posix_mkdir_p::style const style) {
  return sst::guts::posix_mkdir_p::helper(
      sst::c_str(std::forward<String>(path)),
      style);
}

//----------------------------------------------------------------------

} // namespace posix_mkdir_p
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // #ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_HELPER_HPP
