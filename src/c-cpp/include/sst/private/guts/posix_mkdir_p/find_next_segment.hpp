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

#ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_FIND_NEXT_SEGMENT_HPP
#define SST_PRIVATE_GUTS_POSIX_MKDIR_P_FIND_NEXT_SEGMENT_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <cstddef>

#include <sst/catalog/SST_ASSERT.h>

namespace sst {
namespace guts {
namespace posix_mkdir_p {

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

//----------------------------------------------------------------------

template<class String>
typename String::size_type
find_next_segment(String const & path,
                  typename String::size_type i = 0) {
  SST_ASSERT((i < path.size()));
  using CharT = typename String::value_type;
  while (i < path.size() && path[i] == CharT('/')) {
    ++i;
  }
  while (i < path.size() && path[i] != CharT('/')) {
    ++i;
  }
  return i;
}

//----------------------------------------------------------------------

} // namespace posix_mkdir_p
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // #ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_FIND_NEXT_SEGMENT_HPP
