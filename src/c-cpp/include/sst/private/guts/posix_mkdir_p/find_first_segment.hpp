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

#ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_FIND_FIRST_SEGMENT_HPP
#define SST_PRIVATE_GUTS_POSIX_MKDIR_P_FIND_FIRST_SEGMENT_HPP

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <sst/private/guts/posix_mkdir_p/find_next_segment.hpp>

namespace sst {
namespace guts {
namespace posix_mkdir_p {

template<class T>
auto find_first_segment(T const & path)
    -> decltype(find_next_segment(path)) {
  return find_next_segment(path);
}

} // namespace posix_mkdir_p
} // namespace guts
} // namespace sst

#endif // #if SST_WITH_POSIX

#endif // #ifndef SST_PRIVATE_GUTS_POSIX_MKDIR_P_FIND_FIRST_SEGMENT_HPP
