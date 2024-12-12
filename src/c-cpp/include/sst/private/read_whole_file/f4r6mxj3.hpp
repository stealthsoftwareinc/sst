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

#ifndef SST_PRIVATE_READ_WHOLE_FILE_F4R6MXJ3_HPP
#define SST_PRIVATE_READ_WHOLE_FILE_F4R6MXJ3_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <sst/catalog/c_str.hpp>
#include <sst/catalog/enable_if_t.hpp>
#include <sst/catalog/read_whole_file.hpp>
#include <sst/catalog/read_whole_file_functor.hpp>
#include <sst/catalog/remove_cvref_t.hpp>

namespace sst {

#define SST_src_t sst::remove_cvref_t<Src>
#define SST_dst_t sst::remove_cvref_t<Dst>
#define SST_src (std::declval<SST_src_t const &>())

template<class Dst, class Src>
class read_whole_file_functor<
    sst::enable_if_t<std::is_convertible<decltype(sst::c_str(SST_src)),
                                         char const *>::value>,
    Dst,
    Src> {

  using src_t = SST_src_t;
  using dst_t = SST_dst_t;

public:

  dst_t operator()(src_t const & src) const {
    dst_t dst;
    sst::read_whole_file<Dst>(src, std::back_inserter(dst));
    return dst;
  }

}; //

#undef SST_src
#undef SST_dst_t
#undef SST_src_t

} // namespace sst

#endif // SST_PRIVATE_READ_WHOLE_FILE_F4R6MXJ3_HPP
